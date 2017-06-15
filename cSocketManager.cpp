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

// << : �и��� �Լ���
void ReceiveNetworkID(SOCKET* pSocket);
void ReceiveRoomName(SOCKET* pSocket);
void ReceivePosition(LPVOID lpParam);
void ReceiveAll(LPVOID lpParam);

void SendFlag(SOCKET* pSocket, ST_FLAG* pFlag);
void SendPosition(SOCKET* pSocket);

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

/* ȣ��Ʈ�� ���ٸ� �ڽ��� ȣ��Ʈ�� �˴ϴ�.*/
void cSocketManager::Setup_Host()
{
	// << :
	int nRet;
	nRet = WSAStartup(MAKEWORD(2, 2), &wsaData_HOST);

	hSocket_Serv = socket(PF_INET, SOCK_STREAM, 0);

	memset(&hostAdr, 0, sizeof(hostAdr));
	hostAdr.sin_family = AF_INET;
	hostAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	hostAdr.sin_port = PORT_DATA_CLIENT;
	bool bValid = 1;
	setsockopt(hSocket_Serv, SOL_SOCKET, SO_REUSEADDR, (const char *)&bValid, sizeof(bValid));
	if (bind(hSocket_Serv, (SOCKADDR*)&hostAdr, sizeof(hostAdr)) == SOCKET_ERROR)
		cout << "Server_HOST bind() Error" << endl;
	// >> : ���ε� ���� �������� ��


	// << : ���ε��� ������ �����忡 �����ϸ� ȣ���� ������ �˷��ش�.

	//if (listen(hSocket_Serv, CLIENT_NUM) == SOCKET_ERROR)
	//	cout << "Server_HOST listen() Error" << endl;

	//clntAdrSz = sizeof(clntAdr);
	//hSocket_Clnt = accept(hSocket_Serv, (SOCKADDR*)&clntAdr, &clntAdrSz);
	//if (hSocket_Clnt > 0)
	//	cout << " ȣ��Ʈ ������ ���� " << endl;

	// << : �̺κ��� ũ��Ƽ�� �������� ó���մϴ�.

	
	//while (true)
	//{
	//	clntAdrSz = sizeof(clntAdr);
	//	hSocket_Clnt = accept(hSocket_Serv, (SOCKADDR*)&clntAdr, &clntAdrSz);
	//	if (hSocket_Clnt > 0)
	//	{
	//		// << : �ٸ� Ŭ���̾�Ʈ�� �����ϸ� ������� ��ǥ�� ��� �ް� ó���Ѵ�.
	//	}
	//}
}

/* �̹� ȣ��Ʈ�� �ִٸ� �ش� ȣ��Ʈ�� �����ϴ� �Լ��Դϴ�. */
void cSocketManager::Connect_Client()
{
}

/* ������ ����� ���� ������ ���� */
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

/* ä�� ������ ���� ���� �ʱ�ȭ�� ������ ���� */
void cSocketManager::Setup_CHAT()
{
	/* WSAStartup�� ����� ���� �ʾҴٸ� 2�ʸ��� �ѹ��� �����մϴ�. */
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

	hSocket_CHAT = socket(PF_INET, SOCK_STREAM, 0);		/// ä�� ���� �Ҵ�

	memset(&ServAdr_CHAT, 0, sizeof(ServAdr_CHAT));
	ServAdr_CHAT.sin_family = AF_INET;
	ServAdr_CHAT.sin_addr.s_addr = inet_addr(HOSTIP);
	ServAdr_CHAT.sin_port = PORT_CHAT_SERVER;

	bool bValid = true;
	setsockopt(hSocket_CHAT, SOL_SOCKET, SO_REUSEADDR, (const char *)&bValid, sizeof(bValid));

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

void cSocketManager::Update()
{
	Calc_Position(); // < : ��ǥ�� �����ؼ� ����մϴ�.
	if (InitServer)
	{
		SetInitServer(false);
		// << : �����κ��� ȣ��Ʈ�� �ض� ��� ��ȣ�� ������ �����带 ���۽�Ų�� ?
	}
}

/* T���� �̿��Ͽ� ���� ��ǥ , ȸ������ �����մϴ�. */
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

/* ��� �����带 �����ϰ� ������ �ݽ��ϴ� */
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

/* ���� ��ǥ�� ������� , ������ ��ǥ�� �������� ���� */
void cSocketManager::UpdatePosition(float  x, float y, float z)
{
	prevPosition = g_pData->m_vPosition2P;
	nextPosition = D3DXVECTOR3(x, y, z);
	stStart = clock();
}

/* ���� ȸ������ ��� ȸ��������, ������ ȸ������ ��ǥ ȸ�������� ���� */
void cSocketManager::UpdateRotation(float Rotate)
{
	prevRotation = g_pData->m_vRotation2P;
	nextRotation = Rotate;
}

/* ä���� �����ϴ� ������ */
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

/* ä���� �����ϴ� ������ */
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

/* Ŭ���̾�Ʈ (2P)�� ��ȣ�ۿ��ϴ� ������ */
unsigned int _stdcall INTERECT_CLIENT(LPVOID lpParam)
{
	return 0;
}

unsigned int _stdcall SEND_REQUEST_SERVER(LPVOID lpParam)
{
	SOCKET hSocket = socket(PF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(HOSTIP);
	addr.sin_port = PORT_DATA_SERVER_OUT;

	clock_t prevTime = clock();
	int result = connect(hSocket, (SOCKADDR*)&addr, sizeof(addr));
	/* ���ῡ �����ߴٸ� 2�ʸ��� �ٽ� �翬���� �õ��մϴ�. */
	while (result == SOCKET_ERROR)
	{
		if (prevTime + (ONE_SECOND * 2) > clock()) continue;
		prevTime = clock();
		cout << "SEND ������ ���� ��õ���" << endl;
		result = connect(hSocket, (SOCKADDR*)&addr, sizeof(addr));
	}

	ST_FLAG stFlag;
	// >> : ��ó�� �����͸� �޾ƿö� ��Ʈ��ũ ���̵� �޾ƿ;���
	while (true)
	{
		if (prevTime + (ONE_SECOND - OVERHEAD) > clock()) continue;
		prevTime = clock();

		SendFlag(&hSocket,&stFlag);

		switch (stFlag.eFlag)
		{
		case FLAG_NONE:
			break;
		case FLAG_NETWORK_ID:
			ReceiveNetworkID(&hSocket);
			break;
		case FLAG_ROOM_NAME:
			ReceiveRoomName(&hSocket);
			break;
		case FLAG_ALL_DATA:
			break;
		case FLAG_IP:
			break;
		case FLAG_POSITION:
			ReceivePosition(&hSocket);
			break;
		case FLAG_OBJECT_DATA:
			break;
		case FLAG_ALL:
			break;

		}
	}
	return 0;
}

unsigned int _stdcall RECV_REQUEST_SERVER(LPVOID lpParam)
{
	SOCKET hSocket = socket(PF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addr;
	int strLen;
	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(HOSTIP);
	addr.sin_port = PORT_DATA_SERVER_IN;

	clock_t prevTime = clock();
	int result = connect(hSocket, (SOCKADDR*)&addr, sizeof(addr));
	/* ���ῡ �����ߴٸ� 2�ʸ��� �ٽ� �翬���� �õ��մϴ�. */
	while (result == SOCKET_ERROR)
	{
		if (prevTime + (ONE_SECOND * 2) > clock()) continue;
		prevTime = clock();
		cout << "RECV ������ ���� ��õ���" << endl;
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
		case FLAG_ALL:
			break;
		}
	}

	return 0;
}
/* ��Ʈ��ũ ���̵� ���� */
void ReceiveNetworkID(SOCKET* pSocket)
{
	int nID;
	recv(*pSocket, (char*)&nID, sizeof(int), 0);
	g_pSocketmanager->SetNetworkID(nID);
	cout << "��Ʈ��ũ ���̵� " << nID << endl;
	g_pSocketmanager->SetFlagNum(FLAG_ROOM_NAME);	// << : ��Ʈ��ũ ���̵� ������ �Ϸ�Ǹ� ���� �Ҵ�޾ƾ� �մϴ�.
}

/* ���� ���� �������� Ȯ�� */
void ReceiveRoomName(SOCKET* pSocket)
{
	// << : ������ �����ϴٸ� ��絥���͸� �����ϴ� �ܰ�� , ������ �ȵȴٸ� ���̸��� �ٲٵ���
	int IsOK = 0;
	recv(*pSocket, (char*)&IsOK, sizeof(int), 0);
	if (IsOK)
	{
		cout << "�ش� �濡 ����Ǿ����ϴ�." << endl;
		g_pSocketmanager->SetFlagNum(FLAG_ALL_DATA);

	}
	else if (!IsOK)
		cout << "�ش� �� �ο� �ʰ�" << endl;
};

/* ��ǥ ���� */
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

/* ��� ������ ���� */
void ReceiveAll(LPVOID lpParam)
{
	SOCKET hSocket = *(SOCKET*)lpParam;

}

void SendFlag(SOCKET* pSocket, ST_FLAG* pFlag)
{
	pFlag->eFlag = g_pSocketmanager->GetFlagNum();			// << : �̱��濡�� �÷��׸� �޾ƿɴϴ�.
	pFlag->nNetworkID = g_pSocketmanager->GetNetworkID();	// << : �̱��濡�� ��Ʈ��ũ ���̵� �޾ƿɴϴ�.
	pFlag->nPlayerIndex = g_pData->m_nPlayerNum1P;
	sprintf_s(pFlag->szRoomName, g_pSocketmanager->szRoomName, strlen(g_pSocketmanager->szRoomName));
	send(*pSocket, (char*)pFlag, sizeof(ST_FLAG), 0);
}

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
