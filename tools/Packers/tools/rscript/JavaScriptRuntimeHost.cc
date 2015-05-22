/*********************************************************************************************************
* JavaScriptRuntimeHost.cc
* Note: Phoenix Container Runtime for JavaScript
* Date: @2015.05
* Author: Force Charlie
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include <Windows.h>
//// when WIN SDK >WINBLUE
#if defined(_WIN32_WINNT) &&_WIN32_WINNT>0x0603
#define USE_EDGEMODE_JSRT
#endif

///
#include <jsrt.h>
#ifdef USE_EDGEMODE_JSRT
#pragma comment(lib,"chakrart.lib")
#else
#pragma comment(lib,"jsrt.lib,")
#endif

using namespace JavaScript;

unsigned currentSourceContext=0;

class JavaScriptRuntimeHost{
private:
public:
    JavaScriptRuntimeHost();
    JsErrorCode CreateHostContext(JsRuntimeHandle runtime,
        int argc, wchar_t *argv [],
        int argumentsStart,
        JsContextRef *context);
};

JavaScriptRuntimeHost::JavaScriptRuntimeHost()
{
    ///
    //Resource Initilaize
}


JsErrorCode JavaScriptRuntimeHost::CreateHostContext(JsRuntimeHandle runtime,
    int argc, wchar_t *argv [],
    int argumentsStart,
    JsContextRef *context)
{
    IfFailRet(JsCreateContext(runtime,nullptr,context));
    IfFailRet(JsSetCurrentContext(*context));
    //
    // Create the host object the script will use.
    //

    JsValueRef hostObject;
    IfFailRet(JsCreateObject(&hostObject));

    //
    // Get the global object
    //

    JsValueRef globalObject;
    IfFailRet(JsGetGlobalObject(&globalObject));

    //
    // Get the name of the property ("host") that we're going to set on the global object.
    //

    JsPropertyIdRef hostPropertyId;
    IfFailRet(JsGetPropertyIdFromName(L"host", &hostPropertyId));

    //
    // Set the property.
    //

    IfFailRet(JsSetProperty(globalObject, hostPropertyId, hostObject, true));

    //
    // Now create the host callbacks that we're going to expose to the script.
    //

    IfFailRet(DefineHostCallback(hostObject, L"echo", Echo));
    IfFailRet(DefineHostCallback(hostObject, L"runScript", RunScript));

    //
    // Create an array for arguments.
    //

    JsValueRef arguments;
    IfFailRet(JsCreateArray(argc - argumentsStart, &arguments));

    for (int index = argumentsStart; index < argc; index++)
    {
        //
        // Create the argument value.
        //

        JsValueRef argument;
        IfFailRet(JsPointerToString(argv[index], wcslen(argv[index]), &argument));

        //
        // Create the index.
        //

        JsValueRef indexValue;
        IfFailRet(JsIntToNumber(index - argumentsStart, &indexValue));

        //
        // Set the value.
        //

        IfFailRet(JsSetIndexedProperty(arguments, indexValue, argument));
    }

    //
    // Get the name of the property that we're going to set on the host object.
    //

    JsPropertyIdRef argumentsPropertyId;
    IfFailRet(JsGetPropertyIdFromName(L"arguments", &argumentsPropertyId));

    //
    // Set the arguments property.
    //

    IfFailRet(JsSetProperty(hostObject, argumentsPropertyId, arguments, true));

    //
    // Clean up the current execution context.
    //

    IfFailRet(JsSetCurrentContext(JS_INVALID_REFERENCE));
    return JsNoError;
}

int WINAPI RunScript(const wchar_t *szJsfile,const wchar_t *argument){
    FILE *file;
    if(_wfopen_s(&file,szJsfile,L"rb")){
        fwprintf(stderr,L"chakrahost:unable to open file: %s.\n",szJsfile);
        return 1;
    }
    unsigned int current=ftell(file);
    fseek(file,0,SEEK_END);
    unsigned int end=ftell(file);
    fseek(file,current,SEEK_SET);
    unsigned int lengthBytes=end-current;
    char *rawBytes=(char*)calloc(lengthBytes+1,sizeof(char));
    if(rawBytes==nullptr){
        fwprintf(stderr,L"chakrahost: fatal errpr.\n");
        fclose(file);
        return 2;
    }
    fread(rawBytes,sizeof(char),lengthBytes,file);
    wchar_t *contents=(wchar_t*)calloc(lengthBytes+1,sizeof(wchar_t));
    if(contents==nullptr){
        free(rawBytes);
        fwprintf(stderr,L"chakrahost: fatal error.]\n");
        fclose(file);
        return 3;
    }
    if (MultiByteToWideChar(CP_UTF8, 0, rawBytes, lengthBytes + 1, contents, lengthBytes + 1) == 0){
        free(rawBytes);
        free(contents);
        fwprintf(stderr, L"chakrahost: fatal error.\n");
        fclose(file);
        return 4;
    }

    auto ret  = RunScriptBuffer(contents,lengthBytes,argument);
    free(rawBytes);
    free(contents);
    return ret;
}

int WINAPI RunScriptBuffer(wchar_t* buffer,size_t bufferSize,const wchar_t *argument){
    return 0;
}
