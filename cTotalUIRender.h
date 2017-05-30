#pragma once

class cStartScene;
class cCharacterSelectScene;

class cTotalUIRender
{
public:
	cTotalUIRender();
	~cTotalUIRender();

private:
	cStartScene*				m_pStartScene;
	cCharacterSelectScene*		m_pChaSelectScene;

public:
	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetupChaSelectScene();
};

