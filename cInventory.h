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
	
	//���� �� ã�� ��
	bool					m_isWarning;
	string					m_strWarningWord;
	int						m_nBagIsFullTextOutCount;
	LPD3DXFONT				m_pFontWarning;

	//�κ� ������ ������ �̵���
	bool					m_IsPick;
	StuffCode				FirstCode, SecondCode;
	int						m_FirstInvenItemNum, m_SecondInvenItemNum;

	//���콺 �����Ϳ� �ű� ������ ����
	LPDIRECT3DTEXTURE9		m_pTexture;
	RECT					m_rcItem;

public:
	void Setup();
	void Update();
	void Render();

	void SetInventoryBase();
	void SetItem(StuffCode ItemName);

	void LimitWarningTextOutTime();

	void MoveItem();
	void PickedRender();
	eUITAG CarcCuruntPtInven();
	StuffCode GetPreparedUsingItem();

	virtual void OnClick(cUIButton* pSender);
};

