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

	//폰트
	g_pFontManager->CreateFont2D(m_pFont, CHATWORDWIDTH, CHATWORDHEIGHT, 900);

	//텍스쳐
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

		//챗타임이 100보다 작을 때 알파값 조절
		if (m_vChat[i].time <= 50)	m_vChat[i].alpha -= 0.02f;

		//챗타임이 다 끝나면 챗 없애기
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

	//채팅배경 채팅일 때만 띄우기
	if (g_pData->GetIsOnChat())
	{
		pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0.1f),
			D3DCOLOR_ARGB(100, 255, 255, 255));
	}

	//채팅 텍스트 띄우기
	for (int i = 0; i < CHATSIZE; ++i)
	{
		if (m_vChat[i].strChat == " ") continue;

		RECT rc{ 0,WINSIZEY - (CHATWORDHEIGHT * (i + 2)), WINSIZEX, 20 };

		//컬러 설정(1P = 빨강, 2P = 녹색)
		D3DXCOLOR color;
		string str;

		if (m_vChat[i].gender == 1)
		{
			color = D3DXCOLOR(0.9f, 0.5f, 0.5f, m_vChat[i].alpha);
			str = "우석: " + m_vChat[i].strChat;
		}
		else if (m_vChat[i].gender == 2)
		{
			str = "가희: " + m_vChat[i].strChat;
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
