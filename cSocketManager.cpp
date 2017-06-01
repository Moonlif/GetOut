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

	if (hSockChat != SOCKET_ERROR)		/// ������ ������ �����̶��
	{
		hSndThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&hSockChat, 0, NULL);	// �޽��� �߽� ������ �Լ�
		hRcvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&hSockChat, 0, NULL);	// �޽��� ���� ������ �Լ�
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

unsigned WINAPI cSocketManager::SendMsg(void * arg)
{
	SOCKET hSock = *((SOCKET*)arg);
	char nameMsg[NAME_SIZE + BUF_SIZE];
	while (true)
	{
		fgets(msg, BUF_SIZE, stdin);	// << : g_pDataManager���� �����Ͱ� ������ �����ϵ��� �����Ѵ�.
		if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))	// << : ������ �Լ��� �����ϴ� ����, DataManager���� ������ �������� �˸��� ������ �ʿ��ϴ�.
		{
			closesocket(hSock);
			exit(0);
		}
		sprintf(nameMsg, "%s %s", name, msg);		/// << : NAME + CHATDATA
		send(hSock, nameMsg, strlen(nameMsg), 0);	/// << : Chat Data ����
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


