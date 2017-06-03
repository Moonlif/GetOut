#pragma once

class cUIObject;
class cUITextView;
class cUIImageView;
class cCamera;
#include "cUIButton.h"

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

	virtual void OnClick(cUIButton* pSender) override;
};

