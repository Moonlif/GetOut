#pragma once
#include "stdafx.h"
// >> :
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <process.h>
#include <WinSock2.h>
#include <time.h>
#define g_pSocketmanager cSocketManager::GetInstance()

#define BUF_SIZE 100
#define HOSTIP "127.0.0.1"
#define IN_PLAYER1 1 << 0
#define IN_PLAYER2 1 << 1
#define NAME_SIZE 20
#define ONE_SECOND 1000
#define OUT_PLAYER1 1 << 4
#define OUT_PLAYER2 1 << 5
#define PORT_DATA 1234
#define PORT_CHAT 9090
#define PORT_CLIENT 10111
#define ROOM_NAME_SIZE 50
#define SEND_PER_SECOND 2


class cSocketManager
{
private:
	SINGLETONE(cSocketManager);

	WSADATA wsaData_CHAT, wsaData_DATA;
	SOCKET hSocket_CHAT, hSocket_DATA;
	SOCKADDR_IN ServAdr_CHAT, ServAdr_DATA;
	HANDLE hSndThread, hRcvThread, hDataThread;

	char name[NAME_SIZE] = "[DEFAULT]";
	char msg[BUF_SIZE];

	D3DXVECTOR3 prevPosition, nextPosition;
	clock_t stStart, stCurrent, stUpdateTime;
	float m_fT;

	SYNTHESIZE(int, nFlagNum, FlagNum);
public:
	void Setup_DATA();
	void Setup_CHAT();
	void Update_DATA();
	void Update();
	void Calc_Position();
	void Destroy();
	void UpdatePosition(float  x, float y, float z);
};

struct ST_PLAYER_POSITION
{
	char  szRoomName[50] = { 0, };	// << : Key
	int	  nFROM_SERVER;				// << : Server Flag
	int   nFROM_CLIENT;				// << :	Client Flag
	int	  nPlayerIndex;				// << : Player Index
	animationState eAnimState;		// << : Animation index
	float fX;
	float fY;
	float fZ;
	float fAngle;
	ST_PLAYER_POSITION() :nFROM_SERVER(0), nFROM_CLIENT(0), nPlayerIndex(0), eAnimState(ANIM_IDLE), fX(0.0f), fY(0.0f), fZ(0.0f), fAngle(0.0f) {};
	ST_PLAYER_POSITION(float x, float y, float z, float angle) { fX = x, fY = y, fZ = z, fAngle = angle; };
};

struct ST_ALL_DATA
{
	// << : Player Data
	char  szRoomName[50] = { 0, };	// << : Key
	int	  nFROM_SERVER;				// << : SERVER FLAG
	int   nFROM_CLIENT;				// << : CLIENT FLAG
	int	  nPlayerIndex;				// << : Current Player Index
	animationState eAnimState;		// << : Animation index
	float fX;
	float fY;
	float fZ;
	float fAngle;
	// << : Object Data
	float objectPosX[SWITCH_LASTNUM];	// << : PosX
	float objectPosY[SWITCH_LASTNUM];	// << : PosY
	float objectPosZ[SWITCH_LASTNUM];	// << : PosZ
	float objectRotX[SWITCH_LASTNUM];	// << : RotX
	float objectRotY[SWITCH_LASTNUM];	// << : RotY
	float objectRotZ[SWITCH_LASTNUM];	// << : RotZ
	StuffCode objectType[SWITCH_LASTNUM];	// << : objectType
	bool objectRunning[SWITCH_LASTNUM];		// << : Is Object Run?
};

struct ST_CHAT
{
	char ROOM_NAME[ROOM_NAME_SIZE] = { 0, };
	char TEXT[NAME_SIZE + BUF_SIZE] = { 0, };
};

enum FLAG
{
	FLAG_NONE = 1 << 0,
	FLAG_POSITION = 1 << 1,
	FLAG_OBJECT_DATA = 1 << 2,
	FLAG_ALL = 1 << 3,
};
