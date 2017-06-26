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
	SYNTHESIZE(int,						m_nAlpha, Alpha);						//알파값

	SYNTHESIZE(LPDIRECT3DTEXTURE9,		m_pItemTexture, ItemTexture);			//아이템 텍스쳐
	SYNTHESIZE(eITEMTYPE,				m_nItemType, ItemType);					//아이템 타입
	SYNTHESIZE(StuffCode,				m_ItemCode, ItemCode);					//아이템 코드
	SYNTHESIZE(RECT,					m_rcItem, rcItem);						//렉트
public:
	virtual void Render(LPD3DXSPRITE pSprite) override;
	cUIInvenItem* FindEmptyInven();												//비어있는 인벤 찾기
	
};

