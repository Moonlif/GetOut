#pragma once
class cMtlTex;
class cUIImageView;

class cGamePlay_UI
{
public:
	cGamePlay_UI();
	~cGamePlay_UI();

private:
	vector<cMtlTex*>	m_vecHand;	
	LPD3DXMESH			m_MeshHand;

	cUIImageView*		m_pImage;
	LPD3DXSPRITE		m_pSprite;
public:
	void Setup();
	void Update();
	void Render();
};

