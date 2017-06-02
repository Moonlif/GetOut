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

	WSADATA wsaData;
	// >> : For Chat
	SOCKET hSockChat;
	SOCKADDR_IN ServAdr_CHAT;
	HANDLE hSndThread, hRcvThread;


	char name[NAME_SIZE] = "[DEFAULT]";
	char msg[BUF_SIZE];

public:
	void Setup();
	void Setup_Chat();
	void Update();
	void Destroy();

	void ErrorHandling(char * msg);

};
