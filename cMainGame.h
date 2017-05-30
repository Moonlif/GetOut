#pragma once
class cCamera;
class cStartScene;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	cCamera*		m_pCamera;
	cStartScene*	m_pStartScene;

public:
	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//light
	void Set_Light();
};

