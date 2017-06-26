#include "stdafx.h"
#include "cUIImageView.h"


cUIImageView::cUIImageView()
	: m_pTexture(NULL)
	, m_nAlpha(255)
{
}

cUIImageView::cUIImageView(char * szFullPath, D3DXVECTOR3 pos, int alpha)
{
	//알파값 설정
	m_nAlpha = alpha;

	//이미지 정보를 담고 있는 변수 생성
	D3DXIMAGE_INFO stImageInfo;

	//텍스처 생성
	m_pTexture = g_pTextureManager->GetTexture(szFullPath, &stImageInfo);

	//넓이 높이 저장
	m_stSize.nWidth = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;

	//포지션 저장
	m_vPosition = pos;
}


cUIImageView::~cUIImageView()
{
}


void cUIImageView::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	pSprite->SetTransform(&m_matWorld);

	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.nWidth, m_stSize.nHeight);

	pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
	pSprite->End();

	cUIObject::Render(pSprite);
}
