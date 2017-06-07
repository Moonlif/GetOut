#pragma once
class cUIObject;
class cUIInvenItem;

class cInventory
{
public:
	cInventory();
	~cInventory();

private:
	cUIObject*				m_pUIBase;
	cUIInvenItem*			m_pInven;

	LPD3DXSPRITE			m_pSprite;
	
	//���� �� ã�� ��
	int						m_nBagIsFullTextOutCount;
	LPD3DXFONT				m_pFontBagFull;

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
	void BagIsFull();

	void MoveItem();
	void PickedRender();
	eUITAG CarcCuruntPtInven();
};

