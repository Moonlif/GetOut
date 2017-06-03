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
	//������
	cUIObject*				m_pRoot;
	cUIImageView*			m_pBackgroundImage;

	//�÷��̾� ����
	cUIObject*				m_pPlayer1;
	cUIObject*				m_pPlayer2;

	//��������Ʈ
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

