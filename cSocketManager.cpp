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
	/* 윈도우 소켓 버전(2.2), 라이브러리 초기화 */
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		//실패시 MessageBox를 띄운다.
		int a = 3;
	}

	/* 소켓 생성 , 소켓 핸들 반환 */
	hSocket = socket(PF_INET, SOCK_STREAM, 0);			/// IPv4 주소, STREAM모드
	if (hSocket == INVALID_SOCKET)						/// 소켓 비할당 예외처리
	{
		// 실패시 MessageBox를 띄워서 검사한다.
		int b = 4;
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;						/// IPv4 사용
	servAddr.sin_addr.s_addr = inet_addr(HOSTIP);		/// 호스트 IP주소
	servAddr.sin_port = PORTNUM;						/// 접속할 포트 번호

	/* 소켓 기반 연결요청 */
	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)	/// Connect 예외처리
	{
		// 실패시 MessageBox를 띄워서 검사한다.
		int c = 5;
	}

	/* Recv 함수호출을 통해 데이터 수신 */
	strLen = recv(hSocket, message, sizeof(message) - 1, 0);						
	if (strLen == -1)	/// Receive 예외처리
	{
		// MessageBox를 띄워서 검사한다.
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
	/// Send , Receive 시간에 맞춰 수행
}

void cSocketManager::Close_Socket()
{
	// Client는 CloseSocket하면 된다. (HalfClose는 서버에서 수행)
	closesocket(hSocket);
	/* WinSoc 라이브러리 해제 */
	WSACleanup();
}