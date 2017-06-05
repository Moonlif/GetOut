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
#define NAME_SIZE 20
#define HOSTIP "122.45.137.187"
#define PORT_DATA 1234
#define PORT_CHAT 9090

class cSocketManager
{
private:
	SINGLETONE(cSocketManager);

	WSADATA wsaData_CHAT, wsaData_DATA;
	// >> : For Chat
	SOCKET hSocket_CHAT, hSocket_DATA;
	SOCKADDR_IN ServAdr_CHAT, ServAdr_DATA;
	HANDLE hSndThread, hRcvThread, hDataThread;

	char name[NAME_SIZE] = "[DEFAULT]";
	char msg[BUF_SIZE];

public:
	void Setup_DATA();
	void Setup_CHAT();
	void Update_DATA();
	void Update();
	void Destroy();
};
