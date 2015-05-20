/*********************************************************************************************************
* PythonRuntime.cc
* Note: Phoenix Container Runtime for Python
* Date: @2015.05
* Author: Force Charlie
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include <Windows.h>
#include <Python.h>


class MBGet{
private:
    char *pElementText;
public:
    MBGet(const wchar_t *str){
        if(!str){
            pElementText=nullptr;
        }
         int iTextLen;
         iTextLen =WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
         pElementText = new char[iTextLen + 1];
         memset((void *)pElementText, 0, sizeof(char) * (iTextLen + 1));
         ::WideCharToMultiByte(CP_ACP, 0, str, -1, pElementText, iTextLen,NULL, NULL);
    }
    ~MBGet(){
        if(pElementText)
        {
            delete[] pElementText;
        }
    }
    const char* get(){return this->pElementText;}
};
////Run Python Function
int RunPythonFunction(const wchar_t *filePath,const wchar_t *fun)
{
    Py_Initialize();
    if(!Py_IsInitialized())
        return -1;
    PyObject *pModule=nullptr;
    PyObject *pFunc=nullptr;
    MBGet filePathA(filePath);
    MBGet funA(fun);
    pModule=PyImport_InportModule(filePathA.get());
    pFunc=PyObject_GetAttrString(pModule,funA.get());
    PyEval_CallObject(pFunc,nullptr);
    Py_Finalize();
    return 0;
}

int RunPythonFile(const wchar_t *file,const wchar_t *szArg){
    return 0;
}