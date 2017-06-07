#pragma once
#include "cUIObject.h"

class cUIInvenItem : public cUIObject
{
public:
	cUIInvenItem();
	cUIInvenItem(char* szFullPath, D3DXVECTOR3 pos, int alpha);
	virtual~cUIInvenItem();

private:
	LPDIRECT3DTEXTURE9					m_pTexture;								//인벤 배경 텍스쳐
	SYNTHESIZE(int,						m_nAlpha, Alpha);

	SYNTHESIZE(LPDIRECT3DTEXTURE9,		m_pItemTexture, ItemTexture);			//아이템 텍스쳐
	SYNTHESIZE(int,						m_nItem, ItemNum);						//아이템 개수
	SYNTHESIZE(eITEMTYPE,				m_nItemType, ItemType);
	SYNTHESIZE(StuffCode,				m_ItemCode, ItemCode);
	SYNTHESIZE(RECT,					m_rcItem, rcItem);
public:
	virtual void Render(LPD3DXSPRITE pSprite) override;
	cUIInvenItem* FindEmptyInven();
};

