#include "stdafx.h"
#include "cUIchat.h"


cUIchat::cUIchat()
{
}

cUIchat::cUIchat(D3DXVECTOR3 pos)
{
	m_vChat.resize(CHATSIZE);
	for (int i = 0; i < CHATSIZE; ++i)
	{
		m_vChat[i].strChat = " ";
		m_vChat[i].time = 0;
		m_vChat[i].alpha = 0;
	}

	m_vPosition = pos;

	g_pFontManager->CreateFont2D(m_pFont, CHATWORDWIDTH, CHATWORDHEIGHT, 900);
}


cUIchat::~cUIchat()
{
	SAFE_RELEASE(m_pFont);
}

void cUIchat::Update()
{

	for (int i = 0; i < CHATSIZE; ++i)
	{
		if (m_vChat[i].strChat == " ") continue;

		m_vChat[i].time--;

		//êŸ���� 100���� ���� �� ���İ� ����
		if (m_vChat[i].time <= 50)	m_vChat[i].alpha -= 0.02f;

		//êŸ���� �� ������ ê ���ֱ�
		if (m_vChat[i].time <= 0)
		{
			m_vChat[i].alpha = 0;
			m_vChat[i].strChat = " ";
			m_vChat[i].time = 0;
		}
	}

	cUIObject::Update();
}

void cUIchat::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	pSprite->SetTransform(&m_matWorld);

	for (int i = 0; i < CHATSIZE; ++i)
	{
		if (m_vChat[i].strChat == " ") continue;

		RECT rc{ 0,WINSIZEY - (CHATWORDHEIGHT * (i + 2)), WINSIZEX, 20 };

		//�÷� ����(1P = ����, 2P = ���)
		D3DXCOLOR color;
		if (g_pData->m_nPlayerNum1P == 1) color = D3DXCOLOR(0.8f, 0.1f, 0.1f, m_vChat[i].alpha);
		else color = D3DXCOLOR(0.1f, 0.1f, 0.8f, m_vChat[i].alpha);

		g_pFontManager->TextOut2D(m_pFont, m_vChat[i].strChat, rc, color);
	}
	pSprite->End();
	cUIObject::Render(pSprite);
}

void cUIchat::PushChat(string str)
{

	for (int i = CHATSIZE - 1; i > 0; --i)
	{
		m_vChat[i] = m_vChat[i - 1];
	}

	m_vChat[0].strChat = str;
	m_vChat[0].time = CHATTIME;
	m_vChat[0].alpha = 1.0f;
}
