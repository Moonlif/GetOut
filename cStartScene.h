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
	LPD3DXSPRITE			m_pSprite;

	cUITextView*			m_pStartText;

	SYNTHESIZE(bool,		m_IsStartSceneOpen, IsStartSceneOpen);
public:
	void Setup();
	void Update();
	void Render();
};

