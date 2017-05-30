#include "cSocketManager.h"



cSocketManager::cSocketManager()
	: dwSendTick(GetTickCount())
	, dwReceiveTick(GetTickCount())
{
}

cSocketManager::~cSocketManager()
{
}
void cSocketManager::Setup()
{
	char message[30];
	int strLen;
	/* ������ ���� ����(2.2), ���̺귯�� �ʱ�ȭ */
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		//���н� MessageBox�� ����.
		int a = 3;
	}

	/* ���� ���� , ���� �ڵ� ��ȯ */
	hSocket = socket(PF_INET, SOCK_STREAM, 0);			/// IPv4 �ּ�, STREAM���
	if (hSocket == INVALID_SOCKET)						/// ���� ���Ҵ� ����ó��
	{
		// ���н� MessageBox�� ����� �˻��Ѵ�.
		int b = 4;
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;						/// IPv4 ���
	servAddr.sin_addr.s_addr = inet_addr(HOSTIP);		/// ȣ��Ʈ IP�ּ�
	servAddr.sin_port = PORTNUM;						/// ������ ��Ʈ ��ȣ

	/* ���� ��� �����û */
	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)	/// Connect ����ó��
	{
		// ���н� MessageBox�� ����� �˻��Ѵ�.
		int c = 5;
	}

	/* Recv �Լ�ȣ���� ���� ������ ���� */
	strLen = recv(hSocket, message, sizeof(message) - 1, 0);						
	if (strLen == -1)	/// Receive ����ó��
	{
		// MessageBox�� ����� �˻��Ѵ�.
		int d = 6;
	}
}

void cSocketManager::SendData()
{
	if (GetTickCount() + SENDTICK > dwSendTick)
	{
		dwSendTick = GetTickCount();
		SendData();
	}

	if (GetTickCount() + RECEIVETICK > dwReceiveTick)
	{
		dwReceiveTick = GetTickCount();
		ReceiveData();
	}
}

void cSocketManager::Update()
{
	/// Send , Receive �ð��� ���� ����
}

void cSocketManager::Close_Socket()
{
	// Client�� CloseSocket�ϸ� �ȴ�. (HalfClose�� �������� ����)
	closesocket(hSocket);
	/* WinSoc ���̺귯�� ���� */
	WSACleanup();
}