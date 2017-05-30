#pragma once

class cStartScene;
class cCharacterSelectScene;

class cTotalUIRender
{
public:
	cTotalUIRender();
	~cTotalUIRender();

private:
	cStartScene*							m_pStartScene;
	cCharacterSelectScene*					m_pChaSelectScene;
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3,		m_vCameraTarget, CameraTarget);
public:
	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetupChaSelectScene();
};

