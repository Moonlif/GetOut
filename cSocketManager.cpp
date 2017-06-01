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

CRITICAL_SECTION cs;
void cSocketManager::Setup_Chat()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)	/// ���� ���̺귯�� �ʱ�ȭ
		ErrorHandling("WSAStartup() error ! ");

	sprintf(name, "[DEFAULT]");						/// �÷��̾� �̸� �ʱ�ȭ
	hSockChat = socket(PF_INET, SOCK_STREAM, 0);	/// ä�� ���� �Ҵ�

	memset(&ServAdr_CHAT, 0, sizeof(ServAdr_CHAT));
	ServAdr_CHAT.sin_family = AF_INET;
	ServAdr_CHAT.sin_addr.s_addr = inet_addr(HOSTIP);
	ServAdr_CHAT.sin_port = PORT_CHAT;


	if (connect(hSockChat, (SOCKADDR*)&ServAdr_CHAT, sizeof(ServAdr_CHAT)) == SOCKET_ERROR)
		ErrorHandling("connect() error");

	InitializeCriticalSection(&cs);		// << : Init CRITICAL SECTION (�Ӱ迵�� �ʱ�ȭ)

	if (hSockChat != SOCKET_ERROR)		/// ������ ������ �����̶��
	{
		hSndThread = (HANDLE)_beginthreadex(NULL, 0, (unsigned(__stdcall *) (void*))SendMsg, (void*)&hSockChat, 0, NULL);	// �޽��� �߽� ������ �Լ�
		hRcvThread = (HANDLE)_beginthreadex(NULL, 0, (unsigned(__stdcall *) (void*))RecvMsg, (void*)&hSockChat, 0, NULL);	// �޽��� ���� ������ �Լ�
	}

	WaitForSingleObject(hSndThread, INFINITE);	/// ������ ���� ���
	WaitForSingleObject(hRcvThread, INFINITE);	/// ������ ���� ���
}

void cSocketManager::Update()
{
}

void cSocketManager::Destroy()
{
	closesocket(hSockChat);
	WSACleanup();
}


unsigned WINAPI SendMsg(LPVOID lpParam)
{
	SOCKET hSock = *((SOCKET*)lpParam);
	char nameMsg[NAME_SIZE + BUF_SIZE];
	while (true)
	{
		EnterCriticalSection(&cs);	// << : Begin CRITICAL SECTION 
		string sText = g_pData->GetText();
		sText.resize(BUF_SIZE);
		sprintf(nameMsg, "%s", sText.c_str());	
		LeaveCriticalSection(&cs);	// << : End CRITICAL SECTION

		if (sText.size() == 0) continue;
		send(hSock, nameMsg, strlen(nameMsg), 0);
	}
	return 0;
}

unsigned WINAPI RecvMsg(LPVOID lpParam)
{
	int hSock = *((SOCKET*)lpParam);
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


