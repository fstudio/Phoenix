#include  <Edit/Base.h>
#include  <Edit/Physics.h>
/////

////////demo function
int  WINAPI ParserByteToLineMode(BYTE *b,size_t len)
{
    size_t i=0;
    size_t pre=0;
    bool stat=false;
    for(;i<len;i++)
    {
        while(b[i]=='\r'){
            if(i+1<len&&b[i+1]!='\n')
            {
                //New Line.
                pre=i;
            }else{
                stat=true;
            }
        }
        while(b[i]=='\n')
        {
            //*b[pre]; i-pre-1;
            stat=false;
            pre=i;
        }
    }
    return 0;
}

TextDocument::TextDocument()
{
    ///
}

int TextDocument::ParsePhyMemoryFile()
{
    return 0;
}