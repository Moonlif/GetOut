#include "cSocketManager.h"
#include "stdafx.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

CRITICAL_SECTION cs;
CRITICAL_SECTION cs2;
unsigned int _stdcall SEND_CHAT(LPVOID lpParam);
unsigned int _stdcall RECV_CHAT(LPVOID lpParam);
unsigned int _stdcall SEND_DATA_TO_SERVER(LPVOID lpParam);
unsigned int _stdcall RECV_DATA_FROM_SERVER(LPVOID lpParam);
unsigned int _stdcall SEND_DATA_TO_CLIENT(LPVOID lpParam);
unsigned int _stdcall RECV_DATA_FROM_CLIENT(LPVOID lpParam);

cSocketManager::cSocketManager()
	: stUpdateTime(clock())
	, stStart(clock())
	, stCurrent(clock())
	, m_fT(0.0f)
	, nFlagNum(-1)
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
		hSndThread = (HANDLE)_beginthreadex(NULL, 0, (unsigned(__stdcall*)(void*))SEND_CHAT, (void*)&hSocket_CHAT, 0, NULL);	// 메시지 발신 스레드 함수
		hRcvThread = (HANDLE)_beginthreadex(NULL, 0, (unsigned(__stdcall*)(void*))RECV_CHAT, (void*)&hSocket_CHAT, 0, NULL);	// 메시지 수신 스레드 함수
	}
}

void cSocketManager::Update_DATA()
{
	if (GetAsyncKeyState(VK_NUMPAD1) & 0x0001)
	{
		hDataThread = (HANDLE)_beginthreadex(NULL, 0, (unsigned(_stdcall*)(void*)) SEND_DATA_TO_SERVER, (void*)&hSocket_DATA, 0, NULL);
	}
	//if (stUpdateTime + (ONE_SECOND / SEND_PER_SECOND) > clock()) return;

	//stUpdateTime = clock();
	//hDataThread = (HANDLE)_beginthreadex(NULL, 0, (unsigned(_stdcall*)(void*)) PROCESS_DATA, (void*)&hSocket_DATA, 0, NULL);
}

void cSocketManager::Update()
{
	Calc_Position();
}

void cSocketManager::Calc_Position()
{
	stCurrent = clock();
	float Devide = stCurrent - stStart;
	if (Devide == 0) Devide = ONE_SECOND / SEND_PER_SECOND;
	m_fT = (float)(ONE_SECOND / SEND_PER_SECOND) / (float)(Devide);
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
	addr.sin_port = PORT_CLIENT;
	clock_t prevTime = clock();
	int result = connect(hSocket, (SOCKADDR*)&addr, sizeof(addr));
	while (result == SOCKET_ERROR)
	{
		if (prevTime + (ONE_SECOND * 2) > clock()) continue;	// << : 2초에 한번 연결합니다.
		prevTime = clock();
		cout << "DATA connect Error()" << endl;
		result = connect(hSocket, (SOCKADDR*)&addr, sizeof(addr));
	}

	while (true)
	{
		if (prevTime + (ONE_SECOND) > clock()) continue;
		prevTime = clock();

		// << : DataManager에서 플래그를 받아서 날리는 식으로 해야되나.
		int length = FLAG_POSITION;
		send(hSocket, (char*)&length, sizeof(int), 0);

		ST_PLAYER_POSITION st;
		st.fX = 1.0f;
		st.fY = 2.0f;
		st.fZ = 3.0f;
		EnterCriticalSection(&cs2);
		send(hSocket, (char*)&st, sizeof(ST_PLAYER_POSITION), 0);
		LeaveCriticalSection(&cs2);
		cout << "좌표 전송" << endl;
	}
}
unsigned int _stdcall RECV_DATA_FROM_SERVER(LPVOID lpParam)
{
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
