#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <winhttp.h>
#pragma comment(lib, "winhttp")

using namespace std;

void do_work();

int _tmain(int argc, _TCHAR* argv[])
{
    //_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    do_work();
}

void do_work()
{
    DWORD dwSize = 0;
    DWORD dwDownloaded = 0;
    LPSTR pszOutBuffer;
    BOOL bResults = FALSE;
    HINTERNET hSession = NULL, 
              hConnect = NULL, 
              hRequest = NULL;

    // Use WinHttpOpen to obtain a session handle.
    hSession = WinHttpOpen(L"A WinHTTP Example Program/1.0", 
                           WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, 
                           WINHTTP_NO_PROXY_NAME, 
                           WINHTTP_NO_PROXY_BYPASS, 0);

    // Specify an HTTP server
    if (hSession)
        hConnect = WinHttpConnect(hSession, L"forcemz.net", 
                                  INTERNET_DEFAULT_HTTP_PORT, 0);

    // Create an HTTP Request handle.
    if (hConnect)
        hRequest = WinHttpOpenRequest(hConnect, L"GET", 
                                      L"", 
                                      NULL, WINHTTP_NO_REFERER, 
                                      WINHTTP_DEFAULT_ACCEPT_TYPES, 
                                      0);

    // Send a Request.
    if (hRequest)
        bResults = WinHttpSendRequest(hRequest, 
                                      WINHTTP_NO_ADDITIONAL_HEADERS, 
                                      0, WINHTTP_NO_REQUEST_DATA, 0, 
                                      0, 0);

    // End the request.
    if (bResults)
        bResults = WinHttpReceiveResponse(hRequest, NULL);

    // Continue to verify data until there is nothing left.
    if (bResults)
    {
        do
        {
            // Verify available data.
            dwSize = 0;
            if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
                printf("Error %u in WinHttpQueryDataAvailable.\n", 
                       GetLastError());
            
            // Allocate space for the buffer.
            pszOutBuffer = new char[dwSize+1];
            
            // Read the Data.
            ZeroMemory(pszOutBuffer, dwSize+1);

            if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, 
                                 dwSize, &dwDownloaded))
                printf("Error %u in WinHttpReadData.\n", GetLastError());
            else
                printf("%s\n", pszOutBuffer);

            // Free the memory allocated to the buffer.
            delete[] pszOutBuffer;
        } while (dwSize > 0);
    } 

    // Report errors.
    if (!bResults)
        printf("Error %d has occurred.\n", GetLastError());

    // Close open handles.
    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);
}