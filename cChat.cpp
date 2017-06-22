#include "stdafx.h"
#include "cChat.h"
#include "cUIchat.h"
#include "cUIButton.h"

cChat::cChat()
	:m_hWndNaming(NULL)
	, m_pRoot(NULL)
	, m_pSprite(NULL)
{
}

cChat::~cChat()
{
	SAFE_RELEASE(m_fontName);
	SAFE_RELEASE(m_pSprite);
	m_pRoot->Destroy();
}

void cChat::Setup()
{
	//배경 
	SetBackground();
}

void cChat::Update()
{
	//채팅 업데이트
	ChatOnOff();

	if (m_pRoot) m_pRoot->Update();
}

void cChat::Render()
{
	//자신이 치는 채팅 렌더
	RenderChat();

	if (m_pRoot) m_pRoot->Render(m_pSprite);
}

//채팅 업데이트
void cChat::ChatOnOff()
{
	//이름 입력
	char str[256];

	//챗 찾기
	cUIchat *chat = (cUIchat*)m_pRoot->FindChildByTag(eUITAG::CHAT_TEXT1);

	GetWindowText(m_hWndNaming, str, strlen(str));
	m_strChat = str;

	//현재 채팅 푸쉬
	if (!g_pData->m_listChat_RECV.empty())
	{
		chat->PushChat(g_pData->m_listChat_RECV.front(), false);
		g_pData->m_listChat_RECV.pop_front();
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x0001)
	{
		//채팅 껐을 때
		if (g_pData->GetIsOnChat())
		{
			////화면지우기
			SetWindowText(m_hWndNaming, NULL);

			//포커스 이동
			SetFocus(g_hWnd);

			//채팅상태 끔
			g_pData->SetIsOnChat(false);

			//아무것도 입력 안할시 리턴
			if (m_strChat == "") return;

			//서버로 데이터 전송
			g_pData->Chat(m_strChat);

			//현재 채팅 푸쉬
			chat->PushChat(m_strChat, true);
		}
		//채팅 켰을 때
		else
		{
			SetFocus(m_hWndNaming);
			ZeroMemory(&str, sizeof(str));
			g_pData->SetIsOnChat(true);
		}
	}
}

//자신이 치는 채팅 렌더
void cChat::RenderChat()
{
	if (!g_pData->GetIsOnChat()) return;
	//이름 렌더
	RECT rc{ 0, WINSIZEY - CHATWORDHEIGHT, 200, WINSIZEY };

	if (g_pData->GetIsStartedGame())
	{
		D3DXCOLOR color;
		if (g_pData->m_nPlayerNum1P == 1)
		{
			color = D3DXCOLOR(0.9f, 0.5f, 0.5f, 1.0f);
			m_strChat = "우석: " + m_strChat;
		}
		else if (g_pData->m_nPlayerNum1P == 2)
		{
			m_strChat = "가희: " + m_strChat;
			color = D3DXCOLOR(0.5f, 0.5f, 0.9f, 1.0f);
		}
		else
		{
			color = D3DXCOLOR(0.5f, 0.9f, 0.5f, 1.0f);
		}
		g_pFontManager->TextOut2D(m_fontName, m_strChat, rc, color);
	}
	else
	{
		D3DXCOLOR color;
		if (g_pData->GetPlayerNum() == 1)
		{
			color = D3DXCOLOR(0.9f, 0.5f, 0.5f, 1.0f);
			
		}
		else if (g_pData->GetPlayerNum() == 2)
		{
			color = D3DXCOLOR(0.5f, 0.5f, 0.9f, 1.0f);
		}
		else
		{
			color = D3DXCOLOR(0.5f, 0.9f, 0.5f, 1.0f);
		}
		g_pFontManager->TextOut2D(m_fontName, m_strChat, rc, color);
	}

	
}

//백그라운드 설정
void cChat::SetBackground()
{
	//채팅 셋
	SetChildWindow();

	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	cUIchat *chatBackground = new cUIchat(D3DXVECTOR3(0, WINSIZEY- CHATWORDHEIGHT, 0));
	chatBackground->SetTag(eUITAG::CHAT_TEXT1);
	chatBackground->SetScaling(D3DXVECTOR3(0.605f, 0.5f, 0.5f));
	
	m_pRoot = chatBackground;
}

//윈도우 설정
void cChat::SetChildWindow()
{
	//WS_VISIBLE

	//이름입력 핸들 생성
	m_hWndNaming = CreateWindow("edit", "",
		WS_CHILD | WS_BORDER,
		0, WINSIZEY - CHATWORDHEIGHT * 10, 250, 20, g_hWnd, HMENU(0), hInst, NULL);

	//폰트 생성
	g_pFontManager->CreateFont2D(m_fontName, CHATWORDWIDTH, CHATWORDHEIGHT, 900);
}


///
// 소켓용
///

void cChat::Setup(int nHandle, int startX, int startY, int Width, int Height)
{
	//채팅 셋
	SetChildWindow(nHandle, startX, startY, Width, Height);

	//배경
	SetBackground();
}

void cChat::SetChildWindow(int nHandle, int startX, int startY, int Width, int Height)
{
	//WS_VISIBLE

	//이름입력 핸들 생성
	m_hWndNaming = CreateWindow("edit", "",
		WS_CHILD | WS_BORDER,
		startX, startY, startX + Width, startY + Height, g_hWnd, HMENU(nHandle), hInst, NULL);

	//폰트 생성
	g_pFontManager->CreateFont2D(m_fontName, CHATWORDWIDTH, CHATWORDHEIGHT, 900);
}

void cChat::Update_ForSocket()
{
	//이름 입력
	char str[256];

	//챗 찾기
	cUIchat *chat = (cUIchat*)m_pRoot->FindChildByTag(eUITAG::CHAT_TEXT1);

	GetWindowText(m_hWndNaming, str, strlen(str));
	m_strChat = str;

	if (GetAsyncKeyState(VK_F1) & 0x0001)
	{
		SetFocus(g_hWnd);
	}
	if (GetAsyncKeyState(VK_F2) & 0x0001)
	{
		SetFocus(m_hWndNaming);
	}
	if (GetAsyncKeyState(VK_F3) & 0x0001)
	{
		SetWindowText(m_hWndNaming, NULL);
	}
	if (GetAsyncKeyState(VK_F4) & 0x0001)
	{
		g_pSocketmanager->SetIP(m_strChat);
		SetWindowText(m_hWndNaming, NULL);
	}
	if (GetAsyncKeyState(VK_F5) & 0x0001)
	{
		g_pSocketmanager->SetMyName(m_strChat);
		SetWindowText(m_hWndNaming, NULL);
	}
	if (GetAsyncKeyState(VK_F6) & 0x0001)
	{
		g_pSocketmanager->SetRoomName(m_strChat);
		SetWindowText(m_hWndNaming, NULL);
	}

	if (m_pRoot) m_pRoot->Update();

}

void cChat::Render(int startX, int startY, int Width, int Height)
{
	RenderChat(startX, startY, Width, Height);

	if (m_pRoot) m_pRoot->Render(m_pSprite);
}

void cChat::RenderChat(int startX, int startY, int Width, int Height)
{
	//if (!g_pData->GetIsOnChat()) return;
	//이름 렌더
	RECT rc{ startX, startY, startX + Width, startY + Height };

	D3DXCOLOR color;
	if (g_pData->GetPlayerNum() == 1)
	{
		color = D3DXCOLOR(0.9f, 0.5f, 0.5f, 1.0f);
	}
	else if (g_pData->GetPlayerNum() == 2)
	{
		color = D3DXCOLOR(0.5f, 0.5f, 0.9f, 1.0f);
	}
	else
	{
		color = D3DXCOLOR(0.5f, 0.9f, 0.5f, 1.0f);
	}
	g_pFontManager->TextOut2D(m_fontName, m_strChat, rc, color);
}
