#pragma once
class cMtlTex;
class cUIImageView;

class cGamePlay_UI
{
public:
	cGamePlay_UI();
	~cGamePlay_UI();

private:
	cUIImageView*		m_pImage;			//이미지
	LPD3DXSPRITE		m_pSprite;			//스프라이트
public:
	void Setup();
	void Update();
	void Render();
};

