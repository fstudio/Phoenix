/*********************************************************************************************************
*   Phoneix Package Runtime
*   Note: HttpInternal.h
*   Data: 2015.01.18
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#ifndef PHOENIX_PACKAGE_RUNTIME_HTTP_INTERNAL_H
#define PHOENIX_PACKAGE_RUNTIME_HTTP_INTERNAL_H

#ifdef __cplusplus
enum  HTTP_REST_METHOD_FLAGS{
    HTTP_REST_GET=0,
    HTTP_REST_POST=1,
    HTTP_REST_PUT=2,
    HTTP_REST_DELETE=3
};

class CppRest{
private:
    unsigned method;
public:
    CppRest();
};

#endif



#endif
