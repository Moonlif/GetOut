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
	//��� 
	SetBackground();
}

void cChat::Update()
{
	//ä�� ������Ʈ
	ChatOnOff();

	if (m_pRoot) m_pRoot->Update();
}

void cChat::Render()
{
	//�ڽ��� ġ�� ä�� ����
	RenderChat();

	if (m_pRoot) m_pRoot->Render(m_pSprite);
}

//ä�� ������Ʈ
void cChat::ChatOnOff()
{
	//�̸� �Է�
	char str[256];

	//ê ã��
	cUIchat *chat = (cUIchat*)m_pRoot->FindChildByTag(eUITAG::CHAT_TEXT1);

	GetWindowText(m_hWndNaming, str, strlen(str));
	m_strChat = str;

	//���� ä�� Ǫ��
	if (!g_pData->m_listChat_RECV.empty())
	{
		chat->PushChat(g_pData->m_listChat_RECV.front(), false);
		g_pData->m_listChat_RECV.pop_front();
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x0001)
	{
		//ä�� ���� ��
		if (g_pData->GetIsOnChat())
		{
			////ȭ�������
			SetWindowText(m_hWndNaming, NULL);

			//��Ŀ�� �̵�
			SetFocus(g_hWnd);

			//ä�û��� ��
			g_pData->SetIsOnChat(false);

			//�ƹ��͵� �Է� ���ҽ� ����
			if (m_strChat == "") return;

			//������ ������ ����
			g_pData->Chat(m_strChat);

			//���� ä�� Ǫ��
			chat->PushChat(m_strChat, true);
		}
		//ä�� ���� ��
		else
		{
			SetFocus(m_hWndNaming);
			ZeroMemory(&str, sizeof(str));
			g_pData->SetIsOnChat(true);
		}
	}
}

//�ڽ��� ġ�� ä�� ����
void cChat::RenderChat()
{
	if (!g_pData->GetIsOnChat()) return;
	//�̸� ����
	RECT rc{ 0, WINSIZEY - CHATWORDHEIGHT, 200, WINSIZEY };

	if (g_pData->GetIsStartedGame())
	{
		D3DXCOLOR color;
		if (g_pData->m_nPlayerNum1P == 1)
		{
			color = D3DXCOLOR(0.9f, 0.5f, 0.5f, 1.0f);
			m_strChat = "�켮: " + m_strChat;
		}
		else if (g_pData->m_nPlayerNum1P == 2)
		{
			m_strChat = "����: " + m_strChat;
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

//��׶��� ����
void cChat::SetBackground()
{
	//ä�� ��
	SetChildWindow();

	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	cUIchat *chatBackground = new cUIchat(D3DXVECTOR3(0, WINSIZEY- CHATWORDHEIGHT, 0));
	chatBackground->SetTag(eUITAG::CHAT_TEXT1);
	chatBackground->SetScaling(D3DXVECTOR3(0.605f, 0.5f, 0.5f));
	
	m_pRoot = chatBackground;
}

//������ ����
void cChat::SetChildWindow()
{
	//WS_VISIBLE

	//�̸��Է� �ڵ� ����
	m_hWndNaming = CreateWindow("edit", "",
		WS_CHILD | WS_BORDER,
		0, WINSIZEY - CHATWORDHEIGHT * 10, 250, 20, g_hWnd, HMENU(0), hInst, NULL);

	//��Ʈ ����
	g_pFontManager->CreateFont2D(m_fontName, CHATWORDWIDTH, CHATWORDHEIGHT, 900);
}


///
// ���Ͽ�
///

void cChat::Setup(int nHandle, int startX, int startY, int Width, int Height)
{
	//ä�� ��
	SetChildWindow(nHandle, startX, startY, Width, Height);

	//���
	SetBackground();
}

void cChat::SetChildWindow(int nHandle, int startX, int startY, int Width, int Height)
{
	//WS_VISIBLE

	//�̸��Է� �ڵ� ����
	m_hWndNaming = CreateWindow("edit", "",
		WS_CHILD | WS_BORDER,
		startX, startY, startX + Width, startY + Height, g_hWnd, HMENU(nHandle), hInst, NULL);

	//��Ʈ ����
	g_pFontManager->CreateFont2D(m_fontName, CHATWORDWIDTH, CHATWORDHEIGHT, 900);
}

void cChat::Update_ForSocket()
{
	//�̸� �Է�
	char str[256];

	//ê ã��
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
	//�̸� ����
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
