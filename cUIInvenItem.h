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
	SYNTHESIZE(int,						m_nAlpha, Alpha);						//���İ�

	SYNTHESIZE(LPDIRECT3DTEXTURE9,		m_pItemTexture, ItemTexture);			//������ �ؽ���
	SYNTHESIZE(eITEMTYPE,				m_nItemType, ItemType);					//������ Ÿ��
	SYNTHESIZE(StuffCode,				m_ItemCode, ItemCode);					//������ �ڵ�
	SYNTHESIZE(RECT,					m_rcItem, rcItem);						//��Ʈ
public:
	virtual void Render(LPD3DXSPRITE pSprite) override;
	cUIInvenItem* FindEmptyInven();												//����ִ� �κ� ã��
	
};

