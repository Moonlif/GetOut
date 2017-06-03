#pragma once

class cUIObject;
class cUITextView;
class cUIImageView;

class cCharacterSelectScene
{
public:
	cCharacterSelectScene();
	~cCharacterSelectScene();

private:
	//배경관련
	cUIObject*				m_pRoot;
	cUIImageView*			m_pBackgroundImage;

	//플레이어 관련
	cUIObject*				m_pPlayer1;
	cUIObject*				m_pPlayer2;

	//스프라이트
	LPD3DXSPRITE			m_pSprite;
public:
	void Setup();
	void Update();
	void Render();

	void UpdateSetFirstBackground();
	void UpdateCharacterSelect();
	void SetBackground();
	void SetMesh();
};

