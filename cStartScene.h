#pragma once

class cUIObject;
class cUITextView;
class cUIImageView;

class cStartScene
{
public:
	cStartScene();
	~cStartScene();
private:
	cUIObject*				m_pStartSceneRoot;				//부모
	cUIImageView*			m_pStartSceneImage;				//스타트씬이미지
	LPD3DXSPRITE			m_pSprite;						//스프라이트

	cUITextView*			m_pStartText;					//텍스트

	SYNTHESIZE(bool,		m_IsStartSceneOpen, IsStartSceneOpen);
public:
	void Setup();
	void Update();
	void Render();


	void WndProc(UINT message);
};

