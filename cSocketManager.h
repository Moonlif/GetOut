#pragma once
#include "stdafx.h"
// >> :
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <process.h>
#include <WinSock2.h>

#define g_pSocketmanager cSocketManager::GetInstance()

#define BUF_SIZE 100
#define NAME_SIZE
#define HOSTIP "127.0.0.1"
#define DATA_PORT 1234
#define CHAT_PORT 9090

class cSocketManager
{
private:
	SINGLETONE(cSocketManager);

	WSADATA wsaData;
	// >> : For Chat
	SOCKET hSockChat;
	SOCKADDR_IN ChatServAdr;
	HANDLE hSndThread, hRcvThread;
public:
	void Setup();
	void Setup_Chat();
	void SendData();			/// g_pDataManager���� ��ǥ��, ����� �����ؼ� Send�Ѵ�.
	void Update();
	void Close_Socket();

	unsigned WINAPI SendMsg(void * arg); // << : ä�� Send ������ �Լ�
	unsigned WINAPI RecvMsg(void * arg); // << : ä�� Recv ������ �Լ�
};
