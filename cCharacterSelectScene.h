#pragma once

class cUIObject;
class cCamera;
#include "cUIButton.h"

#define IMAGECHANGESPEED 12
#define CAMERASHAKESPEED 5
#define CAMERASHAKERANGE 0.5f
#define DELETEBACKGROUNDSPEED 4;
#define SETBACKGROUNDSPEED 4;

class cCharacterSelectScene : public iButtonDelegate
{
public:
	cCharacterSelectScene();
	~cCharacterSelectScene();

private:
	//배경관련
	cUIObject*							m_pRoot;

	//플레이어 관련
	cUIObject*							m_pPlayer1;
	cUIObject*							m_pPlayer2;

	//스프라이트
	LPD3DXSPRITE						m_pSprite;

	//카메라 이동 관련
	cUIObject*							m_pGameStart;
	bool								m_isDeleteBackground;
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vRetargetPos, mRetargetPos)
	cCamera*							m_pCamera;

	//어떤 캐릭 선택했나?
	int				m_WhatIsYourNumber;					//자신이 몇 플레이어인지
public:
	void Setup();
	void Update(cCamera* camera);
	void Render();

	void SetBackground();
	void SetMesh();
	
	void UpdateSetFirstBackground();
	void UpdateCharacterSelect();
	void UpdateBeforGameStart();
	void DeleteBackground();
	D3DXVECTOR3 RandomCircle(D3DXVECTOR3 pos, float range);

	virtual void OnClick(cUIButton* pSender) override;
};

