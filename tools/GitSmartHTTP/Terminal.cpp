/*
* Terminal.cpp .Support Windows Color
*/
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>


class Console{
private:
   HANDLE hConsole;
public:
   Console():hConsole(nullptr){
       hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
   }
   ~Console(){
       if(hConsole)
       {
           CloseHandle(hConsole);
       }
   }
   HANDLE get(){
       return this->hConsole;
   }
};

int Print(WORD color,const wchar_t *format,...){
    int ret;
    static Console hCon;
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    GetConsoleScreenBufferInfo(hCon.get(), &bInfo);
    SetConsoleTextAttribute(hCon.get(),color);
    va_list ap;
    va_start(ap, format);
    ret=vwprintf_s(format,ap);
    va_end(ap);
    SetConsoleTextAttribute(hCon.get(),bInfo.wAttributes);
    return 0;
}

