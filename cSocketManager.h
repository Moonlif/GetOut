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

#define ROOM_NAME_SIZE 50
#define BUF_SIZE 100
#define NAME_SIZE 20
#define HOSTIP "122.45.137.187"
#define PORT_DATA 1234
#define PORT_CHAT 9090
#define ONE_SECOND 1000
#define DATA_INTERVAL 10

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

	DWORD	dwUpdateTime;
public:
	void Setup_DATA();
	void Setup_CHAT();
	void Update_DATA();
	void Update();
	void Destroy();
};

struct ST_PLAYER_POSITION
{
	char  szRoomName[50] = { 0, };
	int	  nFROM_SERVER;
	int   nFROM_CLIENT;
	int	  nPlayerIndex;
	float fX;
	float fY;
	float fZ;
	float fAngleX;
	float fAngleY;
	float fAngleZ;
	ST_PLAYER_POSITION() :nFROM_SERVER(0), nFROM_CLIENT(0), fX(0.0f), fY(0.0f), fZ(0.0f), fAngleX(0.0f), fAngleY(0.0f), fAngleZ(0.0f) {};
	ST_PLAYER_POSITION(float x, float y, float z, float angleX, float angleY, float angleZ) { fX = x, fY = y, fZ = z, fAngleX = angleX, fAngleY = angleY, fAngleZ = angleZ; };
};

struct ST_SOCKET_POSITION
{
	SOCKET pSocket;
	char szRoomName[50] = { 0, };
	int  nPlayerIndex;
};

struct ST_CHAT
{
	char ROOM_NAME[ROOM_NAME_SIZE] = { 0, };
	char TEXT[NAME_SIZE + BUF_SIZE] = { 0, };
};
