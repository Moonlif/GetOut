#include "cSocketManager.h"
#include "stdafx.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

CRITICAL_SECTION cs;
unsigned int _stdcall PROCESS_CHAT_Send(LPVOID lpParam);
unsigned int _stdcall PROCESS_CHAT_Recv(LPVOID lpParam);
unsigned int _stdcall PROCESS_DATA(LPVOID lpParam);

cSocketManager::cSocketManager()
{
}

cSocketManager::~cSocketManager()
{
}

void cSocketManager::Setup_DATA()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData_DATA) != 0) /// Init Socket
		cout << "DATA WSAStartup() error!" << endl;
}

void cSocketManager::Setup_CHAT()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData_CHAT) != 0)	/// Init Socket
		cout << "CHAT WSAStartup() error!" << endl;

	//sprintf(name, "[DEFAULT]");						/// 플레이어 이름 초기화
	hSocket_CHAT = socket(PF_INET, SOCK_STREAM, 0);	/// 채팅 소켓 할당

	memset(&ServAdr_CHAT, 0, sizeof(ServAdr_CHAT));
	ServAdr_CHAT.sin_family = AF_INET;
	ServAdr_CHAT.sin_addr.s_addr = inet_addr(HOSTIP);
	ServAdr_CHAT.sin_port = PORT_CHAT;


	if (connect(hSocket_CHAT, (SOCKADDR*)&ServAdr_CHAT, sizeof(ServAdr_CHAT)) == SOCKET_ERROR)
		cout << "CHAT connect() error" << endl;

	InitializeCriticalSection(&cs);		// << : Init CRITICAL SECTION (임계영역 초기화)

	if (hSocket_CHAT != SOCKET_ERROR)		/// 소켓의 연결이 정상이라면
	{
		hSndThread = (HANDLE)_beginthreadex(NULL, 0, (unsigned(__stdcall*)(void*))PROCESS_CHAT_Send, (void*)&hSocket_CHAT, 0, NULL);	// 메시지 발신 스레드 함수
		hRcvThread = (HANDLE)_beginthreadex(NULL, 0, (unsigned(__stdcall*)(void*))PROCESS_CHAT_Recv, (void*)&hSocket_CHAT, 0, NULL);	// 메시지 수신 스레드 함수
	}
}

void cSocketManager::Update_DATA()
{
}

void cSocketManager::Update()
{
}

void cSocketManager::Destroy()
{
	WaitForSingleObject(hSndThread, INFINITE);	/// 스레드 종료 대기
	WaitForSingleObject(hRcvThread, INFINITE);	/// 스레드 종료 대기

	CloseHandle(hSndThread);
	CloseHandle(hRcvThread);

	closesocket(hSocket_CHAT);
	closesocket(hSocket_DATA);
	WSACleanup();
}


unsigned int _stdcall PROCESS_CHAT_Send(LPVOID lpParam)
{
	SOCKET hSock = *((SOCKET*)lpParam);
	char nameMsg[NAME_SIZE + BUF_SIZE];
	while (true)
	{
		EnterCriticalSection(&cs);	// << : Begin CRITICAL SECTION 
		string sText = g_pData->GetText();
		if (sText.size() < 2) continue;
		//sText.resize(BUF_SIZE);
		sprintf_s(nameMsg, "%s", sText.c_str(), NAME_SIZE + BUF_SIZE);
		LeaveCriticalSection(&cs);	// << : End CRITICAL SECTION

		send(hSock, nameMsg, strlen(nameMsg), 0);
	}
	return 0;
}

unsigned int _stdcall PROCESS_CHAT_Recv(LPVOID lpParam)
{
	int hSock = *((SOCKET*)lpParam);
	char nameMsg[NAME_SIZE + BUF_SIZE];
	int strLen;
	while (true)
	{
		strLen = recv(hSock, nameMsg, NAME_SIZE + BUF_SIZE - 1, 0);
		if (strLen == -1) // << : connect Error
			return -1;

		EnterCriticalSection(&cs);	// << : Begin CRITICAL SECTION
		nameMsg[strLen] = 0;
		string Output(nameMsg);
		g_pData->m_listChat_RECV.push_back(Output);
		LeaveCriticalSection(&cs);	// << : End CRITICAL SECTION

		fputs(nameMsg, stdout);
	} /// << : while
	return 0;
}

unsigned int _stdcall PROCESS_DATA(LPVOID lpParam)
{

}