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
	
	//가방 꽉 찾을 때
	int						m_nBagIsFullTextOutCount;
	LPD3DXFONT				m_pFontBagFull;

	//인벤 내에서 아이템 이동시
	bool					m_IsPick;
	StuffCode				FirstCode, SecondCode;
	int						m_FirstInvenItemNum, m_SecondInvenItemNum;

	//마우스 포인터에 옮길 아이템 렌더
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

