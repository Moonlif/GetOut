#include "cSocketManager.h"
#include "stdafx.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

CRITICAL_SECTION cs;
CRITICAL_SECTION cs2;
unsigned int _stdcall SEND_CHAT(LPVOID lpParam);
unsigned int _stdcall RECV_CHAT(LPVOID lpParam);
unsigned int _stdcall INTERECT_CLIENT(LPVOID lpParam);
unsigned int _stdcall SEND_REQUEST_SERVER(LPVOID lpParam);
unsigned int _stdcall RECV_REQUEST_SERVER(LPVOID lpParam);

// << : 분리된 함수들
void ReceiveNetworkID(SOCKET* pSocket);
void ReceiveRoomName(SOCKET* pSocket);
void ReceivePosition(LPVOID lpParam);
void ReceiveAllData(SOCKET* pSocket);

void SendFlag(SOCKET* pSocket, ST_FLAG* pFlag);
void SendPosition(SOCKET* pSocket);

struct ST_ALL_DATA
{
	// << : 플레이어 데이터
	float manX;
	float manY;
	float manZ;
	float manAngle;
	int manAnim;
	int manItem[25];

	float womanX;
	float womanY;
	float womanZ;
	float womanAngle;
	int womanAnim;
	int womanItem[25];

	// << : 맵 데이터
	float mapX[30];
	float mapY[30];
	float mapZ[30];
	float mapRotX[30];
	float mapRotY[30];
	float mapRotZ[30];
	bool mapIsRunning[30];
}; 

cSocketManager::cSocketManager()
	: stUpdateTime(clock())
	, stStart(clock())
	, stCurrent(clock())
	, m_fT(0.0f)
	, nFlagNum(FLAG_NETWORK_ID)
	, prevRotation(0.0f)
	, nextRotation(0.0f)
	, InitServer(false)
	, nNetworkID(-1)
{
	InitializeCriticalSection(&cs);		// << : Init CRITICAL SECTION (임계영역 초기화)
	InitializeCriticalSection(&cs2);	// << : 2
	prevPosition.x = 0;
	prevPosition.y = 0;
	prevPosition.z = 0;
	nextPosition.x = 0;
	nextPosition.y = 0;
	nextPosition.z = 0;

	sprintf_s(HostIP, "%s", "127.0.0.1", 16);
}

cSocketManager::~cSocketManager()
{
}

/* T값을 이용하여 현재 좌표 , 회전값을 예측합니다. */
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

/* 모든 스레드를 종료하고 소켓을 닫습니다 */
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

/* IP를 얻어오는 부분 */
char * cSocketManager::GetIP()
{
	return HostIP;
}

/* 서버로부터 수신한 초기 데이터를 클라이언트에 적용합니다 */
void cSocketManager::InitClientData(ST_ALL_DATA stData)
{
	// << : 플레이어 정보 초기화
	ManPosition = D3DXVECTOR3(stData.manX, stData.manY, stData.manZ);
	WomanPosition = D3DXVECTOR3(stData.womanX, stData.womanY, stData.womanZ);
	ManRot = stData.manAngle;
	WomanRot = stData.womanAngle;

	for (int i = 0; i < INVENTORY_SIZE; ++i)
	{
		ManInventory[i] = (StuffCode)stData.manItem[i];
		WomanInventory[i] = (StuffCode)stData.womanItem[i];
	}

	// << : 맵 정보 초기화
	for (int i = 0; i < SWITCH_LASTNUM; ++i)
	{
		m_bStuffSwitch[i] = stData.mapIsRunning[i];
		m_vStuffPosition[i] = D3DXVECTOR3(stData.mapX[i], stData.mapY[i], stData.mapZ[i]);
		m_vStuffRotation[i] = D3DXVECTOR3(stData.mapRotX[i], stData.mapRotY[i], stData.mapRotZ[i]);
	}
}

/* IP를 설정하는 부분 */
void cSocketManager::SetIP(int First, int Second, int Third, int Fourth)
{
	if (First > 255 || Second > 255 || Third > 255 || Fourth > 255 ||
		First < 0 || Second < 0 || Third < 0 || Fourth < 0)
	{
		cout << "잘못된 IP 주소 입력" << endl;
		return;
	}
	char addrFirst[10] = { 0, };
	char addrSecond[10] = { 0, };
	char addrThird[10] = { 0, };
	char addrFourth[10] = { 0, };

	_itoa_s(First, addrFirst, 10);
	_itoa_s(Second, addrSecond, 10);
	_itoa_s(Third, addrThird, 10);
	_itoa_s(Fourth, addrFourth, 10);

	string szFullIP = string(addrFirst) + "." + string(addrSecond) + "." + string(addrThird) + "." + string(addrFourth);
	cout << szFullIP << endl;
}

/* 서버와 통신을 위한 스레드 동작 */
void cSocketManager::Setup_DATA()
{
	int nRet;
	clock_t prevTime = clock();
	nRet = WSAStartup(MAKEWORD(2, 2), &wsaData_DATA); /// Init Socket
	while (nRet != 0)
	{
		if (prevTime + (ONE_SECOND * 2) > clock()) continue;
		prevTime = clock();
		cout << "DATA WSAStartup() error!" << endl;
		nRet = WSAStartup(MAKEWORD(2, 2), &wsaData_DATA); /// Init Socket
	}
	hDataSend_Serv = (HANDLE)_beginthreadex(NULL, 0, (unsigned(_stdcall*)(void*))SEND_REQUEST_SERVER, NULL, 0, NULL);
	hDataRecv_Serv = (HANDLE)_beginthreadex(NULL, 0, (unsigned(_stdcall*)(void*))RECV_REQUEST_SERVER, NULL, 0, NULL);
}

/* 채팅 동작을 위한 소켓 초기화및 스레드 동작 */
void cSocketManager::Setup_CHAT()
{
	/* WSAStartup이 제대로 되지 않았다면 2초마다 한번씩 실행합니다. */
	int nRet;
	clock_t prevTime = clock();
	nRet = WSAStartup(MAKEWORD(2, 2), &wsaData_CHAT);
	while (nRet != 0)
	{
		if (prevTime + (ONE_SECOND * 2) > clock()) continue;
		prevTime = clock();
		nRet = WSAStartup(MAKEWORD(2, 2), &wsaData_CHAT);
		cout << "CHAT WSAStartup() Error!" << endl;
	}

	hSocket_CHAT = socket(PF_INET, SOCK_STREAM, 0);		/// 채팅 소켓 할당

	memset(&ServAdr_CHAT, 0, sizeof(ServAdr_CHAT));
	ServAdr_CHAT.sin_family = AF_INET;
	ServAdr_CHAT.sin_addr.s_addr = inet_addr(HostIP);
	ServAdr_CHAT.sin_port = PORT_CHAT_SERVER;

	bool bValid = true;
	setsockopt(hSocket_CHAT, SOL_SOCKET, SO_REUSEADDR, (const char *)&bValid, sizeof(bValid));

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

/* 싱글톤 업데이트 */
void cSocketManager::Update()
{
	if (GetAsyncKeyState(VK_NUMPAD5) & 0x0001)
		g_pSocketmanager->SetIP(192, 168, 255, 4);
	Calc_Position(); // < : 좌표를 보정해서 계산합니다.
	if (InitServer)
	{
		SetInitServer(false);
		// << : 서버로부터 호스트를 해라 라는 신호가 들어오면 스레드를 동작시킨다 ?
	}
}

/* 현재 좌표를 출발지로 , 수신한 좌표를 목적지로 설정 */
void cSocketManager::UpdatePosition(float  x, float y, float z)
{
	prevPosition = g_pData->m_vPosition2P;
	nextPosition = D3DXVECTOR3(x, y, z);
	stStart = clock();
}

/* 현재 회전값을 출발 회전값으로, 수신한 회전값을 목표 회전값으로 설정 */
void cSocketManager::UpdateRotation(float Rotate)
{
	prevRotation = g_pData->m_vRotation2P;
	nextRotation = Rotate;
}

/* 채팅을 전송하는 스레드 */
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
		LeaveCriticalSection(&cs);	// << : End CRITICAL SECTION
		send(hSock, (char*)&SendData, sizeof(ST_CHAT), 0);
	}
	return 0;
}

/* 채팅을 수신하는 스레드 */
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

/* 클라이언트 (2P)와 상호작용하는 스레드 */
unsigned int _stdcall INTERECT_CLIENT(LPVOID lpParam)
{
	return 0;
}

/* 서버로 요청을 전송하는 스레드 함수 */
unsigned int _stdcall SEND_REQUEST_SERVER(LPVOID lpParam)
{
	SOCKET hSocket = socket(PF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(g_pSocketmanager->GetIP());
	addr.sin_port = PORT_DATA_SERVER_OUT;

	clock_t prevTime = clock();
	int result = connect(hSocket, (SOCKADDR*)&addr, sizeof(addr));
	/* 연결에 실패했다면 2초마다 다시 재연결을 시도합니다. */
	while (result == SOCKET_ERROR)
	{
		if (prevTime + (ONE_SECOND * 2) > clock()) continue;
		prevTime = clock();
		cout << "SEND 스레드 연결 재시도중" << endl;
		result = connect(hSocket, (SOCKADDR*)&addr, sizeof(addr));
	}

	ST_FLAG stFlag;
	// >> : 맨처음 데이터를 받아올때 네트워크 아이디도 받아와야함
	while (true)
	{
		if (prevTime + (ONE_SECOND - OVERHEAD) > clock()) continue;
		prevTime = clock();

		SendFlag(&hSocket,&stFlag);

		switch (stFlag.eFlag)
		{
		case FLAG::FLAG_NONE:
			break;
		case FLAG::FLAG_NETWORK_ID:
			ReceiveNetworkID(&hSocket);
			break;
		case FLAG::FLAG_ROOM_NAME:
			ReceiveRoomName(&hSocket);
			break;
		case FLAG::FLAG_ALL_DATA:
			ReceiveAllData(&hSocket);
			break;
		case FLAG::FLAG_IP:
			break;
		case FLAG::FLAG_POSITION:
			ReceivePosition(&hSocket);
			break;
		case FLAG::FLAG_OBJECT_DATA:
			break;
		}
	}
	return 0;
}

/* 서버에서 요청을 수신하는 스레드 함수 */
unsigned int _stdcall RECV_REQUEST_SERVER(LPVOID lpParam)
{
	SOCKET hSocket = socket(PF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addr;
	int strLen;
	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(g_pSocketmanager->GetIP());
	addr.sin_port = PORT_DATA_SERVER_IN;

	clock_t prevTime = clock();
	int result = connect(hSocket, (SOCKADDR*)&addr, sizeof(addr));
	/* 연결에 실패했다면 2초마다 다시 재연결을 시도합니다. */
	while (result == SOCKET_ERROR)
	{
		if (prevTime + (ONE_SECOND * 2) > clock()) continue;
		prevTime = clock();
		cout << "RECV 스레드 연결 재시도중" << endl;
		result = connect(hSocket, (SOCKADDR*)&addr, sizeof(addr));
	}

	ST_FLAG stFlag;
	while (strLen = recv(hSocket, (char*)&stFlag, sizeof(ST_FLAG), 0) != 0)
	{
		stFlag.nNetworkID = g_pSocketmanager->GetNetworkID();
		if (strLen == -1) break;
		cout << stFlag.szRoomName << endl;
		cout << stFlag.eFlag << endl;
		cout << stFlag.nPlayerIndex << endl;

		switch (stFlag.eFlag)
		{
		case FLAG_NONE:
			break;
		case FLAG_IP:
			break;
		case FLAG_POSITION:
			SendPosition(&hSocket);
			break;
		case FLAG_OBJECT_DATA:
			break;
		}
	}

	return 0;
}

/* 네트워크 아이디 수신 */
void ReceiveNetworkID(SOCKET* pSocket)
{
	int nID;
	recv(*pSocket, (char*)&nID, sizeof(int), 0);
	g_pSocketmanager->SetNetworkID(nID);
	cout << "네트워크 아이디 " << nID << endl;
	g_pSocketmanager->SetFlagNum(FLAG::FLAG_ROOM_NAME);	// << : 네트워크 아이디 수신이 완료되면 방을 할당받아야 합니다.
}

/* 방이 연결 가능한지 확인 */
void ReceiveRoomName(SOCKET* pSocket)
{
	// << : 연결이 가능하다면 모든데이터를 수신하는 단계로 , 연결이 안된다면 방이름을 바꾸도록
	int IsOK = 0;
	recv(*pSocket, (char*)&IsOK, sizeof(int), 0);
	if (IsOK)
	{
		cout << "해당 방에 연결되었습니다." << endl;
		g_pSocketmanager->SetFlagNum(FLAG::FLAG_ALL_DATA);

	}
	else if (!IsOK)
	{
		cout << "해당 방 인원 초과" << endl;
		g_pSocketmanager->SetFlagNum(FLAG::FLAG_NONE);	// << : 클라이언트에서 방이름을 재설정 해줘야 합니다.
	}
};

/* 모든 데이터 수신 */
void ReceiveAllData(SOCKET* pSocket)
{
	ST_ALL_DATA Recv;
	recv(*pSocket, (char*)&Recv, sizeof(ST_ALL_DATA), 0);	// << : 데이터 수신
	g_pSocketmanager->InitClientData(Recv);					// << : 수신한 모든 데이터를 적용한다.
	g_pSocketmanager->SetFlagNum(FLAG::FLAG_POSITION);		// << : 좌표를 전송시켜보자
}

/* 좌표 수신 */
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

/* 서버에게 어떤 데이터를 원하는지 알려줍니다. */
void SendFlag(SOCKET* pSocket, ST_FLAG* pFlag)
{
	pFlag->eFlag = g_pSocketmanager->GetFlagNum();			// << : 싱글톤에서 플래그를 받아옵니다.
	pFlag->nNetworkID = g_pSocketmanager->GetNetworkID();	// << : 싱글톤에서 네트워크 아이디를 받아옵니다.
	pFlag->nPlayerIndex = g_pData->m_nPlayerNum1P;
	sprintf_s(pFlag->szRoomName, g_pSocketmanager->szRoomName, strlen(g_pSocketmanager->szRoomName));
	if(pFlag->eFlag != FLAG::FLAG_NONE)	// << : 요청할 내용이 없다면 전송하지 않습니다.
		send(*pSocket, (char*)pFlag, sizeof(ST_FLAG), 0);
}

/* 자신의 좌표를 서버에게 전송합니다 */
void SendPosition(SOCKET* pSocket)
{
	SOCKET hSocket = *pSocket;
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
}
