#include "cSocketManager.h"
#include "stdafx.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

CRITICAL_SECTION cs;
unsigned int _stdcall PROCESS_CHAT_Send(LPVOID lpParam);
unsigned int _stdcall PROCESS_CHAT_Recv(LPVOID lpParam);
unsigned int _stdcall PROCESS_DATA(LPVOID lpParam);

cSocketManager::cSocketManager()
	: stUpdateTime(clock())
	, stStart(clock())
	, stCurrent(clock())
	, m_fT(0.0f)
{
	InitializeCriticalSection(&cs);		// << : Init CRITICAL SECTION (임계영역 초기화)
	prevPosition.x = 0;
	prevPosition.y = 0;
	prevPosition.z = 0;
	nextPosition.x = 0;
	nextPosition.y = 0;
	nextPosition.z = 0;
}

cSocketManager::~cSocketManager()
{
}

void cSocketManager::Setup_DATA()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData_DATA) != 0) /// Init Socket
		cout << "DATA WSAStartup() error!" << endl;

	hSocket_DATA = socket(PF_INET, SOCK_STREAM, 0);	/// 데이터 소켓 할당

	memset(&ServAdr_DATA, 0, sizeof(ServAdr_DATA));
	ServAdr_DATA.sin_family = AF_INET;
	ServAdr_DATA.sin_addr.s_addr = inet_addr(HOSTIP);
	ServAdr_DATA.sin_port = PORT_DATA;

	if (connect(hSocket_DATA, (SOCKADDR*)&ServAdr_DATA, sizeof(ServAdr_DATA)) == SOCKET_ERROR)
		cout << "DATA connect() error" << endl;

}

void cSocketManager::Setup_CHAT()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData_CHAT) != 0)	/// Init Socket
		cout << "CHAT WSAStartup() error!" << endl;

	//sprintf(name, "[DEFAULT]");						/// 플레이어 이름 초기화
	hSocket_CHAT = socket(PF_INET, SOCK_STREAM, 0);	/// 채팅 소켓 할당

	memset(&ServAdr_CHAT, 0, sizeof(ServAdr_CHAT));
	ServAdr_CHAT.sin_family = AF_INET;
	ServAdr_CHAT.sin_addr.s_addr = inet_addr(HOSTIP);
	ServAdr_CHAT.sin_port = PORT_CHAT;


	if (connect(hSocket_CHAT, (SOCKADDR*)&ServAdr_CHAT, sizeof(ServAdr_CHAT)) == SOCKET_ERROR)
		cout << "CHAT connect() error" << endl;


	if (hSocket_CHAT != SOCKET_ERROR)		/// 소켓의 연결이 정상이라면
	{
		hSndThread = (HANDLE)_beginthreadex(NULL, 0, (unsigned(__stdcall*)(void*))PROCESS_CHAT_Send, (void*)&hSocket_CHAT, 0, NULL);	// 메시지 발신 스레드 함수
		hRcvThread = (HANDLE)_beginthreadex(NULL, 0, (unsigned(__stdcall*)(void*))PROCESS_CHAT_Recv, (void*)&hSocket_CHAT, 0, NULL);	// 메시지 수신 스레드 함수
	}
}

void cSocketManager::Update_DATA()
{
	if (stUpdateTime + (ONE_SECOND / SEND_PER_SECOND) > clock()) return;

	stUpdateTime = clock();
	hDataThread = (HANDLE)_beginthreadex(NULL, 0, (unsigned(_stdcall*)(void*)) PROCESS_DATA, (void*)&hSocket_DATA, 0, NULL);
}

void cSocketManager::Update()
{
	Calc_Position();
}

void cSocketManager::Calc_Position()
{
	stCurrent = clock();
	m_fT = (float)(stCurrent - stStart) / (float)1000.0f;
	if (m_fT > 1) m_fT = 1;

	D3DXVECTOR3 interval = nextPosition - prevPosition;

	g_pData->m_vPosition2P = prevPosition + (interval * m_fT);
}

void cSocketManager::Destroy()
{
	WaitForSingleObject(hSndThread, INFINITE);	/// 스레드 종료 대기
	WaitForSingleObject(hRcvThread, INFINITE);	/// 스레드 종료 대기

	CloseHandle(hSndThread);
	CloseHandle(hRcvThread);

	closesocket(hSocket_CHAT);
	closesocket(hSocket_DATA);
	WSACleanup();
}

void cSocketManager::UpdatePosition(float  x, float y, float z)
{
	prevPosition = nextPosition;
	nextPosition = D3DXVECTOR3(x, y, z);
}


unsigned int _stdcall PROCESS_CHAT_Send(LPVOID lpParam)
{
	SOCKET hSock = *((SOCKET*)lpParam);
	char nameMsg[NAME_SIZE + BUF_SIZE];
	ST_CHAT SendData;
	while (true)
	{
		EnterCriticalSection(&cs);	// << : Begin CRITICAL SECTION 
		string Data = g_pData->GetText();
		sprintf_s(SendData.TEXT, "%s", Data.c_str(),NAME_SIZE + BUF_SIZE);
		if (Data.size() < 2) continue;
		//sText.resize(BUF_SIZE);
		LeaveCriticalSection(&cs);	// << : End CRITICAL SECTION
		send(hSock, (char*)&SendData, sizeof(ST_CHAT), 0);
	}
	return 0;
}

unsigned int _stdcall PROCESS_CHAT_Recv(LPVOID lpParam)
{
	SOCKET hSock = *((SOCKET*)lpParam);
	ST_CHAT RecvData;
	int strLen;
	while (true)
	{
		strLen = recv(hSock, (char*)&RecvData, sizeof(ST_CHAT), 0);
		if (strLen == -1 || strLen == 0) // << : connect Error
			continue;

		string Output(RecvData.TEXT);
		g_pData->m_listChat_RECV.push_back(Output);

		fputs(RecvData.TEXT, stdout);
	} /// << : while
	return 0;
}

unsigned int _stdcall PROCESS_DATA(LPVOID lpParam)
{
	SOCKET hSocket = socket(PF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(HOSTIP);
	addr.sin_port = PORT_DATA;

	if (connect(hSocket, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		cout << "DATA connect Error()" << endl;
	}
	
	ST_PLAYER_POSITION SendData;

	SendData.fAngle = g_pData->m_vRotation1P;
	SendData.fX = g_pData->m_vPosition1P.x;
	SendData.fY = g_pData->m_vPosition1P.y;
	SendData.fZ = g_pData->m_vPosition1P.z;
	SendData.eAnimState = g_pData->m_eAnimState1P;

	if(g_pData->m_nPlayerNum1P == 1)
		SendData.nPlayerIndex = SendData.nPlayerIndex | OUT_PLAYER1;
	else if(g_pData->m_nPlayerNum1P == 2)
		SendData.nPlayerIndex = SendData.nPlayerIndex | OUT_PLAYER2;

	SendData.nFROM_CLIENT = 0;
	SendData.nFROM_SERVER = 0;
	sprintf_s(SendData.szRoomName, "%s", "DEFAULT", 7);
	
	send(hSocket, (char*)&SendData, sizeof(ST_PLAYER_POSITION), 0);

	ST_PLAYER_POSITION RecvData;
	recv(hSocket, (char*)&RecvData, sizeof(ST_PLAYER_POSITION), 0);

	if (RecvData.nPlayerIndex & IN_PLAYER1)
		g_pData->m_nPlayerNum2P = 1;

	if(RecvData.nPlayerIndex & IN_PLAYER2)
		g_pData->m_nPlayerNum2P = 2;

	// << : CRITICAL SECTION ?
	g_pSocketmanager->stStart = clock();
	g_pSocketmanager->UpdatePosition(RecvData.fX, RecvData.fY, RecvData.fZ);
	// << : CRITICAL SECTION ?
	return 0;
}