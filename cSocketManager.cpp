#include "cSocketManager.h"
#include "stdafx.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

CRITICAL_SECTION cs;
CRITICAL_SECTION cs2;
unsigned int _stdcall SEND_CHAT(LPVOID lpParam);
unsigned int _stdcall RECV_CHAT(LPVOID lpParam);
// << : ���ε� ������ ���� Ŭ���̾�Ʈ�� ����� �������� ���߽��ϴ�.
unsigned int _stdcall SEND_DATA_TO_SERVER(LPVOID lpParam);
unsigned int _stdcall RECV_DATA_FROM_SERVER(LPVOID lpParam);
unsigned int _stdcall SEND_DATA_TO_CLIENT(LPVOID lpParam);
unsigned int _stdcall RECV_DATA_FROM_CLIENT(LPVOID lpParam);
// << : ���� ���� ���
unsigned int _stdcall PROCESS_DATA(LPVOID lpParam);

// << : �и��� �Լ���
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
	InitializeCriticalSection(&cs);		// << : Init CRITICAL SECTION (�Ӱ迵�� �ʱ�ȭ)
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

	hSocket_CHAT = socket(PF_INET, SOCK_STREAM, 0);		/// ä�� ���� �Ҵ�
	clock_t prevTime = clock();

	memset(&ServAdr_CHAT, 0, sizeof(ServAdr_CHAT));
	ServAdr_CHAT.sin_family = AF_INET;
	ServAdr_CHAT.sin_addr.s_addr = inet_addr(HOSTIP);
	ServAdr_CHAT.sin_port = PORT_CHAT_SERVER;

	int result = connect(hSocket_CHAT, (SOCKADDR*)&ServAdr_CHAT, sizeof(ServAdr_CHAT));

	/* ���ῡ �����ߴٸ� 2�ʸ��� �ٽ� �翬���� �õ��մϴ�. */
	while (result != SOCKET_ERROR)
	{
		if (prevTime + (ONE_SECOND * 2) > clock()) continue;
		prevTime = clock();
		cout << "CHAT ������ �翬�� �մϴ�" << endl;
		result = connect(hSocket_CHAT, (SOCKADDR*)&ServAdr_CHAT, sizeof(ServAdr_CHAT));
	}

	/* ������ ������ �����̶�� �����带 ���۽�ŵ�ϴ�. */
	if (hSocket_CHAT != SOCKET_ERROR)
	{
		hChatSend = (HANDLE)_beginthreadex(NULL, 0, (unsigned(__stdcall*)(void*))SEND_CHAT, (void*)&hSocket_CHAT, 0, NULL);	// �޽��� �߽� ������ �Լ�
		hChatRecv = (HANDLE)_beginthreadex(NULL, 0, (unsigned(__stdcall*)(void*))RECV_CHAT, (void*)&hSocket_CHAT, 0, NULL);	// �޽��� ���� ������ �Լ�
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
	WaitForSingleObject(hChatSend, INFINITE);	/// ������ ���� ���
	WaitForSingleObject(hChatRecv, INFINITE);	/// ������ ���� ���

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
	/* ���ῡ �����ߴٸ� 2�ʸ��� �ٽ� �翬���� �õ��մϴ�. */
	while (result == SOCKET_ERROR)
	{
		if (prevTime + (ONE_SECOND * 2) > clock()) continue;
		prevTime = clock();
		cout << "������ ���� ��õ���" << endl;
		result = connect(hSocket, (SOCKADDR*)&addr, sizeof(addr));
	}

	/* � �����͸� ������ ���� �˷��ݴϴ�. �׵� �ش��ϴ� �����͸� �����մϴ�. */
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
		cout << "��ǥ ����" << endl;
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

		switch (nFlag.eFlag)	// << : g_pDataManager�� �״�� �־��ش� ?
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
	/* ���ῡ �����ߴٸ� 2�ʸ��� �ٽ� �翬���� �õ��մϴ�. */
	while (result == SOCKET_ERROR)
	{
		if (prevTime + (ONE_SECOND * 2) > clock()) continue;
		prevTime = clock();
		cout << "������ ���� ��õ���" << endl;
		result = connect(hSocket, (SOCKADDR*)&addr, sizeof(addr));
	}

	/* � �����͸� ������ ���� �˷��ݴϴ�. �׵� �ش��ϴ� �����͸� �����մϴ�. */
	ST_FLAG stFlag;
	while (true)
	{
		if (prevTime + (ONE_SECOND - OVERHEAD) > clock()) continue;
		prevTime = clock();
		stFlag.eFlag = g_pSocketmanager->GetFlagNum();	// << : �̱��濡�� �÷��׸� �޾ƿɴϴ�.

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
	cout << "�������� �÷��̾� ";
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
		cout << "����" << " ";
	}

	cout << "X��ǥ : " << stRecv.fX << " ";
	cout << "Y��ǥ : " << stRecv.fY << " ";
	cout << "Z��ǥ : " << stRecv.fZ << " ";
	cout << "Angle : " << stRecv.fAngle << endl;
}
