/*********************************************************************************************************
*   Phoneix Native Module Launcher Host
*   Note: LauncherDll.cpp
*   Date: 2015.01.13
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <Windows.h>
#include <Runtime/Runtime.h>
#include <sstream>

typedef int(* PackageInitialize)(int Argc,char **Argv);


/*
    PCHAR*
    CommandLineToArgvA(
        PCHAR CmdLine,
        int* _argc
        )
    {
        PCHAR* argv;
        PCHAR  _argv;
        ULONG   len;
        ULONG   argc;
        CHAR   a;
        ULONG   i, j;

        BOOLEAN  in_QM;
        BOOLEAN  in_TEXT;
        BOOLEAN  in_SPACE;

        len = strlen(CmdLine);
        i = ((len+2)/2)*sizeof(PVOID) + sizeof(PVOID);

        argv = (PCHAR*)GlobalAlloc(GMEM_FIXED,
            i + (len+2)*sizeof(CHAR));

        _argv = (PCHAR)(((PUCHAR)argv)+i);

        argc = 0;
        argv[argc] = _argv;
        in_QM = FALSE;
        in_TEXT = FALSE;
        in_SPACE = TRUE;
        i = 0;
        j = 0;

        while( a = CmdLine[i] ) {
            if(in_QM) {
                if(a == '\"') {
                    in_QM = FALSE;
                } else {
                    _argv[j] = a;
                    j++;
                }
            } else {
                switch(a) {
                case '\"':
                    in_QM = TRUE;
                    in_TEXT = TRUE;
                    if(in_SPACE) {
                        argv[argc] = _argv+j;
                        argc++;
                    }
                    in_SPACE = FALSE;
                    break;
                case ' ':
                case '\t':
                case '\n':
                case '\r':
                    if(in_TEXT) {
                        _argv[j] = '\0';
                        j++;
                    }
                    in_TEXT = FALSE;
                    in_SPACE = TRUE;
                    break;
                default:
                    in_TEXT = TRUE;
                    if(in_SPACE) {
                        argv[argc] = _argv+j;
                        argc++;
                    }
                    _argv[j] = a;
                    j++;
                    in_SPACE = FALSE;
                    break;
                }
            }
            i++;
        }
        _argv[j] = '\0';
        argv[argc] = NULL;

        (*_argc) = argc;
        return argv;
    }

*/
////Note: Argv[0] is this Package Name
LPSTR* WINAPI CommandLineToArgvA(LPCSTR lpCmdline, int* numargs)
{
    DWORD argc;
    LPSTR  *argv;
    LPSTR s;
    LPSTR d;
    LPSTR cmdline;
    int qcount,bcount;

    if(!numargs)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return NULL;
    }

    if (*lpCmdline==0)
    {
        /* Return the path to the executable */
        DWORD len, deslen=MAX_PATH, size;

        size = sizeof(LPSTR)*2 + deslen*sizeof(CHAR);
        for (;;)
        {
            if (!(argv = LocalAlloc(LMEM_FIXED, size))) return NULL;
            len = GetModuleFileNameA(0, (LPSTR)(argv+2), deslen);
            if (!len)
            {
                LocalFree(argv);
                return NULL;
            }
            if (len < deslen) break;
            deslen*=2;
            size = sizeof(LPSTR)*2 + deslen*sizeof(CHAR);
            LocalFree( argv );
        }
        argv[0]=(LPSTR)(argv+2);
        argv[1]=NULL;
        *numargs=1;

        return argv;
    }

    /* --- First count the arguments */
    argc=1;
    s=lpCmdline;
    /* The first argument, the executable path, follows special rules */
    if (*s=='"')
    {
        /* The executable path ends at the next quote, no matter what */
        s++;
        while (*s)
            if (*s++=='"')
                break;
    }
    else
    {
        /* The executable path ends at the next space, no matter what */
        while (*s && *s!=' ' && *s!='\t')
            s++;
    }
    /* skip to the first argument, if any */
    while (*s==' ' || *s=='\t')
        s++;
    if (*s)
        argc++;

    /* Analyze the remaining arguments */
    qcount=bcount=0;
    while (*s)
    {
        if ((*s==' ' || *s=='\t') && qcount==0)
        {
            /* skip to the next argument and count it if any */
            while (*s==' ' || *s=='\t')
                s++;
            if (*s)
                argc++;
            bcount=0;
        }
        else if (*s=='\\')
        {
            /* '\', count them */
            bcount++;
            s++;
        }
        else if (*s=='"')
        {
            /* '"' */
            if ((bcount & 1)==0)
                qcount++; /* unescaped '"' */
            s++;
            bcount=0;
            /* consecutive quotes, see comment in copying code below */
            while (*s=='"')
            {
                qcount++;
                s++;
            }
            qcount=qcount % 3;
            if (qcount==2)
                qcount=0;
        }
        else
        {
            /* a regular character */
            bcount=0;
            s++;
        }
    }

    /* Allocate in a single lump, the string array, and the strings that go
     * with it. This way the caller can make a single LocalFree() call to free
     * both, as per MSDN.
     */
    argv=LocalAlloc(LMEM_FIXED, (argc+1)*sizeof(LPSTR)+(strlen(lpCmdline)+1)*sizeof(CHAR));
    if (!argv)
        return NULL;
    cmdline=(LPSTR)(argv+argc+1);
    strcpy(cmdline, lpCmdline);

    /* --- Then split and copy the arguments */
    argv[0]=d=cmdline;
    argc=1;
    /* The first argument, the executable path, follows special rules */
    if (*d=='"')
    {
        /* The executable path ends at the next quote, no matter what */
        s=d+1;
        while (*s)
        {
            if (*s=='"')
            {
                s++;
                break;
            }
            *d++=*s++;
        }
    }
    else
    {
        /* The executable path ends at the next space, no matter what */
        while (*d && *d!=' ' && *d!='\t')
            d++;
        s=d;
        if (*s)
            s++;
    }
    /* close the executable path */
    *d++=0;
    /* skip to the first argument and initialize it if any */
    while (*s==' ' || *s=='\t')
        s++;
    if (!*s)
    {
        /* There are no parameters so we are all done */
        argv[argc]=NULL;
        *numargs=argc;
        return argv;
    }

    /* Split and copy the remaining arguments */
    argv[argc++]=d;
    qcount=bcount=0;
    while (*s)
    {
        if ((*s==' ' || *s=='\t') && qcount==0)
        {
            /* close the argument */
            *d++=0;
            bcount=0;

            /* skip to the next one and initialize it if any */
            do {
                s++;
            } while (*s==' ' || *s=='\t');
            if (*s)
                argv[argc++]=d;
        }
        else if (*s=='\\')
        {
            *d++=*s++;
            bcount++;
        }
        else if (*s=='"')
        {
            if ((bcount & 1)==0)
            {
                /* Preceded by an even number of '\', this is half that
                 * number of '\', plus a quote which we erase.
                 */
                d-=bcount/2;
                qcount++;
            }
            else
            {
                /* Preceded by an odd number of '\', this is half that
                 * number of '\' followed by a '"'
                 */
                d=d-bcount/2-1;
                *d++='"';
            }
            s++;
            bcount=0;
            /* Now count the number of consecutive quotes. Note that qcount
             * already takes into account the opening quote if any, as well as
             * the quote that lead us here.
             */
            while (*s=='"')
            {
                if (++qcount==3)
                {
                    *d++='"';
                    qcount=0;
                }
                s++;
            }
            if (qcount==2)
                qcount=0;
        }
        else
        {
            /* a regular character */
            *d++=*s++;
            bcount=0;
        }
    }
    *d='\0';
    argv[argc]=NULL;
    *numargs=argc;

    return argv;
}

class Arguments{
private:
    std::vector<char *> argv_;
public:
    static Arguments Main(LPCSTR lpCmdline)
    {
        int ac;
        LPSTR *w_av = CommandLineToArgvA(lpCmdline, &ac);
        std::vector<std::string> av1(ac);
        std::vector<char const *> av2(ac);
        for (int i = 0; i < ac; i++) {
            av1[i]=w_av[i];
            av2[i] = av1[i].c_str();
        }
        LocalFree(w_av);
        return Arguments(ac,&av2[0]);
    }
    Arguments(int Argc,char const * const* Argv)
    {
        this->argv_.resize(Argc+1);
        for(int i=0;i<Argc;i++)
        {
            this->argv_[i]=strdup(Argv[i]);
        }
        this->argv_[Argc]=0;
    }
    ~Arguments()
    {
        for(size_t i=0;i<this->argv_.size();i++){
            free(argv_[i]);
        }
    }
    int argc()const
    {
        return static_cast<int>(this->argv_.size() - 1);
    }
    char const* const* argv()const {
        return &this->argv_[0];
    }
};




int moduleStartup(const char *module,int Argc,char **Argv)
{
    HMODULE hMod=GetModuleHandleA(module);
    PackageInitialize entry=static_cast<PackageInitialize>(GetProcAddress(hMod,"PackageInitialize"));
    if(entry==nullptr)
        return -1;
    /*
    std::vector<const char* > Args;
    std::string moduleName="PackageExample";
    Args.push_back(moduleName.c_str());
    auto Argc=Args.size()-1;
    */
    int ret=entry(Argc,Argv);
    FreeLibrary(hMod);
    CloseHandle(hMod);
    return ret;
}

HRESULT WINAPI PackageLauncher(const char * pk,const char *search,const char * config)
{
    if(!pk||!search)
        return S_FALSE;
    std::stringstream s;
    s<<search<<"/"<<pk<<".dll";
    if(access(s.str().c_str(),4)!=0)
        return false;
    std::string path=s.str();
    s.clear();
    if(config){
        //Laod config
    }
    return S_OK;
}


DWORD WINAPI ModuleStartupLaucnherThread(LPVOID lpData)
{
    //
    if(!lpData)
        return 1;
    LauncherParam *lparma=static_cast<LauncherParam*>(lpData);
    if(!ComponentInitializeEx())
        return -1;
    ////
    ComponentUnInitialze();
    return 0;
}
