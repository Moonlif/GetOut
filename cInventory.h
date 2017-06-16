#pragma once
class cUIObject;
class cUIInvenItem;
#include "cUIButton.h"

class cInventory : public iButtonDelegate
{
public:
	cInventory();
	~cInventory();

private:
	cUIObject*				m_pUIBase;
	cUIInvenItem*			m_pInven;

	LPD3DXSPRITE			m_pSprite;
	
	//�κ� ������ ������ �̵���
	bool					m_IsPick;
	StuffCode				FirstCode, SecondCode;

	//���콺 �����Ϳ� �ű� ������ ����
	LPDIRECT3DTEXTURE9		m_pTexture;
	RECT					m_rcItem;

public:
	void Setup();
	void Update();
	void Render();

	void SetInventoryBase();
	void SetItem(StuffCode ItemName);

	void MoveItem();
	void PickedRender();
	eUITAG CarcCuruntPtInven();
	StuffCode GetPreparedUsingItem();

	void SaveInvenInfo();
	void LoadInvenInfo();

	virtual void OnClick(cUIButton* pSender);
};

