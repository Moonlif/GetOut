#include "stdafx.h"
#include "cUIInvenItem.h"


cUIInvenItem::cUIInvenItem()
	:m_pItemTexture(NULL)
{
}

cUIInvenItem::cUIInvenItem(char * szFullPath, float x, float y, int alpha)
	: m_pItemTexture(NULL)
{
	m_nAlpha = alpha;
	D3DXIMAGE_INFO stImageInfo;

	m_pTexture = g_pTextureManager->GetTexture(szFullPath, &stImageInfo);

	m_stSize.nWidth = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;

	m_vPosition = D3DXVECTOR3(x, y, 1.0f);
}


cUIInvenItem::~cUIInvenItem()
{
}

void cUIInvenItem::Render(LPD3DXSPRITE pSprite)
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
