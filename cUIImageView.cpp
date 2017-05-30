#include "stdafx.h"
#include "cUIImageView.h"


cUIImageView::cUIImageView()
	: m_pTexture(NULL)
	, m_nAlpha(255)
{
}


cUIImageView::~cUIImageView()
{
}

void cUIImageView::SetTexture(char * szFullPath)
{
	D3DXIMAGE_INFO stImageInfo;

	m_pTexture = g_pTextureManager->GetTexture(szFullPath, &stImageInfo);

	m_stSize.nWidth = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;


	SetRect(&m_rc, 0, 0, m_stSize.nWidth, m_stSize.nHeight);
}

void cUIImageView::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	pSprite->SetTransform(&m_matWorld);

	pSprite->Draw(m_pTexture, &m_rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));
	pSprite->End();

	cUIObject::Render(pSprite);
}
