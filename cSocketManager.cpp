#include "cSocketManager.h"
#include "stdafx.h"

cSocketManager::cSocketManager()
{
}

cSocketManager::~cSocketManager()
{
}
void cSocketManager::Setup()
{
}

void cSocketManager::Setup_Chat()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)	/// 소켓 라이브러리 초기화
		ErrorHandling("WSAStartup() error ! ");

	sprintf(name, "[DEFAULT]");						/// 플레이어 이름 초기화
	hSockChat = socket(PF_INET, SOCK_STREAM, 0);	/// 채팅 소켓 할당

	memset(&ServAdr_CHAT, 0, sizeof(ServAdr_CHAT));
	ServAdr_CHAT.sin_family = AF_INET;
	ServAdr_CHAT.sin_addr.s_addr = inet_addr(HOSTIP);
	ServAdr_CHAT.sin_port = PORT_CHAT;

	if (connect(hSockChat, (SOCKADDR*)&ServAdr_CHAT, sizeof(ServAdr_CHAT)) == SOCKET_ERROR)
		ErrorHandling("connect() error");

	if (hSockChat != SOCKET_ERROR)		/// 소켓의 연결이 정상이라면
	{
		hSndThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&hSockChat, 0, NULL);	// 메시지 발신 스레드 함수
		hRcvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&hSockChat, 0, NULL);	// 메시지 수신 스레드 함수
	}

	WaitForSingleObject(hSndThread, INFINITE);	/// 스레드 종료 대기
	WaitForSingleObject(hRcvThread, INFINITE);	/// 스레드 종료 대기
}

void cSocketManager::Update()
{
}

void cSocketManager::Destroy()
{
	closesocket(hSockChat);
	WSACleanup();
}

unsigned WINAPI cSocketManager::SendMsg(void * arg)
{
	SOCKET hSock = *((SOCKET*)arg);
	char nameMsg[NAME_SIZE + BUF_SIZE];
	while (true)
	{
		fgets(msg, BUF_SIZE, stdin);	// << : g_pDataManager에서 데이터가 있을때 전송하도록 변경한다.
		if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))	// << : 스레드 함수를 종료하는 기준, DataManager에서 게임이 끝났음을 알리는 변수가 필요하다.
		{
			closesocket(hSock);
			exit(0);
		}
		sprintf(nameMsg, "%s %s", name, msg);		/// << : NAME + CHATDATA
		send(hSock, nameMsg, strlen(nameMsg), 0);	/// << : Chat Data 전송
	} /// << : while
	return 0;
}

unsigned cSocketManager::RecvMsg(void * arg)
{
	int hSock = *((SOCKET*)arg);
	char nameMsg[NAME_SIZE + BUF_SIZE];
	int strLen;
	while (true)
	{
		strLen = recv(hSock, nameMsg, NAME_SIZE + BUF_SIZE - 1, 0);
		if (strLen == -1) // << : connect Error
			return -1;
		nameMsg[strLen] = 0;
		fputs(nameMsg, stdout);
	} /// << : while
	return 0;
}

void cSocketManager::ErrorHandling(char * msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	//exit(1);
}


