#pragma once
class cMtlTex;
class cUIImageView;

class cGamePlay_UI
{
public:
	cGamePlay_UI();
	~cGamePlay_UI();

private:
	cUIImageView*		m_pImage;			//�̹���
	LPD3DXSPRITE		m_pSprite;			//��������Ʈ
public:
	void Setup();
	void Update();
	void Render();
};

