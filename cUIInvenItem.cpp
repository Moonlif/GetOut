#include "stdafx.h"
#include "cUIInvenItem.h"


cUIInvenItem::cUIInvenItem()
	:m_pItemTexture(NULL)
	, m_nAlpha(255)
{
}

cUIInvenItem::cUIInvenItem(char * szFullPath, D3DXVECTOR3 pos, int alpha)
	: m_pItemTexture(NULL)
{
	m_nAlpha = alpha;
	D3DXIMAGE_INFO stImageInfo;

	m_pTexture = g_pTextureManager->GetTexture(szFullPath, &stImageInfo);

	m_stSize.nWidth = stImageInfo.Width;
	m_stSize.nHeight = stImageInfo.Height;

	m_vPosition = pos;
}


cUIInvenItem::~cUIInvenItem()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pItemTexture);
}

void cUIInvenItem::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	pSprite->SetTransform(&m_matWorld);

	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.nWidth, m_stSize.nHeight);
	//배경이미지
	pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));

	//아이템이미지
	if(m_pItemTexture) 	pSprite->Draw(m_pItemTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), 
		D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));


	pSprite->End();

	cUIObject::Render(pSprite);

}
