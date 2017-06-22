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

	//��Ʈ
	g_pFontManager->CreateFont2D(m_pFont, CHATWORDWIDTH, CHATWORDHEIGHT, 900);

	//�ؽ���
	D3DXIMAGE_INFO stImageInfo;
	m_pTexture = g_pTextureManager->GetTexture("UI/Chat/titlebar_mask.png", &stImageInfo);
	m_stSize.nWidth = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;

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

	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.nWidth, m_stSize.nHeight);

	//ä�ù�� ä���� ���� ����
	if (g_pData->GetIsOnChat())
	{
		pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0.1f),
			D3DCOLOR_ARGB(100, 255, 255, 255));
	}

	//ä�� �ؽ�Ʈ ����
	for (int i = 0; i < CHATSIZE; ++i)
	{
		if (m_vChat[i].strChat == " ") continue;

		RECT rc{ 0,WINSIZEY - (CHATWORDHEIGHT * (i + 2)), WINSIZEX, 20 };

		//�÷� ����(1P = ����, 2P = ���)
		D3DXCOLOR color;
		string str;

		if (m_vChat[i].gender == 1)
		{
			color = D3DXCOLOR(0.9f, 0.5f, 0.5f, m_vChat[i].alpha);
			str = "�켮: " + m_vChat[i].strChat;
		}
		else if (m_vChat[i].gender == 2)
		{
			str = "����: " + m_vChat[i].strChat;
			color = D3DXCOLOR(0.5f, 0.5f, 0.9f, m_vChat[i].alpha);
		}
		else
		{
			str = m_vChat[i].strChat;
			color = D3DXCOLOR(0.5f, 0.9f, 0.5f, m_vChat[i].alpha);
		}

		g_pFontManager->TextOut2D(m_pFont, str, rc, color);
	}


	pSprite->End();
	cUIObject::Render(pSprite);
}

void cUIchat::PushChat(string str, bool IsYou)
{
	

	for (int i = CHATSIZE - 1; i > 0; --i)
	{
		if (m_vChat[i - 1].strChat == " ") continue;
		m_vChat[i] = m_vChat[i - 1];
	}

	m_vChat[0].strChat = str;
	m_vChat[0].time = CHATTIME;
	m_vChat[0].alpha = 1.0f;

	if (IsYou) m_vChat[0].gender = g_pData->m_nPlayerNum1P;
	else m_vChat[0].gender = g_pData->m_nPlayerNum2P;
}
