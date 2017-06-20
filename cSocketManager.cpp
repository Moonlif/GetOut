#include "cSocketManager.h"
#include "stdafx.h"
#include "cUIObject.h"
#include "cUIButton.h"
#include "cChat.h"
#include "Player.h"

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
int ReceiveRoomName(SOCKET* pSocket);
void ReceiveGender(SOCKET* pSocket);
void ReceivePosition(SOCKET* pSocket);
void ReceiveAllData(SOCKET* pSocket);
void ReceiveObjectData(SOCKET* pSocket);

void SendFlag(SOCKET* pSocket, FLAG eFlag);
void SendNetworkID(SOCKET* pSocket, int ID, bool* bConnected);
void SendGender(SOCKET* pSocket);
void SendPosition(SOCKET* pSocket);
void SendObjectData(SOCKET* pSocket);

struct ST_ALL_DATA
{
	// << : 플레이어 데이터
	float manX;
	float manY;
	float manZ;
	float manAngle;
	int manAnim;
	int manItem[INVENTORY_SIZE];

	float womanX;
	float womanY;
	float womanZ;
	float womanAngle;
	int womanAnim;
	int womanItem[INVENTORY_SIZE];

	// << : 맵 데이터
	float mapX[SWITCH_LASTNUM];
	float mapY[SWITCH_LASTNUM];
	float mapZ[SWITCH_LASTNUM];
	float mapRotX[SWITCH_LASTNUM];
	float mapRotY[SWITCH_LASTNUM];
	float mapRotZ[SWITCH_LASTNUM];
	bool mapIsRunning[SWITCH_LASTNUM];

	// << : 벨브 데이터
	bool bValve1;
	bool bValve2;
	int nFValve1Count;
	int nFValve2Count;
	int nBrickCount;

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
	, m_pTextBox(NULL)
	, m_pPlMan(NULL)
	, m_pPlWoman(NULL)
	, IsRun(false)
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

void cSocketManager::AddFlag(FLAG eFlag)
{
	nFlagNum = nFlagNum | eFlag;
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
	SAFE_DELETE(m_pTextBox);
	SAFE_RELEASE(m_pSprite);

	hChatSend, hChatRecv, hDataRecv_Serv, hDataSend_Serv;
	CloseHandle(hChatSend);
	CloseHandle(hChatRecv);
	CloseHandle(hDataRecv_Serv);
	CloseHandle(hDataSend_Serv);

	closesocket(hSocket_CHAT);
	closesocket(hSocket_DATA);
	WSACleanup();
}

/* IP를 얻어오는 부분 */
char * cSocketManager::GetIP()
{
	return HostIP;
}

char * cSocketManager::GetRoomName()
{
	return szRoomName;
}

/* 게임 시작시 다른 클래스들 초기화 */
void cSocketManager::InitClientData()
{
	/* 남자 정보 로딩 상황 */
	if (g_pData->m_nPlayerNum1P == 1 && m_pPlMan)
	{
		m_pPlMan->SetPosition(ManPosition);
		m_pPlMan->SetRotation(ManRot);
		for (int i = 0; i < INVENTORY_SIZE; ++i)
			g_pData->m_arrLoadInvenItem[i] = ManInventory[i];
		g_pData->SetIsLoadItem(true);
	}

	/* 여자 정보 로딩 상황 */
	else if (g_pData->m_nPlayerNum1P == 2 && m_pPlWoman)
	{
		m_pPlWoman->SetPosition(WomanPosition);
		m_pPlWoman->SetRotation(WomanRot);
		for (int i = 0; i < INVENTORY_SIZE; ++i)
			g_pData->m_arrLoadInvenItem[i] = WomanInventory[i];
		g_pData->SetIsLoadItem(true);
	}

	/* 맵 정보 로딩 */
	for (int i = 0; i < SWITCH_LASTNUM; ++i)
	{
		g_pData->m_bStuffSwitch[i] = m_bStuffSwitch[i];
		g_pData->m_vStuffPosition[i] = m_vStuffPosition[i];
		g_pData->m_vStuffRotation[i] = m_vStuffRotation[i];
	}

	/* 맵 상태 로딩*/
	g_pData->m_bValve1 = bValve1;
	g_pData->m_bValve2 = bValve2;
	g_pData->m_n2FValve1Count = nFValve1Count;
	g_pData->m_n2FValve2Count = nFValve2Count;
	g_pData->m_nBrickCount = nBrickCount;
}

/* 서버로부터 수신한 초기 데이터를 클라이언트에 적용합니다 */
void cSocketManager::RecvClientData(ST_ALL_DATA stData)
{
	// << : 플레이어 정보 초기화
	ManPosition = D3DXVECTOR3(stData.manX, stData.manY, stData.manZ);
	WomanPosition = D3DXVECTOR3(stData.womanX, stData.womanY, stData.womanZ);
	ManRot = stData.manAngle;
	WomanRot = stData.womanAngle;

	for (int i = 0; i < INVENTORY_SIZE; ++i)
	{
		ManInventory[i] = (StuffCode)stData.manItem[i];		// << : 남자 인벤토리
		WomanInventory[i] = (StuffCode)stData.womanItem[i];	// << : 여자 인벤토리
	}

	// << : 맵 정보 초기화
	for (int i = 0; i < SWITCH_LASTNUM; ++i)
	{
		m_bStuffSwitch[i] = stData.mapIsRunning[i];
		m_vStuffPosition[i] = D3DXVECTOR3(stData.mapX[i], stData.mapY[i], stData.mapZ[i]);
		m_vStuffRotation[i] = D3DXVECTOR3(stData.mapRotX[i], stData.mapRotY[i], stData.mapRotZ[i]);
	}

	// << : 맵상태 초기화
	bValve1 = stData.bValve1;
	bValve2 = stData.bValve2;
	nFValve1Count = stData.nFValve1Count;
	nFValve2Count = stData.nFValve2Count;
	nBrickCount = stData.nBrickCount;
}

void cSocketManager::RecvObjectData(ST_OBJECT_DATA stData)
{
	for (int i = 0; i < SWITCH_LASTNUM; ++i)
	{
		D3DXVECTOR3 Position = D3DXVECTOR3(stData.mapX[i], stData.mapY[i], stData.mapZ[i]);
		D3DXVECTOR3 Rotation = D3DXVECTOR3(stData.mapRotX[i], stData.mapRotY[i], stData.mapRotZ[i]);
		m_bStuffSwitch[i] = stData.mapIsRunning[i];
		m_vStuffPosition[i] = Position;
		m_vStuffRotation[i] = Rotation;
	}
	bValve1 = stData.bValve1;
	bValve2 = stData.bValve2;
	nFValve1Count = stData.nFValve1Count;
	nFValve2Count = stData.nFValve2Count;
	nBrickCount = stData.nBrickCount;
}

/* 버튼 등 초기설정 수행 */
void cSocketManager::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	m_pTextBox = new cChat;
	m_pTextBox->Setup(1, 200, 200, 50, 50);
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

	sprintf_s(HostIP, "%s", szFullIP.c_str(),sizeof(HostIP));

	Setup_CHAT();
	Setup_DATA();
}

void cSocketManager::SetIP(string szIP)
{
	string szFullIP = szIP;
	
	sprintf_s(HostIP, "%s", szFullIP.c_str(), sizeof(HostIP));

	Setup_CHAT();
	Setup_DATA();
}

void cSocketManager::SetMyName(string szName)
{
	string Name = szName;
	sprintf_s(name, "%s", Name.c_str(), sizeof(name));
}

void cSocketManager::SetRoomName(string szName)
{
	string Name = szName;
	sprintf_s(szRoomName, "%s", Name.c_str(), sizeof(szRoomName));
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

void cSocketManager::SubFlag(FLAG eFlag)
{
	if (nFlagNum & eFlag)
		nFlagNum = nFlagNum - eFlag;
}

/* 싱글톤 업데이트 */
void cSocketManager::Update()
{
	if (m_pTextBox)
		m_pTextBox->Update_ForSocket();
	Calc_Position(); // < : 좌표를 보정해서 계산합니다.
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

void cSocketManager::UpdateObjectData()
{
	for (int i = 0; i < SWITCH_LASTNUM; ++i)
	{
		g_pData->m_bStuffSwitch[i] = m_bStuffSwitch[i];
		g_pData->m_vStuffPosition[i] = m_vStuffPosition[i];
	}
}

void cSocketManager::UIRender()
{
	if (m_pTextBox)
		m_pTextBox->Render(200, 200, 50, 50);
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

/* 클라이언트 (2P)와 상호작용하는 스레드 (미구현)*/
unsigned int _stdcall INTERECT_CLIENT(LPVOID lpParam)
{
	return 0;
}

/* 요청을 전송하는 스레드 */
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
	int nCnt = 0;
	/* 연결에 실패했다면 2초마다 다시 재연결을 시도합니다. */
	while (result == SOCKET_ERROR)
	{
		if (prevTime + (ONE_SECOND * 2) > clock()) continue;
		prevTime = clock();
		cout << "SEND 스레드 연결 재시도중" << endl;
		result = connect(hSocket, (SOCKADDR*)&addr, sizeof(addr));
		nCnt++;
		if (nCnt > 5) return 0;	// << : 5번 이상 시도하면 함수 꺼버림
	}

	g_pSocketmanager->SetServerRun(true);
	ST_FLAG stFlag;
	FLAG eFlag = FLAG::FLAG_NONE;
	while (true)
	{
		eFlag = (FLAG)g_pSocketmanager->GetFlagNum();
		// << : 일정 간격마다 좌표를 전송한다. 단 특정 상황에서는 바로하도록 변경해야함
		if (eFlag == FLAG::FLAG_NONE)
		{
			Sleep(5);
			continue;
		}
		if (eFlag & FLAG::FLAG_NETWORK_ID)
		{
			// << : SendFlag 어떻게 보낼건지 설정해야함
			SendFlag(&hSocket, FLAG::FLAG_NETWORK_ID);
			ReceiveNetworkID(&hSocket);
			g_pSocketmanager->SubFlag(FLAG::FLAG_NETWORK_ID);
			g_pSocketmanager->AddFlag(FLAG::FLAG_ROOM_NAME);
			cout << "Send Network ID" << endl;
		}
		if (eFlag & FLAG::FLAG_ROOM_NAME)
		{
			int Result;
			SendFlag(&hSocket, FLAG::FLAG_ROOM_NAME);
			Result = ReceiveRoomName(&hSocket);
			if (Result)
			{
				g_pSocketmanager->SubFlag(FLAG::FLAG_ROOM_NAME);
				g_pSocketmanager->AddFlag(FLAG::FLAG_ALL_DATA);
			}
			else
			{
				g_pSocketmanager->SetFlagNum(FLAG::FLAG_NONE);	// << : 클라이언트에서 방이름을 재설정 해줘야 합니다.
				// << : F6으로 방이름을 변경하면 플래그를 변경시킨다 ?
			}
			cout << "Recv RoomName" << endl;
		}
		if (eFlag & FLAG::FLAG_ALL_DATA)
		{
			SendFlag(&hSocket, FLAG::FLAG_ALL_DATA);
			ReceiveAllData(&hSocket);
			g_pSocketmanager->SubFlag(FLAG::FLAG_ALL_DATA);
			cout << "Recv All Data" << endl;
		}
		if (eFlag & FLAG::FLAG_GENDER)
		{
			SendFlag(&hSocket, FLAG::FLAG_GENDER);
			SendGender(&hSocket);
			g_pSocketmanager->SubFlag(FLAG::FLAG_GENDER);
			cout << "Send Gender " << endl;
		}
		if (eFlag & FLAG::FLAG_POSITION && prevTime + ONE_SECOND < clock())
		{
			prevTime = clock();
			SendFlag(&hSocket, FLAG::FLAG_POSITION);
			SendPosition(&hSocket);
			cout << "Send Position" << endl;
		}
		if (eFlag & FLAG::FLAG_OBJECT_DATA)
		{
			SendFlag(&hSocket, FLAG::FLAG_OBJECT_DATA);
			SendObjectData(&hSocket);
			g_pSocketmanager->SubFlag(FLAG::FLAG_OBJECT_DATA);
		}
	}
	closesocket(hSocket);
	cout << "SEND 스레드가 종료되었습니다 " << endl;
	return 0;
}

/* 요청을 수신하는 스레드 */
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
	int nCnt = 0;
	/* 연결에 실패했다면 2초마다 다시 재연결을 시도합니다. */
	while (result == SOCKET_ERROR)
	{
		if (prevTime + (ONE_SECOND * 2) > clock()) continue;
		prevTime = clock();
		cout << "RECV 스레드 연결 재시도중" << endl;
		result = connect(hSocket, (SOCKADDR*)&addr, sizeof(addr));
		nCnt++;
		if (nCnt > 5) return 0;	// << : 5번 이상 시도시 스레드 꺼버림
	}

	g_pSocketmanager->SetServerRun(true);
	FLAG eFlag;
	bool isConnected = true;
	while (isConnected)
	{
		strLen = recv(hSocket, (char*)&eFlag, sizeof(FLAG), 0);
		if (strLen == -1) break;
		//cout << eFlag << endl;

		switch (eFlag)
		{
		case FLAG::FLAG_NONE:
			break;
		case FLAG::FLAG_NETWORK_ID:
			SendNetworkID(&hSocket, g_pSocketmanager->GetNetworkID(), &isConnected);
			break;
		case FLAG::FLAG_GENDER:
			ReceiveGender(&hSocket);
			break;
		case FLAG::FLAG_POSITION:
			ReceivePosition(&hSocket);
			break;
		case FLAG::FLAG_OBJECT_DATA:
			ReceiveObjectData(&hSocket);
			break;
		}
	}
	closesocket(hSocket);
	cout << "RECV스레드가 종료되었습니다 " << endl;
	return 0;
}

/* 네트워크 아이디 수신 */
void ReceiveNetworkID(SOCKET* pSocket)
{
	int nID;
	recv(*pSocket, (char*)&nID, sizeof(int), 0);
	g_pSocketmanager->SetNetworkID(nID);
	cout << "네트워크 아이디 " << nID << endl;
}

/* 방이 연결 가능한지 확인 */
int ReceiveRoomName(SOCKET* pSocket)
{
	// << : 연결이 가능하다면 모든데이터를 수신하는 단계로 , 연결이 안된다면 방이름을 바꾸도록
	int IsOK = 0;
	recv(*pSocket, (char*)&IsOK, sizeof(int), 0);
	if (IsOK)
		cout << "해당 방에 연결되었습니다." << endl;
	else if (!IsOK)
		cout << "해당 방 인원 초과" << endl;

	return IsOK;
};

/* 2P의 성별을 받아옵니다 */
void ReceiveGender(SOCKET* pSocket)
{
	int Gender;
	recv(*pSocket, (char*)&Gender, sizeof(int), 0);
	
	if (Gender == FLAG_MAN)
	{
		g_pData->m_nPlayerNum2P = 1;
		cout << "2P는 남자입니다 " << endl;
	}
	else if (Gender == FLAG_WOMAN)
	{
		g_pData->m_nPlayerNum2P = 2;
		cout << "2P는 여자입니다 " << endl;
	}
	else
	{
		g_pData->m_nPlayerNum2P = 0;
		cout << "2P는 없거나 고르지 않았습니다." << endl;
	}
}

/* 좌표 수신 */
void ReceivePosition(SOCKET* pSocket)
{
	ST_PLAYER_POSITION stRecv;
	recv(*pSocket, (char*)&stRecv, sizeof(ST_PLAYER_POSITION), 0);
	g_pSocketmanager->UpdatePosition(stRecv.fX, stRecv.fY, stRecv.fZ);
	g_pSocketmanager->UpdateRotation(stRecv.fAngle);
	g_pData->m_eAnimState2P = stRecv.eAnimState;

	cout << "애니메이션 : " << stRecv.eAnimState << endl;
}

/* 모든 데이터 수신 */
void ReceiveAllData(SOCKET* pSocket)
{
	ST_ALL_DATA Recv;
	recv(*pSocket, (char*)&Recv, sizeof(ST_ALL_DATA), 0);	// << : 데이터 수신
	g_pSocketmanager->RecvClientData(Recv);					// << : 수신한 모든 데이터를 적용한다.
	g_pSocketmanager->AddFlag(FLAG::FLAG_GENDER);		// << : 성별을 선택하고 상대의 성별을 확인해야함
	cout << "ReceiveAllData" << endl;
}

/* 자신의 성별을 서버에게 전송합니다 */
void SendGender(SOCKET* pSocket)
{
	ST_FLAG stSend;
	stSend.eFlag = FLAG::FLAG_GENDER;
	stSend.nNetworkID = g_pSocketmanager->GetNetworkID();
	if (g_pData->m_nPlayerNum1P == 1)
		stSend.nPlayerIndex = FLAG_MAN;
	else if (g_pData->m_nPlayerNum1P == 2)
		stSend.nPlayerIndex = FLAG_WOMAN;
	sprintf_s(stSend.szRoomName, g_pSocketmanager->szRoomName, strlen(g_pSocketmanager->szRoomName));
	send(*pSocket, (char*)&stSend, sizeof(ST_FLAG), 0);	// << : 자신이 선택한 성별을 전송합니다.
}

/* 서버에게 어떤 데이터를 원하는지 알려줍니다. */
void SendFlag(SOCKET* pSocket, FLAG eFlag)
{

	ST_FLAG stFlag;
	stFlag.eFlag = eFlag; // << : 플래그 파라미터로 받음
	stFlag.nNetworkID = g_pSocketmanager->GetNetworkID();	// << : 싱글톤에서 네트워크 아이디를 받아옵니다.
	stFlag.nPlayerIndex = g_pData->m_nPlayerNum1P;
	sprintf_s(stFlag.szRoomName, g_pSocketmanager->szRoomName, strlen(g_pSocketmanager->szRoomName));

	send(*pSocket, (char*)&stFlag, sizeof(ST_FLAG), 0);
}

/* 서버에게 자신의 NetworkID를 알려줍니다 */
void SendNetworkID(SOCKET* pSocket, int ID,bool* bConnected)
{
	int NetworkID = ID;
	int result = send(*pSocket, (char*)&NetworkID, sizeof(int), 0);
	if (result == -1) *bConnected = false;
}

/* 자신의 좌표를 서버에게 전송합니다 */
void SendPosition(SOCKET* pSocket)
{
	SOCKET hSocket = *pSocket;
	ST_PLAYER_POSITION stSend;
	if (g_pData->m_nPlayerNum1P == 1)
		stSend.nPlayerIndex = FLAG_MAN;
	else if (g_pData->m_nPlayerNum1P == 2)
		stSend.nPlayerIndex = FLAG_WOMAN;
	// << : 현재 방이름 복사
	sprintf_s(stSend.szRoomName, "%s", g_pSocketmanager->GetRoomName(), sizeof(stSend.szRoomName));
	stSend.fX = g_pData->m_vPosition1P.x;
	stSend.fY = g_pData->m_vPosition1P.y;
	stSend.fZ = g_pData->m_vPosition1P.z;
	stSend.fAngle = g_pData->m_vRotation1P;
	stSend.eAnimState = g_pData->m_eAnimState1P;
	send(hSocket, (char*)&stSend, sizeof(ST_PLAYER_POSITION), 0);
}

/* 물체와 맵의 정보를 수신 (구현 예정)*/
void ReceiveObjectData(SOCKET* pSocket)
{
	ST_OBJECT_DATA stData;
	int result = recv(*pSocket, (char*)&stData, sizeof(ST_OBJECT_DATA), 0);
	// << : 수신한 데이터를 버퍼에 적용후 클래스에 적용시킨다.
	// << : 맵정보만 담을 구조체가 하나 필요함
}

void SendObjectData(SOCKET* pSocket)
{
	ST_OBJECT_DATA stData;
	for (int i = 0; i < SWITCH_LASTNUM; ++i)
	{
		D3DXVECTOR3 Position = g_pData->m_vStuffPosition[i];
		D3DXVECTOR3 Rotation = g_pData->m_vStuffRotation[i];
		stData.mapX[i] = Position.x;
		stData.mapY[i] = Position.y;
		stData.mapZ[i] = Position.z;
		stData.mapRotX[i] = Rotation.x;
		stData.mapRotY[i] = Rotation.y;
		stData.mapRotZ[i] = Rotation.z;
		stData.mapIsRunning[i] = g_pData->m_bStuffSwitch[i];
	}
	send(*pSocket, (char*)&stData, sizeof(ST_OBJECT_DATA), 0);

}
