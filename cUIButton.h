#pragma once
#include "cUIObject.h"

//버튼 델리게이트
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
	//버튼 상태 이넘
	enum eButtonState
	{
		E_NORMAL,
		E_MOUSEOVER,
		E_SELECTED,
		E_STATE_CNT,
	};

	eButtonState m_eButtonState;							//버튼 상태
	LPDIRECT3DTEXTURE9	m_aTexture[E_STATE_CNT];			//버튼 각 상태에 따른 텍스쳐

	SYNTHESIZE(iButtonDelegate*,	m_pDelegate, Delegate)	//델리게이트
	SYNTHESIZE(int,					m_nAlpha, Alpha)		//버튼 알파값
public:
	virtual void Update() override;
	virtual void Render(LPD3DXSPRITE pSprite) override;
};

