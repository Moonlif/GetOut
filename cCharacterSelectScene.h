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
	//������
	cUIObject*							m_pRoot;

	//�÷��̾� ����
	cUIObject*							m_pPlayer1;
	cUIObject*							m_pPlayer2;

	//��������Ʈ
	LPD3DXSPRITE						m_pSprite;

	//ī�޶� �̵� ����
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

