#pragma once
#include "cUIObject.h"

class cUIInvenItem : public cUIObject
{
public:
	enum eITEMTYPE
	{
		NONE,
		USE,
	};

	cUIInvenItem();
	cUIInvenItem(char* szFullPath, float x, float y, int alpha);
	virtual~cUIInvenItem();

private:
	LPDIRECT3DTEXTURE9					m_pTexture;
	SYNTHESIZE(LPDIRECT3DTEXTURE9,		m_pItemTexture, ItemTexture);
	SYNTHESIZE(int,						m_nItem, nItem);						//아이템 개수
	SYNTHESIZE(int,						m_nAlpha, Alpha);
	SYNTHESIZE(DWORD,					m_nItemType, nItemType);
public:
	virtual void Render(LPD3DXSPRITE pSprite) override;
};

