#pragma once
#include "cUIObject.h"

class cUIInvenItem : public cUIObject
{
public:
	cUIInvenItem();
	cUIInvenItem(char* szFullPath, D3DXVECTOR3 pos, int alpha);
	virtual~cUIInvenItem();

private:
	LPDIRECT3DTEXTURE9					m_pTexture;								//�κ� ��� �ؽ���
	SYNTHESIZE(int,						m_nAlpha, Alpha);

	SYNTHESIZE(LPDIRECT3DTEXTURE9,		m_pItemTexture, ItemTexture);			//������ �ؽ���
	SYNTHESIZE(int,						m_nItem, nItem);						//������ ����
	SYNTHESIZE(DWORD,					m_nItemType, nItemType);
public:
	virtual void Render(LPD3DXSPRITE pSprite) override;
};

