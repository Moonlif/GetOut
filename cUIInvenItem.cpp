#include "stdafx.h"
#include "cUIInvenItem.h"


cUIInvenItem::cUIInvenItem()
	:m_pItemTexture(NULL)
	, m_nAlpha(255)
	, m_nItemType(eITEMTYPE::ITEMTYPE_NONE)
	, m_nItem(0)
{
}

cUIInvenItem::cUIInvenItem(char * szFullPath, D3DXVECTOR3 pos, int alpha)
	: m_pItemTexture(NULL)
	, m_nItemType(eITEMTYPE::ITEMTYPE_NONE)
	, m_nItem(0)
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
	///-----------------------------------------------------------------------
	//							배경이미지 그리기
	///-----------------------------------------------------------------------

	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.nWidth, m_stSize.nHeight);
	pSprite->Draw(m_pTexture, &rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), D3DCOLOR_ARGB(m_nAlpha, 255, 255, 255));

	///-----------------------------------------------------------------------
	//							아이템 이미지 그리기
	///-----------------------------------------------------------------------
	D3DXMATRIXA16 matS,matT, matItemWorld;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matItemWorld);
	
	///-----------------------------------------------------------------------
	//							조합칸에 있을 때 이미지 그리기
	///-----------------------------------------------------------------------
	if (m_nTag == eUITAG::INVENTORY_COMBINE_1 || m_nTag == eUITAG::INVENTORY_COMBINE_2 ||
		m_nTag == eUITAG::INVENTORY_COMBINE_3)
	{
		//조합칸에 있는 페이퍼들이면 
		if (m_ItemCode == StuffCode::STUFF_PAPER1 || m_ItemCode == StuffCode::STUFF_PAPER2 ||
			m_ItemCode == StuffCode::STUFF_PAPER3)
		{
			D3DXMatrixScaling(&matS, 0.7f, 0.8f, 1.0f);
			D3DXMatrixTranslation(&matT, 23.0f, 38.0f, 0.0f);
		}
		else
		{
			D3DXMatrixScaling(&matS, 0.80f, 1.15f, 1.0f);
			D3DXMatrixTranslation(&matT, 19.0f, 20.0f, 0.0f);
		}
	}
	///-----------------------------------------------------------------------
	//							사용 칸에 있을 때 이미지 그리기
	///-----------------------------------------------------------------------
	else if (m_nTag == eUITAG::INVENTORY_USINGITEM)
	{		
		//사용칸에 있는 페이퍼들이면 
		if (m_ItemCode == StuffCode::STUFF_PAPER1 || m_ItemCode == StuffCode::STUFF_PAPER2 ||
			m_ItemCode == StuffCode::STUFF_PAPER3)
		{
			D3DXMatrixScaling(&matS, 0.45f, 0.8f, 1.0f);
			D3DXMatrixTranslation(&matT, 18.0f, 38.0f, 0.0f);
		}
		else
		{
			D3DXMatrixScaling(&matS, 0.55f, 1.12f, 1.0f);
			D3DXMatrixTranslation(&matT, 14.0f, 20.0f, 0.0f);
		}
	}
	///-----------------------------------------------------------------------
	//							인벤토리에 있을 때 그리기
	///-----------------------------------------------------------------------
	else
	{
		if (m_ItemCode == StuffCode::STUFF_PAPER1 || m_ItemCode == StuffCode::STUFF_PAPER2 ||
			m_ItemCode == StuffCode::STUFF_PAPER3)
		{
			D3DXMatrixScaling(&matS, 0.6f, 1.0f, 1.0f);
			D3DXMatrixTranslation(&matT, 5.0f, 25.0f, 0.0f);
		}
		else
		{
			D3DXMatrixScaling(&matS, 0.7f, 1.6f, 1.0f);
		}
	}

	//월드 구하기
	matItemWorld = matS * matT * m_matWorld;
	pSprite->SetTransform(&matItemWorld);
	if(m_pItemTexture) 	pSprite->Draw(m_pItemTexture, &m_rcItem, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));


	pSprite->End();

	cUIObject::Render(pSprite);

}

cUIInvenItem* cUIInvenItem::FindEmptyInven()
{
	if (m_pItemTexture == NULL) return this;

	for each (auto c in m_vecChild)
	{
		if (c->GetTag() == eUITAG::INVENTORY_COMBINE_1 || c->GetTag() == eUITAG::INVENTORY_COMBINE_2 ||
			c->GetTag() == eUITAG::INVENTORY_COMBINE_3 || c->GetTag() == eUITAG::INVENTORY_USINGITEM) continue;

		cUIInvenItem* p = ((cUIInvenItem*)c)->FindEmptyInven();

		if (p) return p;
	}

	return NULL;

}

