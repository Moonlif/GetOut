#pragma once

class cUIObject;
class cUITextView;

class cStartScene
{
public:
	cStartScene();
	~cStartScene();
private:
	cUIObject*				m_pStartScene;
	cUITextView*
	LPD3DXSPRITE			m_pSprite;
public:
	void Setup();
	void Update();
	void Render();
};

