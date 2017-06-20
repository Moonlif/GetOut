#pragma once
#include "cUIObject.h"

class cUIButton;
class iButtonDelegate
{
public:
	virtual void OnClick(cUIButton* pSender) = 0;
};

class cUIButton : public cUIObject
{
public:
	cUIButton();
	cUIButton(char* szNormal, char* szMouseOver, char* szSelected, D3DXVECTOR3 pos);
	virtual ~cUIButton();

protected:
	enum eButtonState
	{
		E_NORMAL,
		E_MOUSEOVER,
		E_SELECTED,
		E_STATE_CNT,
	};

	eButtonState m_eButtonState;
	LPDIRECT3DTEXTURE9	m_aTexture[E_STATE_CNT];

	SYNTHESIZE(iButtonDelegate*,	m_pDelegate, Delegate)
	SYNTHESIZE(int,					m_nAlpha, Alpha)
public:
	virtual void SetTexture(char* szNormal, char* szOver, char* szSelect);
	virtual void Update() override;
	virtual void Render(LPD3DXSPRITE pSprite) override;
};

