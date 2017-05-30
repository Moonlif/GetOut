#pragma once

class cUIObject;
class cUITextView;
class cUIImageView;

class cCharacterSelectScene
{
public:
	cCharacterSelectScene();
	~cCharacterSelectScene();

private:
	cUIObject*			m_pRoot;
	cUIImageView*		m_pBlackImage;

	LPD3DXSPRITE		m_pSprite;
public:
	void Setup();
	void Update();
	void Render();
};

