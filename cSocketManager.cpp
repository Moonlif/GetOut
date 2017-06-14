#include "cSocketManager.h"
#include "stdafx.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

CRITICAL_SECTION cs;
CRITICAL_SECTION cs2;
unsigned int _stdcall SEND_CHAT(LPVOID lpParam);
unsigned int _stdcall RECV_CHAT(LPVOID lpParam);
// << : 바인딩 문제로 현재 클라이언트간 통신이 구현되지 못했습니다.
unsigned int _stdcall SEND_DATA_TO_SERVER(LPVOID lpParam);
unsigned int _stdcall RECV_DATA_FROM_SERVER(LPVOID lpParam);
unsigned int _stdcall SEND_DATA_TO_CLIENT(LPVOID lpParam);
unsigned int _stdcall RECV_DATA_FROM_CLIENT(LPVOID lpParam);
// << : 기존 구현 방식
unsigned int _stdcall PROCESS_DATA(LPVOID lpParam);

// << : 분리된 함수들
void ReceivePosition(LPVOID lpParam);

cSocketManager::cSocketManager()
	: stUpdateTime(clock())
	, stStart(clock())
	, stCurrent(clock())
	, m_fT(0.0f)
	, nFlagNum(FLAG_POSITION)
	, prevRotation(0.0f)
	, nextRotation(0.0f)
{
	InitializeCriticalSection(&cs);		// << : Init CRITICAL SECTION (임계영역 초기화)
	InitializeCriticalSection(&cs2);	// << : 2
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

	hDataThread = (HANDLE)_beginthreadex(NULL, 0, (unsigned(_stdcall*)(void*)) PROCESS_DATA, (void*)&hSocket_DATA, 0, NULL);
}

void cSocketManager::Setup_CHAT()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData_CHAT) != 0)	
		cout << "CHAT WSAStartup() error!" << endl;

	hSocket_CHAT = socket(PF_INET, SOCK_STREAM, 0);		/// 채팅 소켓 할당
	clock_t prevTime = clock();

	memset(&ServAdr_CHAT, 0, sizeof(ServAdr_CHAT));
	ServAdr_CHAT.sin_family = AF_INET;
	ServAdr_CHAT.sin_addr.s_addr = inet_addr(HOSTIP);
	ServAdr_CHAT.sin_port = PORT_CHAT_SERVER;

	int result = connect(hSocket_CHAT, (SOCKADDR*)&ServAdr_CHAT, sizeof(ServAdr_CHAT));

	/* 연결에 실패했다면 2초마다 다시 재연결을 시도합니다. */
	while (result != SOCKET_ERROR)
	{
		if (prevTime + (ONE_SECOND * 2) > clock()) continue;
		prevTime = clock();
		cout << "CHAT 서버에 재연결 합니다" << endl;
		result = connect(hSocket_CHAT, (SOCKADDR*)&ServAdr_CHAT, sizeof(ServAdr_CHAT));
	}

	/* 소켓의 연결이 정상이라면 스레드를 동작시킵니다. */
	if (hSocket_CHAT != SOCKET_ERROR)
	{
		hChatSend = (HANDLE)_beginthreadex(NULL, 0, (unsigned(__stdcall*)(void*))SEND_CHAT, (void*)&hSocket_CHAT, 0, NULL);	// 메시지 발신 스레드 함수
		hChatRecv = (HANDLE)_beginthreadex(NULL, 0, (unsigned(__stdcall*)(void*))RECV_CHAT, (void*)&hSocket_CHAT, 0, NULL);	// 메시지 수신 스레드 함수
	}
}

void cSocketManager::Update_DATA()
{

	if (stUpdateTime + (ONE_SECOND / SEND_PER_SECOND) > clock()) return;

	stUpdateTime = clock();
}

void cSocketManager::Update()
{
	Calc_Position();
}

void cSocketManager::Calc_Position()
{
	stCurrent = clock();
	float Devide = stCurrent - stStart;
	if (Devide == 0) Devide = ONE_SECOND;
	m_fT = (float)(Devide) / (float)(ONE_SECOND);
	if (m_fT > 1) m_fT = 1;

	D3DXVECTOR3 posInterval = nextPosition - prevPosition;
	float rotInterval = nextRotation - prevRotation;
	
	g_pData->m_vPosition2P = prevPosition + (posInterval * m_fT);
	g_pData->m_vRotation2P = prevRotation + (rotInterval * m_fT);
}

void cSocketManager::Destroy()
{
	WaitForSingleObject(hChatSend, INFINITE);	/// 스레드 종료 대기
	WaitForSingleObject(hChatRecv, INFINITE);	/// 스레드 종료 대기

	CloseHandle(hChatSend);
	CloseHandle(hChatRecv);

	closesocket(hSocket_CHAT);
	closesocket(hSocket_DATA);
	WSACleanup();
}

void cSocketManager::UpdatePosition(float  x, float y, float z)
{
	prevPosition = nextPosition;
	nextPosition = D3DXVECTOR3(x, y, z);
	stStart = clock();
}

void cSocketManager::UpdateRotation(float Rotate)
{
	prevRotation = nextRotation;
	nextRotation = Rotate;
}

unsigned int _stdcall SEND_CHAT(LPVOID lpParam)
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

unsigned int _stdcall RECV_CHAT(LPVOID lpParam)
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
		WaitForSingleObject(g_hMutex_CHAT, INFINITE);	// << : Wait Mutex
		g_pData->m_listChat_RECV.push_back(Output);
		ReleaseMutex(g_hMutex_CHAT);					// << : ReleaseMutex

		fputs(RecvData.TEXT, stdout);
	} /// << : while
	return 0;
}

unsigned int _stdcall SEND_DATA_TO_SERVER(LPVOID lpParam)
{
	SOCKET hSocket = socket(PF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(HOSTIP);
	addr.sin_port = PORT_DATA_SERVER;

	clock_t prevTime = clock();
	int result = connect(hSocket, (SOCKADDR*)&addr, sizeof(addr));
	/* 연결에 실패했다면 2초마다 다시 재연결을 시도합니다. */
	while (result == SOCKET_ERROR)
	{
		if (prevTime + (ONE_SECOND * 2) > clock()) continue;
		prevTime = clock();
		cout << "스레드 연결 재시도중" << endl;
		result = connect(hSocket, (SOCKADDR*)&addr, sizeof(addr));
	}

	/* 어떤 데이터를 보낼지 먼저 알려줍니다. 그뒤 해당하는 데이터를 전송합니다. */
	while (true)
	{
		if (prevTime + (ONE_SECOND) > clock()) continue;
		prevTime = clock();

		ST_FLAG stFlag;
		stFlag.eFlag = FLAG_POSITION;
		stFlag.nPlayerIndex = g_pData->m_nPlayerNum1P;
		sprintf_s(stFlag.szRoomName, "DEFAULT", 7);
		send(hSocket, (char*)&stFlag, sizeof(ST_FLAG), 0);

		ST_PLAYER_POSITION st;
		st.nPlayerIndex = g_pData->m_nPlayerNum1P;
		st.fX = g_pData->m_vPosition1P.x;
		st.fY = g_pData->m_vPosition1P.y;
		st.fZ = g_pData->m_vPosition1P.z;
		st.fAngle = g_pData->m_vRotation1P;
		send(hSocket, (char*)&st, sizeof(ST_PLAYER_POSITION), 0);
		cout << "좌표 전송" << endl;
	}
}

unsigned int _stdcall RECV_DATA_FROM_SERVER(LPVOID lpParam)
{
	SOCKET hSocket = *(SOCKET*)lpParam;
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(HOSTIP);
	addr.sin_port = 1235;
	clock_t prevTime = clock();
	char szBuffer[BUF_SIZE * 10] = { 0, };
	int result = listen(hSocket, 5);

	int strLen, i;
	while ((strLen = recv(hSocket, (char*)&szBuffer, sizeof(ST_FLAG), 0)) != 0)
	{
		if (strLen == -1) break;
		ST_FLAG nFlag = *(ST_FLAG*)szBuffer;

		switch (nFlag.eFlag)	// << : g_pDataManager에 그대로 넣어준다 ?
		{
		case FLAG_NONE:
			break;
		case FLAG_IP:
			break;
		case FLAG_POSITION:
			cout << "FLAG_POSITION" << endl;
			break;
		case FLAG_OBJECT_DATA:
			break;
		case FLAG_ALL:
			break;
		}
	}

	return 0;
}

unsigned int _stdcall SEND_DATA_TO_CLIENT(LPVOID lpParam)
{
	return 0;
}

unsigned int _stdcall RECV_DATA_FROM_CLIENT(LPVOID lpParam)
{
	return 0;
}

unsigned int _stdcall PROCESS_DATA(LPVOID lpParam)
{
	SOCKET hSocket = socket(PF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(HOSTIP);
	addr.sin_port = PORT_DATA_SERVER;

	clock_t prevTime = clock();
	int result = connect(hSocket, (SOCKADDR*)&addr, sizeof(addr));
	/* 연결에 실패했다면 2초마다 다시 재연결을 시도합니다. */
	while (result == SOCKET_ERROR)
	{
		if (prevTime + (ONE_SECOND * 2) > clock()) continue;
		prevTime = clock();
		cout << "스레드 연결 재시도중" << endl;
		result = connect(hSocket, (SOCKADDR*)&addr, sizeof(addr));
	}

	/* 어떤 데이터를 보낼지 먼저 알려줍니다. 그뒤 해당하는 데이터를 전송합니다. */
	ST_FLAG stFlag;
	while (true)
	{
		if (prevTime + (ONE_SECOND - OVERHEAD) > clock()) continue;
		prevTime = clock();
		stFlag.eFlag = g_pSocketmanager->GetFlagNum();	// << : 싱글톤에서 플래그를 받아옵니다.

		stFlag.nPlayerIndex = g_pData->m_nPlayerNum1P;
		sprintf_s(stFlag.szRoomName, "DEFAULT", 7);
		send(hSocket, (char*)&stFlag, sizeof(ST_FLAG), 0);

		ST_PLAYER_POSITION stSend;
		if (g_pData->m_nPlayerNum1P == 1)
			stSend.nPlayerIndex = OUT_PLAYER1;
		else if (g_pData->m_nPlayerNum1P == 2)
			stSend.nPlayerIndex = OUT_PLAYER2;
		sprintf_s(stSend.szRoomName, "DEFAULT", 7);
		stSend.fX = g_pData->m_vPosition1P.x;
		stSend.fY = g_pData->m_vPosition1P.y;
		stSend.fZ = g_pData->m_vPosition1P.z;
		stSend.fAngle = g_pData->m_vRotation1P;
		send(hSocket, (char*)&stSend, sizeof(ST_PLAYER_POSITION), 0);

		switch (stFlag.eFlag)
		{
		case FLAG_POSITION:
			ReceivePosition(&hSocket);
			break;
		}
	}
	return 0;
}

void ReceivePosition(LPVOID lpParam)
{
	SOCKET hSocket = *(SOCKET*)lpParam;
	ST_PLAYER_POSITION stRecv;
	recv(hSocket, (char*)&stRecv, sizeof(ST_PLAYER_POSITION), 0);
	g_pSocketmanager->UpdatePosition(stRecv.fX, stRecv.fY, stRecv.fZ);
	g_pSocketmanager->UpdateRotation(stRecv.fAngle);
	cout << "접속중인 플레이어 ";
	if (stRecv.nPlayerIndex & IN_PLAYER1)
	{
		g_pData->m_nPlayerNum2P = 1;
		cout << "1P" << " ";
	}
	else if (stRecv.nPlayerIndex & IN_PLAYER2)
	{
		g_pData->m_nPlayerNum2P = 2;
		cout << "2P" << " ";
	}
	else
	{
		cout << "없음" << " ";
	}

	cout << "X좌표 : " << stRecv.fX << " ";
	cout << "Y좌표 : " << stRecv.fY << " ";
	cout << "Z좌표 : " << stRecv.fZ << " ";
	cout << "Angle : " << stRecv.fAngle << endl;
}
