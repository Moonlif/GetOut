#include "stdafx.h"
#include "cUIButton.h"

cUIButton::cUIButton()
	: m_eButtonState(E_NORMAL)
	, m_pDelegate(NULL)
	, m_nAlpha(255)
{
}

cUIButton::cUIButton(char * szNormal, char * szMouseOver, char * szSelected, D3DXVECTOR3 pos)
{
	//이미지 정보를 담고 있는 변수 생성
	D3DXIMAGE_INFO stImageInfo;

	//이미지정보를 반환하는 텍스쳐를 등록함.
	m_aTexture[E_NORMAL] = g_pTextureManager->GetTexture(szNormal, &stImageInfo);

	//반환된 이미지 정보에 따른 넓이와 높이 저장.
	m_stSize.nWidth = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;

	//이미지정보를 반환하는 텍스쳐를 등록함.
	m_aTexture[E_MOUSEOVER] = g_pTextureManager->GetTexture(szMouseOver, &stImageInfo);

	//저장된 넓이,높이와 반환된 이미지의 넓이 높이가 다르면 중단
	//(각 버튼상태 이미지의 크기는 동일해야 한다는 설정)
	assert(m_stSize.nWidth == stImageInfo.Width && m_stSize.nHeight == stImageInfo.Height);


	m_aTexture[E_SELECTED] = g_pTextureManager->GetTexture(szSelected, &stImageInfo);
	assert(m_stSize.nWidth == stImageInfo.Width && m_stSize.nHeight == stImageInfo.Height);

	//포지션 저장
	m_vPosition = pos;
}


cUIButton::~cUIButton()
{
}

void cUIButton::Update()
{
	if (m_isHidden) return;

	//현재 커서의 위치를 받아옴
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	//버튼의 렉트 설정
	RECT rc;
	SetRect(&rc, (int)m_matWorld._41, (int)m_matWorld._42, (int)m_matWorld._41 + (int)m_stSize.nWidth, (int)m_matWorld._42 + (int)m_stSize.nHeight);

	//마우스 포인트와 버튼렉트가 부딪혔을 시
	if (PtInRect(&rc, pt))
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			if (m_eButtonState == E_MOUSEOVER)
			{
				m_eButtonState = E_SELECTED;
			}
		}
		else
		{
			if (m_eButtonState == E_SELECTED)
			{
				if (m_pDelegate)
					m_pDelegate->OnClick(this);
			}
			m_eButtonState = E_MOUSEOVER;
		}
	}
	else
	{
		m_eButtonState = E_NORMAL;
	}

	cUIObject::Update();
}

void cUIButton::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	pSprite->SetTransform(&m_matWorld);

	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.nWidth, m_stSize.nHeight);

	pSprite->Draw(m_aTexture[m_eButtonState], &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
	pSprite->End();

	cUIObject::Render(pSprite);
}
