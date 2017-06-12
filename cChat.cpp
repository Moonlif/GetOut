#include "stdafx.h"
#include "cChat.h"
#include "cUIchat.h"

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
	SAFE_DELETE(m_pRoot);
}

void cChat::Setup()
{
	//ä�� ��
	SetChildWindow();

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
	//����
	RenderChat();

	if (m_pRoot) m_pRoot->Render(m_pSprite);
}

void cChat::SetChildWindow()
{
	//WS_VISIBLE

	//�̸��Է� �ڵ� ����
	m_hWndNaming = CreateWindow("edit", "",
		WS_CHILD | WS_BORDER,
		0, WINSIZEY - CHATWORDHEIGHT, 250, 20, g_hWnd, HMENU(0), hInst, NULL);

	//��Ʈ ����
	g_pFontManager->CreateFont2D(m_fontName, CHATWORDWIDTH, CHATWORDHEIGHT, 500);
}

void cChat::ChatOnOff()
{
	//�̸� �Է�
	char str[256];

	//ê ã��
	cUIchat *chat = (cUIchat*)m_pRoot->FindChildByTag(eUITAG::CHAT_TEXT1);

	if (!g_pData->m_listChat_RECV.empty())
	{
		chat->PushChat(m_strChat);
		g_pData->m_listChat_RECV.pop_front();
	}
	GetWindowText(m_hWndNaming, str, strlen(str));
	m_strChat = str;

	//���� ä�� Ǫ��
	if (!g_pData->m_listChat_RECV.empty())
	{
		chat->PushChat(g_pData->m_listChat_RECV.front());
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

			//������ ������ ����
			g_pData->Chat(m_strChat);

			//���� ä�� Ǫ��
			chat->PushChat(m_strChat);
		}
		//ä�� ���� ��
		else
		{
			SetFocus(m_hWndNaming);
			g_pData->SetIsOnChat(true);
		}
	}
}

void cChat::RenderChat()
{
	//�̸� ����
	RECT rc{ 0, WINSIZEY - CHATWORDHEIGHT, 200, WINSIZEY };

	D3DXCOLOR color;
	if (g_pData->m_nPlayerNum1P == 1) color = D3DXCOLOR(0.5f, 0.1f, 0.1f, 1.0f);
	else color = D3DXCOLOR(0.1f, 0.1f, 0.5f, 1.0f);

	g_pFontManager->TextOut2D(m_fontName, m_strChat, rc, color);
}

void cChat::SetBackground()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	cUIchat *chatBackground = new cUIchat(D3DXVECTOR3(0, WINSIZEY- CHATWORDHEIGHT, 0));
	chatBackground->SetTag(eUITAG::CHAT_TEXT1);
	chatBackground->SetScaling(D3DXVECTOR3(0.605f, 0.5f, 0.5f));
	
	m_pRoot = chatBackground;
}
