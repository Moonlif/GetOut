#pragma once

class cUIObject;
class cUITextView;
class cUIImageView;
//�׽�Ʈ��
class cSkinnedMesh;
class cCharacterSelectScene
{
public:
	cCharacterSelectScene();
	~cCharacterSelectScene();

private:
	cUIObject*			m_pRoot;
	cUIImageView*		m_pBlackImage;

	LPD3DXSPRITE		m_pSprite;

	//�׽�Ʈ
	LPD3DXMESH			m_pBox1, m_pBox2;
	D3DMATERIAL9		m_stMtlBox;
public:
	void Setup();
	void Update();
	void Render();

	void TestCharacSetup();
	void TestCharacRender();
};

