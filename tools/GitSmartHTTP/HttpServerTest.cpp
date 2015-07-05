// TopdeskSvr.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <http.h>
#include <Windows.h>
#include <assert.h>
#include <iostream>
#include <conio.h>
#include <process.h>
#include <atlbase.h>
#include <string>
#include <atlstr.h>
using namespace std;

#pragma comment(lib, "httpapi.lib")
#define CPK 1
#define CK_EXIT 0
#define TRDCOUNT 10
#define BUFFERLEN 16*1024
#define ITEM(x) {x, _T(#x)}
#define ADD_KNOWN_HEADER(Response, HeaderId, RawValue)               \
	do                                                               \
{                                                                \
	(Response).Headers.KnownHeaders[(HeaderId)].pRawValue =      \
	(RawValue);\
	(Response).Headers.KnownHeaders[(HeaderId)].RawValueLength = \
	(USHORT) strlen(RawValue);                               \
} while(FALSE)
#define CHECKRETUL(ul) if (ul!=NO_ERROR)\
{\
	cout<<"ur="<<ul<<endl;\
}

void _send_http_response(HTTP_REQUEST* HttpRequest,HANDLE ReqQueueHandle, BOOL bAnsyc=FALSE);

enum IO_OPERATION
{
	ClientIORead,
	ClientIOWrite
};

typedef struct _TRDCONTEXT
{
	HANDLE hCompletionPort;
	HANDLE ReqQueueHandle;
}TRDCONTEXT, *PTRDCONTEXT;

struct OVERLAPPEDEX : OVERLAPPED 
{
	CHAR   buffer[BUFFERLEN];
	HTTP_REQUEST_ID HttpRequestId;
	IO_OPERATION IOType;
	HANDLE hFile;
};

struct HTTP_HEADER_DESC 
{
	HTTP_HEADER_ID id;
	PCTSTR desc;
};

HTTP_HEADER_DESC gvRequestHeaderDesc[]={
	ITEM(HttpHeaderCacheControl),
	ITEM(HttpHeaderConnection),
	ITEM(HttpHeaderDate),
	ITEM(HttpHeaderKeepAlive),
	ITEM(HttpHeaderPragma),
	ITEM(HttpHeaderTrailer),
	ITEM(HttpHeaderTransferEncoding),
	ITEM(HttpHeaderUpgrade),
	ITEM(HttpHeaderVia),
	ITEM(HttpHeaderWarning),
	ITEM(HttpHeaderAllow),
	ITEM(HttpHeaderContentLength),
	ITEM(HttpHeaderContentType),
	ITEM(HttpHeaderContentEncoding),
	ITEM(HttpHeaderContentLanguage),
	ITEM(HttpHeaderContentLocation),
	ITEM(HttpHeaderContentMd5),
	ITEM(HttpHeaderContentRange),
	ITEM(HttpHeaderExpires),
	ITEM(HttpHeaderLastModified),
	ITEM(HttpHeaderAccept),
	ITEM(HttpHeaderAcceptCharset),
	ITEM(HttpHeaderAcceptEncoding),
	ITEM(HttpHeaderAcceptLanguage),
	ITEM(HttpHeaderAuthorization),
	ITEM(HttpHeaderCookie),
	ITEM(HttpHeaderExpect),
	ITEM(HttpHeaderFrom),
	ITEM(HttpHeaderHost),
	ITEM(HttpHeaderIfMatch),
	ITEM(HttpHeaderIfModifiedSince),
	ITEM(HttpHeaderIfNoneMatch),
	ITEM(HttpHeaderIfRange),
	ITEM(HttpHeaderIfUnmodifiedSince),
	ITEM(HttpHeaderMaxForwards),
	ITEM(HttpHeaderProxyAuthorization),
	ITEM(HttpHeaderReferer),
	ITEM(HttpHeaderRange),
	ITEM(HttpHeaderTe),
	ITEM(HttpHeaderTranslate),
	ITEM(HttpHeaderUserAgent),
	ITEM(HttpHeaderRequestMaximum)
};

HTTP_HEADER_DESC gvResponseHeaderDesc[]={
	ITEM(HttpHeaderCacheControl),
	ITEM(HttpHeaderConnection),
	ITEM(HttpHeaderDate),
	ITEM(HttpHeaderKeepAlive),
	ITEM(HttpHeaderPragma),
	ITEM(HttpHeaderTrailer),
	ITEM(HttpHeaderTransferEncoding),
	ITEM(HttpHeaderUpgrade),
	ITEM(HttpHeaderVia),
	ITEM(HttpHeaderWarning),
	ITEM(HttpHeaderAllow),
	ITEM(HttpHeaderContentLength),
	ITEM(HttpHeaderContentType),
	ITEM(HttpHeaderContentEncoding),
	ITEM(HttpHeaderContentLanguage),
	ITEM(HttpHeaderContentLocation),
	ITEM(HttpHeaderContentMd5),
	ITEM(HttpHeaderContentRange),
	ITEM(HttpHeaderExpires),
	ITEM(HttpHeaderLastModified),
	ITEM(HttpHeaderAcceptRanges),
	ITEM(HttpHeaderAge),
	ITEM(HttpHeaderEtag),
	ITEM(HttpHeaderLocation),
	ITEM(HttpHeaderProxyAuthenticate),
	ITEM(HttpHeaderRetryAfter),
	ITEM(HttpHeaderServer),
	ITEM(HttpHeaderSetCookie),
	ITEM(HttpHeaderVary),
	ITEM(HttpHeaderWwwAuthenticate),
	ITEM(HttpHeaderResponseMaximum)
};

void InitialOverlappedex(OVERLAPPEDEX* pOverlappedex)
{
	ZeroMemory(pOverlappedex,sizeof(OVERLAPPEDEX));
	pOverlappedex->HttpRequestId=HTTP_NULL_ID;
	pOverlappedex->IOType=ClientIORead;
	pOverlappedex->hFile=INVALID_HANDLE_VALUE;
}

void _parse_http_request(HTTP_REQUEST* pHttpRequest)
{
	USES_CONVERSION;
	int headerCount = sizeof(gvRequestHeaderDesc) / sizeof(HTTP_HEADER_DESC);
	CHAR buffer[MAX_PATH];
	for (int i=0;i<headerCount;i++)
	{
		int HeaderID=gvRequestHeaderDesc[i].id;
		if (pHttpRequest->Headers.KnownHeaders[HeaderID].RawValueLength!=0)
		{
			ZeroMemory(buffer,MAX_PATH);
			memcpy_s(buffer,MAX_PATH,pHttpRequest->Headers.KnownHeaders[HeaderID].pRawValue,pHttpRequest->Headers.KnownHeaders[HeaderID].RawValueLength);
			cout<<T2A(gvRequestHeaderDesc[i].desc)<<":"<<buffer<<endl;
		}
	}
}

std::wstring get_response_xml()
{
	std::wstring xml=L"<person><name>毕向阳</name></person>";
	return xml;
}

void _send_http_response_xml(HTTP_REQUEST* HttpRequest,HANDLE ReqQueueHandle, BOOL bAnsyc)
{
	HTTP_RESPONSE HttpResponse;
	//call ZeroMemory is required, or HttpSendHttpResponse returns ERROR_INVALID_PARAMETER
	ZeroMemory(&HttpResponse,sizeof(HTTP_RESPONSE));
	PCSTR Reason="OK";
	HttpResponse.StatusCode=200;
	HttpResponse.pReason=Reason;
	HttpResponse.ReasonLength=strlen(Reason);

	ADD_KNOWN_HEADER(HttpResponse,HttpHeaderContentType,"text/xml;charset=utf-8");

	std::wstring xml = get_response_xml();
	std::string strbuf = CW2AEX<256>(xml.c_str(),CP_UTF8);

	HTTP_DATA_CHUNK dataChunk[2];
	dataChunk[0].DataChunkType           = HttpDataChunkFromMemory;
	dataChunk[0].FromMemory.pBuffer      = (PVOID)strbuf.c_str();
	dataChunk[0].FromMemory.BufferLength = strbuf.length();
	//dataChunk[1].DataChunkType           = HttpDataChunkFromMemory;
	//dataChunk[1].FromMemory.pBuffer      = (PVOID)xml.c_str();
	//dataChunk[1].FromMemory.BufferLength = xml.length();

	HttpResponse.EntityChunkCount         = 1;
	HttpResponse.pEntityChunks            = dataChunk;

	PHTTP_LOG_FIELDS_DATA pLogFieldsData=NULL;
	HTTP_LOG_FIELDS_DATA LogFieldsData;
	//call ZeroMemory is required, or HttpSendHttpResponse returns ERROR_INVALID_PARAMETER
	ZeroMemory(&LogFieldsData,sizeof(HTTP_LOG_FIELDS_DATA));

	OSVERSIONINFO osversion = {0};
	osversion.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if (GetVersionEx(&osversion))
	{
		//windows vista and later
		if (osversion.dwMajorVersion >= 6)
		{
			LogFieldsData.Base.Type=HttpLogDataTypeFields;
			LogFieldsData.ClientIp="127.0.0.1";
			LogFieldsData.ClientIpLength=strlen("127.0.0.1");
			pLogFieldsData=&LogFieldsData;
		}
	}

	if (!bAnsyc)
	{
		ULONG BytesSent;
		ULONG result = HttpSendHttpResponse(
			ReqQueueHandle,     // ReqQueueHandle
			HttpRequest->RequestId,   // Request ID
			0,       // Flags
			&HttpResponse,           // HTTP response
			NULL,                // pReserved1
			&BytesSent,          // bytes sent  (OPTIONAL)
			NULL,                // pReserved2  (must be NULL)
			0,                   // Reserved3   (must be 0)
			NULL,                // LPOVERLAPPED(OPTIONAL)
			(PHTTP_LOG_DATA)pLogFieldsData                 // pReserved4  (must be NULL)
			); 

		if(result != NO_ERROR)
		{
			wprintf(L"HttpSendHttpResponse failed with %lu \n", result);
		}
	}
	else
	{
		OVERLAPPEDEX* pOverlapped = new OVERLAPPEDEX();
		InitialOverlappedex(pOverlapped);
		pOverlapped->IOType=ClientIOWrite;
		ULONG result = HttpSendHttpResponse(
			ReqQueueHandle,     // ReqQueueHandle
			HttpRequest->RequestId,   // Request ID
			0,       // Flags
			&HttpResponse,           // HTTP response
			NULL,      // pReserved1
			NULL,      // bytes sent  (OPTIONAL)
			NULL,      // pReserved2  (must be NULL)
			0,       // Reserved3   (must be 0)
			pOverlapped,                // LPOVERLAPPED(OPTIONAL)
			(PHTTP_LOG_DATA)pLogFieldsData       // pReserved4  (must be NULL)
			); 

		if(result != NO_ERROR && result!=ERROR_IO_PENDING)
		{
			wprintf(L"HttpSendHttpResponse failed with %lu \n", result);
		}
	}
}
void _send_http_response_file(HTTP_REQUEST* HttpRequest,HANDLE ReqQueueHandle, BOOL bAnsyc)
{
	HTTP_RESPONSE HttpResponse;
	//call ZeroMemory is required, or HttpSendHttpResponse returns ERROR_INVALID_PARAMETER
	ZeroMemory(&HttpResponse,sizeof(HTTP_RESPONSE));
	PCSTR Reason="OK";
	HttpResponse.StatusCode=200;
	HttpResponse.pReason=Reason;
	HttpResponse.ReasonLength=strlen(Reason);

	ADD_KNOWN_HEADER(HttpResponse,HttpHeaderContentType,"text/xml;charset=utf-8");

	std::wstring xml = get_response_xml();
	std::string strbuf = CW2AEX<256>(xml.c_str(),CP_UTF8);

	HTTP_DATA_CHUNK dataChunk[2];
	dataChunk[0].DataChunkType           = HttpDataChunkFromFragmentCache;
	dataChunk[0].FromFragmentCache.pFragmentName = L"https://+:8089/Topsec";
	dataChunk[0].FromFragmentCache.FragmentNameLength = wcslen(L"https://+:8089/Topsec") * 2;
	HttpResponse.EntityChunkCount         = 1;
	HttpResponse.pEntityChunks            = dataChunk;

	OVERLAPPEDEX* pOverlapped = new OVERLAPPEDEX();
	InitialOverlappedex(pOverlapped);
	pOverlapped->IOType=ClientIOWrite;

	ULONG result = HttpSendHttpResponse(
		ReqQueueHandle,     // ReqQueueHandle
		HttpRequest->RequestId,   // Request ID
		0,       // Flags
		&HttpResponse,           // HTTP response
		NULL,      // pReserved1
		NULL,      // bytes sent  (OPTIONAL)
		NULL,      // pReserved2  (must be NULL)
		0,       // Reserved3   (must be 0)
		pOverlapped,              // LPOVERLAPPED(OPTIONAL)
		NULL       // Windows Server 2003 and Windows XP with SP2:  This parameter is reserved and must be NULL.
		//Windows Vista and Windows Server 2008:  This parameter is new for Windows Vista, and Windows Server 2008
		); 
	if(result != NO_ERROR && result!=ERROR_IO_PENDING)
	{
		wprintf(L"HttpSendHttpResponse failed with %lu \n", result);
	}
}

void handle_http_request(HTTP_REQUEST* HttpRequest, HANDLE ReqQueueHandle)
{
	_parse_http_request(HttpRequest);
	if (_strcmpi("/topdesk",HttpRequest->pRawUrl) == 0)
	{
		_send_http_response_xml(HttpRequest, ReqQueueHandle,TRUE);
	}
	else if(_strcmpi("/topsec",HttpRequest->pRawUrl) == 0)
	{
		_send_http_response_file(HttpRequest, ReqQueueHandle,TRUE);
	}
}

unsigned int __stdcall _workthread(void *p)
{
	PTRDCONTEXT pTrdContext=(PTRDCONTEXT)p;
	DWORD NumberOfBytesTransferred;
	ULONG_PTR CompletionKey;
	LPOVERLAPPED pOverlapped;
	DWORD tid=GetCurrentThreadId();
	while (TRUE)
	{
		BOOL bOK=GetQueuedCompletionStatus(
			pTrdContext->hCompletionPort,
			&NumberOfBytesTransferred,
			&CompletionKey,
			&pOverlapped,
			5000);
		if (bOK)
		{
			if (pOverlapped!=NULL)
			{
				OVERLAPPEDEX* pOverlappedex=(OVERLAPPEDEX*)pOverlapped;
				if (pOverlappedex->IOType==ClientIORead)
				{
					handle_http_request((HTTP_REQUEST*)pOverlappedex->buffer, pTrdContext->ReqQueueHandle);InitialOverlappedex(pOverlappedex);HttpReceiveHttpRequest(pTrdContext->ReqQueueHandle,pOverlappedex->HttpRequestId,0,(PHTTP_REQUEST)pOverlappedex->buffer,BUFFERLEN,NULL,pOverlappedex);
				}
				else
				{
					cout<<"send response successfully"<<endl;
					delete pOverlappedex;
				}
			}
			else
			{
				if (CompletionKey==CK_EXIT)
				{
					cout<<"thread "<<tid<<" exit."<<endl;
					break;
				}
			}
		}
	}
	return 0;
}

CStringW GetLoggingDirectory()
{
	WCHAR buffer[MAX_PATH];
	GetModuleFileName(NULL,buffer,MAX_PATH);
	CStringW strFilename=buffer;
	int index=strFilename.ReverseFind(_T('\\'));
	return strFilename.Left(index);
}

int _tmain(int argc, _TCHAR* argv[])
{
	HTTPAPI_VERSION HttpApiVersion=HTTPAPI_VERSION_2;
	ULONG ul;
	ul=HttpInitialize(HttpApiVersion,HTTP_INITIALIZE_CONFIG|HTTP_INITIALIZE_SERVER,NULL);
	assert(ul==NO_ERROR);
	CHECKRETUL(ul);

	HTTP_SERVER_SESSION_ID ServerSessionID;
	ul=HttpCreateServerSession(HttpApiVersion,&ServerSessionID,0);
	assert(ul==NO_ERROR);
	CHECKRETUL(ul);

	//enable logging
	CStringW strLogDir = GetLoggingDirectory();
	HTTP_LOGGING_INFO LogginInfo;
	ZeroMemory(&LogginInfo,sizeof(HTTP_LOGGING_INFO));
	LogginInfo.Flags.Present=1;
	LogginInfo.Format=HttpLoggingTypeW3C;
	LogginInfo.Fields=HTTP_LOG_FIELD_TIME|HTTP_LOG_FIELD_CLIENT_IP;
	LogginInfo.DirectoryName=(LPCWSTR)strLogDir;
	LogginInfo.DirectoryNameLength=strLogDir.GetLength()*2;
	LogginInfo.RolloverType=HttpLoggingRolloverDaily;
	ul=HttpSetServerSessionProperty(ServerSessionID,HttpServerLoggingProperty,&LogginInfo,sizeof(HTTP_LOGGING_INFO));
	assert(ul==NO_ERROR);
	CHECKRETUL(ul);

	HTTP_URL_GROUP_ID UrlGroupID;
	ul=HttpCreateUrlGroup(ServerSessionID,&UrlGroupID,0);
	assert(ul==NO_ERROR);
	CHECKRETUL(ul);

	HTTP_URL_CONTEXT UrlContext=0;
	LPCWSTR TopdeskQualifiedUrl=L"http://+:8088/Topdesk";
	ul=HttpAddUrlToUrlGroup(UrlGroupID,TopdeskQualifiedUrl,UrlContext,0);
	assert(ul==NO_ERROR);
	CHECKRETUL(ul);

	LPCWSTR TopsecQualifiedUrl=L"https://+:8089/Topsec";
	ul=HttpAddUrlToUrlGroup(UrlGroupID,TopsecQualifiedUrl,UrlContext,0);
	assert(ul==NO_ERROR);
	CHECKRETUL(ul);

	HANDLE ReqQueueHandle;
	ul=HttpCreateRequestQueue(HttpApiVersion,NULL,NULL,0,&ReqQueueHandle);
	assert(ul==NO_ERROR);
	CHECKRETUL(ul);

	HTTP_BINDING_INFO Binding;
	Binding.Flags.Present=1;
	Binding.RequestQueueHandle=ReqQueueHandle;
	ul=HttpSetUrlGroupProperty(UrlGroupID,HttpServerBindingProperty,&Binding,sizeof(HTTP_BINDING_INFO));
	assert(ul==NO_ERROR);
	CHECKRETUL(ul);

	std::wstring xml = get_response_xml();
	std::string strbuf = CW2AEX<256>(xml.c_str(),CP_UTF8);
	HTTP_DATA_CHUNK cacheChunk;
	cacheChunk.DataChunkType           = HttpDataChunkFromMemory;
	cacheChunk.FromMemory.pBuffer      = (PVOID)strbuf.c_str();
	cacheChunk.FromMemory.BufferLength = strbuf.length();
	HTTP_CACHE_POLICY CachePolicy;
	CachePolicy.Policy=HttpCachePolicyTimeToLive;
	CachePolicy.SecondsToLive=1000*60;
	ul=HttpAddFragmentToCache(ReqQueueHandle,L"https://+:8089/Topsec",&cacheChunk,&CachePolicy,NULL);
	assert(ul==NO_ERROR);
	CHECKRETUL(ul);

	HANDLE hCompletionPort=CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,CPK,0);
	HANDLE hNewCompletionPort=CreateIoCompletionPort(ReqQueueHandle,hCompletionPort,CPK,0);
	assert(hCompletionPort==hNewCompletionPort);
	HANDLE hTread[TRDCOUNT];
	for (int i=0;i<TRDCOUNT;i++)
	{
		PTRDCONTEXT trdContext = new TRDCONTEXT();
		trdContext->hCompletionPort=hCompletionPort;
		trdContext->ReqQueueHandle=ReqQueueHandle;
		hTread[i]=(HANDLE)_beginthreadex(NULL,0,_workthread,trdContext,0,NULL);
	}
	OVERLAPPEDEX* pOverlappedex=new OVERLAPPEDEX[TRDCOUNT];
	for (int i=0;i<TRDCOUNT;i++)
	{
		InitialOverlappedex(pOverlappedex+i);
		ul=HttpReceiveHttpRequest(
			ReqQueueHandle,
			pOverlappedex->HttpRequestId,
			0, //Only the request headers are retrieved; the entity body is not copied.
			(PHTTP_REQUEST)pOverlappedex->buffer,
			BUFFERLEN,
			NULL,
			pOverlappedex);
		assert(ul==NO_ERROR || ul==ERROR_IO_PENDING);
	}

	cout<<"Press any key to exit."<<endl;
	_getch();

	for(int i=0;i<TRDCOUNT;i++)
	{
		PostQueuedCompletionStatus(hCompletionPort,0,CK_EXIT,0);
	}

	DWORD dwRet=WaitForMultipleObjects(TRDCOUNT,hTread,TRUE,INFINITE);
	cout<<"WaitForMultipleObjects returned, code = "<<dwRet<<endl;

	HttpRemoveUrlFromUrlGroup(UrlGroupID,TopdeskQualifiedUrl,0);
	HttpRemoveUrlFromUrlGroup(UrlGroupID,TopsecQualifiedUrl,0);
	//or HttpRemoveUrlFromUrlGroup(UrlGroupID,NULL,HTTP_URL_FLAG_REMOVE_ALL);

	HttpCloseUrlGroup(UrlGroupID);
	HttpCloseServerSession(ServerSessionID);
	HttpCloseRequestQueue(ReqQueueHandle);
	HttpTerminate(HTTP_INITIALIZE_CONFIG|HTTP_INITIALIZE_SERVER,NULL);

	return 0;
}
