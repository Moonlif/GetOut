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

	LPD3DXSPRITE		m_pSprite;
public:
	void Setup();
	void Update();
	void Render();

	void SetInventoryBase();
	void SetItem(StuffCode ItemName);
};

