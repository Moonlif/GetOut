#pragma once

class cUIObject;

class cEnding
{
public:
	cEnding();
	~cEnding();

private:
	cUIObject*		m_pRoot;
	LPD3DXSPRITE	m_pSprite;

	string			m_pText;

public:
	void Setup();
	void Update();
	void Render();
};

