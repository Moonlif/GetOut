#include "stdafx.h"
#include "cUIImageView.h"


cUIImageView::cUIImageView()
	: m_pTexture(NULL)
{
}

cUIImageView::cUIImageView(char * szFullPath, D3DXVECTOR3 pos, int alpha)
{
	D3DXIMAGE_INFO stImageInfo;

	m_pTexture = g_pTextureManager->GetTexture(szFullPath, &stImageInfo);

	m_stSize.nWidth = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;

	SetRect(&m_rc, 0, 0, m_stSize.nWidth, m_stSize.nHeight);
	m_dwImageColor = D3DCOLOR_ARGB(alpha, 255, 255, 255);

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

	pSprite->Draw(m_pTexture, &m_rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), m_dwImageColor);
	pSprite->End();

	cUIObject::Render(pSprite);
}
