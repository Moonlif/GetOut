#pragma once
class cUIObject;


class cInventory
{
public:
	cInventory();
	~cInventory();

private:
	cUIObject*			m_pUIBase;

	LPD3DXSPRITE		m_pSprite;
public:
	void Setup();
	void Update();
	void Render();

	void SetInventoryBase();
};

