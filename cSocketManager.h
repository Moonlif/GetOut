#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <WinSock2.h>

#define g_pSocketmanager cSocketManager::GetInstance() //
#define HOSTIP "127.0.0.1"
#define PORTNUM 1234
#define RECEIVETICK 500
#define SENDTICK 500
class cSocketManager
{
private:
	SINGLETONE(cSocketManager);

	DWORD	dwSendTick;
	DWORD	dwReceiveTick;
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;

public:
	void Setup();
	void SendData();			/// g_pDataManager에서 좌표값, 등등을 조합해서 Send한다.
	void Update();
	void Close_Socket();
};
