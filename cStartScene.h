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
	cUIObject*				m_pStartSceneRoot;
	cUIImageView*			m_pStartSceneImage;
	LPD3DXSPRITE			m_pSprite;

	cUITextView*			m_pStartText;

	SYNTHESIZE(bool,		m_IsStartSceneOpen, IsStartSceneOpen);
public:
	void Setup();
	void Update();
	void Render();


	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

