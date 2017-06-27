#pragma once
#include "cUIObject.h"

//��ư ��������Ʈ
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
	//��ư ���� �̳�
	enum eButtonState
	{
		E_NORMAL,
		E_MOUSEOVER,
		E_SELECTED,
		E_STATE_CNT,
	};

	eButtonState m_eButtonState;							//��ư ����
	LPDIRECT3DTEXTURE9	m_aTexture[E_STATE_CNT];			//��ư �� ���¿� ���� �ؽ���

	SYNTHESIZE(iButtonDelegate*,	m_pDelegate, Delegate)	//��������Ʈ
	SYNTHESIZE(int,					m_nAlpha, Alpha)		//��ư ���İ�
public:
	virtual void Update() override;
	virtual void Render(LPD3DXSPRITE pSprite) override;
};

