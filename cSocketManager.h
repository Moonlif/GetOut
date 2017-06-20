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
#define CLIENT_NUM 5
#define FLAG_MAN 1 << 4
#define FLAG_WOMAN 1 << 5
#define INVENTORY_SIZE 25
#define NAME_SIZE 20
#define ONE_SECOND 1000
#define OVERHEAD 100
#define PORT_DATA_SERVER_OUT 1234
#define PORT_DATA_SERVER_IN 1235
#define PORT_DATA_CLIENT 10111
#define PORT_CHAT_SERVER 9090
#define ROOM_NAME_SIZE 50
#define SEND_PER_SECOND 1

struct ST_ALL_DATA;
struct ST_OBJECT_DATA;
class cUIObject;
class cChat;
class Player;
#include "cUIButton.h"

class cSocketManager : public iButtonDelegate
{
private:
	SINGLETONE(cSocketManager);

	// << : 서버와 통신하기 위해 필요한 변수들입니다.
	WSADATA wsaData_CHAT, wsaData_DATA;
	SOCKET hSocket_CHAT, hSocket_DATA;
	SOCKADDR_IN ServAdr_CHAT, ServAdr_DATA, ClntAdr_DATA;
	HANDLE hChatSend, hChatRecv, hDataRecv_Serv, hDataSend_Serv;
	HANDLE hDataThread;
	char HostIP[16] = { 0, };

	// << : 좌표 계산을 위해 필요한 변수들
	D3DXVECTOR3 prevPosition, nextPosition;
	float prevRotation, nextRotation;
	clock_t stStart, stCurrent, stUpdateTime;
	float m_fT;

	// << : 현재 연결 상황을 저장할 변수
	SYNTHESIZE(int, nFlagNum, FlagNum);
	SYNTHESIZE(bool, InitServer, InitServer);
	SYNTHESIZE(int, nNetworkID, NetworkID);

	// << : 자신의 정보
	char szRoomName[ROOM_NAME_SIZE] = "TEST";
	char name[NAME_SIZE] = "[DEFAULT]";
	char msg[BUF_SIZE];

	// << : 수신한 데이터 버퍼
	D3DXVECTOR3 ManPosition;
	D3DXVECTOR3 WomanPosition;
	float ManRot;
	float WomanRot;
	StuffCode ManInventory[INVENTORY_SIZE];
	StuffCode WomanInventory[INVENTORY_SIZE];
	bool m_bStuffSwitch[SWITCH_LASTNUM];			//아이템일 경우 맵에 있는게 true
	D3DXVECTOR3 m_vStuffPosition[SWITCH_LASTNUM];
	D3DXVECTOR3 m_vStuffRotation[SWITCH_LASTNUM];

	bool bValve1;
	bool bValve2;
	int nFValve1Count;
	int nFValve2Count;
	int nBrickCount;

	// << : 초기 데이터 적용을 위한 포인터
	SYNTHESIZE(Player*, m_pPlMan, ManPlayer);
	SYNTHESIZE(Player*, m_pPlWoman, WomanPlayer);

	// << : 입력창을 렌더하기 위한 변수들
	LPD3DXSPRITE m_pSprite;
	cUIObject* m_pUIRoot;
	cChat*	m_pTextBox;

	// << : 서버가 동작중인지 확인하기 위한 변수
	SYNTHESIZE(bool, IsRun, ServerRun);

public:
	void Calc_Position();
	void Destroy();
	char* GetIP();
	char* GetRoomName();
	void InitClientData();
	void RecvClientData(ST_ALL_DATA stData);
	void RecvObjectData(ST_OBJECT_DATA stData);
	void Setup();
	void SetIP(int First, int Second, int Third, int Fourth);
	void SetIP(string szIP);
	void SetMyName(string szName);
	void SetRoomName(string szName);
	void Setup_DATA();
	void Setup_CHAT();
	void Update();
	void UpdatePosition(float  x, float y, float z);
	void UpdateRotation(float Rotate);
	void UpdateObjectData();

	void UIRender();

	virtual void OnClick(cUIButton* pSender) override;
};

enum FLAG
{
	FLAG_NONE = 1 << 0,
	FLAG_NETWORK_ID = 1 << 1,
	FLAG_ROOM_NAME = 1 << 2,
	FLAG_ALL_DATA = 1 << 3,
	FLAG_GENDER = 1 << 4,
	FLAG_POSITION = 1 << 5,
	FLAG_OBJECT_DATA = 1 << 6
};

struct ST_FLAG
{
	char szRoomName[50] = { 0, };	// << : key
	int nNetworkID;
	int nPlayerIndex;
	int eFlag;
};

struct ST_PLAYER_POSITION
{
	char  szRoomName[50] = { 0, };	// << : Key
	int	  nPlayerIndex;				// << : Player Index
	animationState eAnimState;		// << : Animation index
	float fX;
	float fY;
	float fZ;
	float fAngle;
	ST_PLAYER_POSITION() : nPlayerIndex(0), eAnimState(ANIM_IDLE), fX(0.0f), fY(0.0f), fZ(0.0f), fAngle(0.0f) {};
	ST_PLAYER_POSITION(float x, float y, float z, float angle) { fX = x, fY = y, fZ = z, fAngle = angle; };
};

struct ST_OBJECT_DATA
{
	float mapX[SWITCH_LASTNUM];
	float mapY[SWITCH_LASTNUM];
	float mapZ[SWITCH_LASTNUM];
	float mapRotX[SWITCH_LASTNUM];
	float mapRotY[SWITCH_LASTNUM];
	float mapRotZ[SWITCH_LASTNUM];
	bool mapIsRunning[SWITCH_LASTNUM];

	bool bValve1;
	bool bValve2;
	int nFValve1Count;
	int nFValve2Count;
	int nBrickCount;
};

struct ST_CHAT
{
	char ROOM_NAME[ROOM_NAME_SIZE] = { 0, };
	char TEXT[NAME_SIZE + BUF_SIZE] = { 0, };
};

