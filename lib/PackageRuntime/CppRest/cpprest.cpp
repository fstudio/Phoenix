#include <windows.h>
#include <winhttp.h>
#include "cpprest.h"
#include "resource.h"

#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>
#include <boost/foreach.hpp>
#include <boost/archive/iterators/transform_width.hpp>


#pragma comment(lib, "winhttp.lib")

/**
* Functions to give MultiByte strings to CryptoPP
*/
std::string to_mbstring(const std::wstring& input)
{
	return std::string(input.begin(), input.end());
}

std::wstring to_wstring(const std::string& input)
{
	return std::wstring(input.begin(), input.end());
}

std::wstring map2json(const std::map<std::wstring, std::wstring>& map) {
	// Write JSON
	boost::property_tree::ptree pt;
	for (auto& entry : map)
		pt.put(to_mbstring(entry.first), to_mbstring(entry.second));
	std::ostringstream buf;
	boost::property_tree::write_json(buf, pt, false);
	return to_wstring(buf.str());
}

std::map<std::wstring, std::wstring> json2map(const std::wstring& wszJSON) {
	// Read JSON
	boost::property_tree::ptree pt2;
	std::string szJSON(wszJSON.begin(), wszJSON.end());
	std::istringstream is(szJSON);

	std::map<std::wstring, std::wstring> result;

	try {
		boost::property_tree::read_json(is, pt2);
	
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt2)
		{
			result[to_wstring(v.first)] = to_wstring(v.second.data());
		}
	}
	catch (...){}

    return result;
}

CppRest::ApiResult CppRest::ApiRequest(CppRest::SWinHttpParameters& SParams,
                              bool bLoginUser)
{
	DWORD dwStatusCode = 0;
	DWORD dwLastStatus = 0;
	DWORD dwSize = sizeof(DWORD);
	BOOL  bResults = FALSE;
	BOOL  bDone = FALSE;

	CppRest::ApiResult result = CppRest::ApiResult::CPPREST_API_SERVERUNREACHABLE;

	DWORD dwProxyAuthScheme = 0;
	HINTERNET  hSession = NULL,
		hConnect = NULL,
		hRequest = NULL;

	LPSTR pszOutBuffer;
	DWORD dwDownloaded = 0;

	// Use WinHttpOpen to obtain a session handle.
	hSession = WinHttpOpen(L"CppRest SDK",
		WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS, 0);

	INTERNET_PORT nPort = (SParams.bUseSSL) ? INTERNET_DEFAULT_HTTPS_PORT : INTERNET_DEFAULT_HTTP_PORT;

	// Specify an HTTP server.
	if (hSession)
		hConnect = WinHttpConnect(hSession,
		SParams.wszServer.c_str(),
		nPort, 0);

	// Create an HTTP request handle.
	if (hConnect)
		hRequest = WinHttpOpenRequest(hConnect,
		SParams.wszVerb.c_str(),
		SParams.wszPath.c_str(),
		NULL,
		WINHTTP_NO_REFERER,
		WINHTTP_DEFAULT_ACCEPT_TYPES,
		(SParams.bUseSSL) ? WINHTTP_FLAG_SECURE : 0);

	// Add headers
	if (hRequest && SParams.mHeaders.size() != 0)
	{
		std::wstring wszHeaders(L"");
		for (std::map<std::wstring, std::wstring>::iterator it = SParams.mHeaders.begin(); it != SParams.mHeaders.end(); it++)
		{
			wszHeaders.append(it->first);
			wszHeaders.append(L": ");
			wszHeaders.append(it->second);
			if (std::next(it,1) != SParams.mHeaders.end())
				wszHeaders.append(L"\r\n");
		}
		
		bResults = WinHttpAddRequestHeaders(hRequest,
			wszHeaders.c_str(),
			(ULONG)-1L,
			WINHTTP_ADDREQ_FLAG_ADD);
	}

	// Continue to send a request until status code 
	// is not 401 or 407.
	if (hRequest == NULL)
		bDone = TRUE;

	std::string szJSONResponse("");

	while (!bDone)
	{
		// Send a request.
		bResults = WinHttpSendRequest(hRequest,
			WINHTTP_NO_ADDITIONAL_HEADERS,
			0,
			WINHTTP_NO_REQUEST_DATA,
			0,
			0,
			0);

		// End the request.
		if (bResults)
			bResults = WinHttpReceiveResponse(hRequest, NULL);

		// Resend the request in case of 
		// ERROR_WINHTTP_RESEND_REQUEST error.
		if (!bResults && GetLastError() == ERROR_WINHTTP_RESEND_REQUEST)
			continue;

		// Continue to verify data until there is nothing left.
		if (bResults)
		do
		{
			// Verify available data.
			dwSize = 0;
			if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
				printf("Error %u in WinHttpQueryDataAvailable.\n",
				GetLastError());

			// Allocate space for the buffer.
			pszOutBuffer = new char[dwSize + 1];
			if (!pszOutBuffer)
			{
				printf("Out of memory\n");
				dwSize = 0;
			}
			else
			{
				// Read the Data.
				ZeroMemory(pszOutBuffer, dwSize + 1);

				if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer,
					dwSize, &dwDownloaded))
					;// printf("Error %u in WinHttpReadData.\n", GetLastError());
				else
				{
					szJSONResponse.append(std::string(pszOutBuffer, dwDownloaded));
				}

				// Free the memory allocated to the buffer.
				delete[] pszOutBuffer;
			}
		} while (dwSize > 0);

		// Check the status code.
		if (bResults)
		{
			dwSize = sizeof(dwStatusCode);
			bResults = WinHttpQueryHeaders(hRequest,
				WINHTTP_QUERY_STATUS_CODE |
				WINHTTP_QUERY_FLAG_NUMBER,
				NULL,
				&dwStatusCode,
				&dwSize,
				NULL);
		}

		if (bResults)
		{
			switch (dwStatusCode)
			{
			case 200:
				// The resource was successfully retrieved.
				// You can use WinHttpReadData to read the 
				// contents of the server's response.
				//printf("The resource was successfully retrieved.\n");
				bDone = TRUE;
				result = CppRest::ApiResult::CPPREST_API_200;
				break;

			case 401:
				// The server requires authentication.			
				bDone = TRUE;
				result = CppRest::ApiResult::CPPREST_API_401;

				if (bLoginUser)
				{
                    CppRest::SWinHttpParameters SParams2(SParams);

					result = UserLogin(SParams2); //retrieve OAuthToken from token endpoint

					if (result == CppRest::ApiResult::CPPREST_API_200)
					{
						//Return fresh OAuth token to user for storage
                        SParams.mResponse[L"access_token"].assign(SParams2.mResponse[L"access_token"]);
						SParams.mHeaders[L"Authorization"].assign(L"Bearer ").append(SParams2.mResponse[L"access_token"]);

						result = CppRest::ApiRequest(SParams, false);
					}
				}
				break;
			case 403:
				result = CppRest::ApiResult::CPPREST_API_403;
				bDone = TRUE;
				break;
			case 407:
				// The proxy requires authentication.
				//printf("The proxy requires authentication.  Sending credentials...\n");

				// Obtain the supported and preferred schemes.
				/*bResults = WinHttpQueryAuthSchemes(hRequest,
					&dwSupportedSchemes,
					&dwFirstScheme,
					&dwTarget);

				// Set the credentials before resending the request.
				if (bResults)
					dwProxyAuthScheme = WINHTTP_AUTH_SCHEME_BASIC;

				// If the same credentials are requested twice, abort the
				// request.  For simplicity, this sample does not check 
				// for a repeated sequence of status codes.
				if (dwLastStatus == 407)*/
				bDone = TRUE;
				break;
			default:
				// The status code does not indicate success.
				//printf("Error. Status code %d returned.\n", dwStatusCode);
				bDone = TRUE;
			}
		}

		// Keep track of the last status code.
		dwLastStatus = dwStatusCode;

		// If there are any errors, break out of the loop.
		if (!bResults)
			bDone = TRUE;
	}

	// Report any errors.
	if (!bResults)
	{
		//DWORD dwLastError = GetLastError();
		//printf("Error %d has occurred.\n", dwLastError);
		result = CppRest::ApiResult::CPPREST_API_SERVERUNREACHABLE;
	}

	// Close any open handles.
	if (hRequest) WinHttpCloseHandle(hRequest);
	if (hConnect) WinHttpCloseHandle(hConnect);
	if (hSession) WinHttpCloseHandle(hSession);

	SParams.mResponse = json2map(to_wstring(szJSONResponse));

	return result;
}

std::wstring Credentials2Base64(const std::wstring& wszEmail, const std::wstring& wszPassword)
{
	std::wstring wszToEncode(wszEmail+std::wstring(L":")+wszPassword);

	std::stringstream os;
	typedef boost::archive::iterators::base64_from_binary<    // convert binary values ot base64 characters
		boost::archive::iterators::transform_width<   // retrieve 6 bit integers from a sequence of 8 bit bytes
					const char *,6,8
                    >
				>
				base64_text; // compose all the above operations in to a new iterator

	std::string szToEncode(wszToEncode.begin(), wszToEncode.end());
	std::copy(
		base64_text(szToEncode.c_str()),
		base64_text(szToEncode.c_str() + wszToEncode.size()),
		std::ostream_iterator<char>(os)
		);

	return std::wstring(to_wstring(os.str()));

}

void GetUserInput(HWND hWnd, int idInput, std::wstring& wszInputString)
{
	TCHAR lpszInput[256] = { 0 };
	WORD cchInput;

	// Get number of characters. 
	cchInput = (WORD)SendDlgItemMessage(hWnd,
		idInput,
		EM_LINELENGTH,
		(WPARAM)0,
		(LPARAM)0);

	// Put the number of characters into first word of buffer. 
	*((LPWORD)lpszInput) = cchInput; //Warning with unicode

	// Get the characters. 
	SendDlgItemMessage(hWnd,
		idInput,
		EM_GETLINE,
		(WPARAM)0,       // line 0 
		(LPARAM)lpszInput);

	// Null-terminate the string. 
	lpszInput[cchInput] = 0;
	wszInputString.assign(lpszInput);
}

INT_PTR CALLBACK LoginProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static CppRest::SWinHttpParameters* p_sParams;

	std::wstring wszPassword(L"");
	std::wstring wszEmail(L"");

	CppRest::ApiResult result = CppRest::ApiResult::CPPREST_API_SERVERUNREACHABLE;

	switch (message)
	{
	case WM_INITDIALOG:
		p_sParams = reinterpret_cast<CppRest::SWinHttpParameters*>(lParam);
		return 1;
	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
			SetWindowText(hDlg, L"Connecting...");
			ShowWindow(GetDlgItem(hDlg, IDC_ERROREMAIL), SW_HIDE);
			ShowWindow(GetDlgItem(hDlg, IDC_ERRORPASSWORD), SW_HIDE);

			GetUserInput(hDlg, IDC_PASSWORD, wszPassword);

			GetUserInput(hDlg, IDC_EMAIL, wszEmail);

            p_sParams->wszPath.assign(L"/oauthtoken");
            p_sParams->wszVerb.assign(L"POST");
            p_sParams->mHeaders[L"Authorization"].assign(std::wstring(L"Basic "))
                .append(Credentials2Base64(wszEmail, wszPassword));

            result = CppRest::ApiRequest(*p_sParams,false);

			SetWindowText(hDlg, L"Login");

			switch (result)
			{
			case CppRest::ApiResult::CPPREST_API_SERVERUNREACHABLE:
				MessageBox(hDlg, L"Can not reach server.\n\nPlease check your internet connection and retry.", L"Error", MB_OK);
				// Can not connect to the internet
				// User can connect to internet and retry
				// Or user must cancel to get out of login form
				return 0;
			case CppRest::ApiResult::CPPREST_API_401:
				ShowWindow(GetDlgItem(hDlg, IDC_ERRORPASSWORD), SW_SHOW);
				//Show error login here
				//Wrong email
				//Wrong password
				return 0;
			case CppRest::ApiResult::CPPREST_API_403:
				ShowWindow(GetDlgItem(hDlg, IDC_ERROREMAIL), SW_SHOW);
				//Show error login here
				//Forbidden access for user
				//EndDialog(hDlg, TRUE); //User banned ; but API should return OK and update with dummy license!
				return 0;
			case CppRest::ApiResult::CPPREST_API_200:
				EndDialog(hDlg, result);
				return 0;
			default:
				EndDialog(hDlg, result);
				return 0;
			}
		case IDCANCEL:
			EndDialog(hDlg, CppRest::ApiResult::CPPREST_USER_CANCEL);
			return 0;
		}
		return 0;
	}
	return FALSE;

	UNREFERENCED_PARAMETER(lParam);
}


/**
* Displays a form to gather user credentials
* Displays instructions to update the license manually
* returns OAuthToken
* returns true if login has been successful (200), false otherwise (cancel)
*/
CppRest::ApiResult UserLogin(CppRest::SWinHttpParameters& SParams)
{
	CppRest::ApiResult result = static_cast<CppRest::ApiResult>(
		DialogBoxParam(GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDD_DIALOG1),
			NULL,
			LoginProc,
			reinterpret_cast<LPARAM>(&SParams)
			)
		);

	return (result < 0) ? CppRest::ApiResult::CPPREST_USER_CANCEL : result; //-1 means DialogBox failed to display the form
}