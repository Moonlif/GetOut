#pragma once
class cCamera;

class cMapObject;
class cTotalUIRender;


class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	cCamera*			m_pCamera;

	//map
	cMapObject* m_pMapObject;
	
	//character

	//ui
	cTotalUIRender*		m_pTotalUIRender;

public:
	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	//light
	void Set_Light();
};

