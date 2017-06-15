#pragma once

class cStartScene;
class cCharacterSelectScene;
class cCamera;
class cInventory;
class cChat;
class cGamePlay_UI;

class cTotalUIRender
{
public:
	cTotalUIRender();
	~cTotalUIRender();

private:
	cStartScene*						m_pStartScene;
	cCharacterSelectScene*				m_pChaSelectScene;
	cInventory*							m_pInventory;
	cChat*								m_pChat;
	cGamePlay_UI*						m_pGamePlay;

	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_pCamraStartPos, CamraStartPos);

	LPD3DXFONT							m_pFontWarning;
public:
	void Setup();
	void Update(cCamera* camera);
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetItem(StuffCode ItemName);
	StuffCode GetPreparedUsingItem();
	void SetupChaSelectScene();

	void LimitWarningTextOutTime();
};

