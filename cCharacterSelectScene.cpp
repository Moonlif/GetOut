#include "stdafx.h"
#include "cCharacterSelectScene.h"

#include "cUIImageView.h"
#include "cUIObject.h"


cCharacterSelectScene::cCharacterSelectScene()
	:m_pSprite(NULL)
	, m_pBlackImage(NULL)
	,m_pRoot(NULL)
{
}


cCharacterSelectScene::~cCharacterSelectScene()
{
	m_pRoot->Destroy();
	SAFE_RELEASE(m_pSprite);
}

void cCharacterSelectScene::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	//라이트 셋업
	g_pLightManager->SetSpotLight(eLIGHT::E_sCHASLECT_LIGHT1, D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f),
		D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f), D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f), D3DXVECTOR3(300, 100, 0),
		10.0f, D3DX_PI / 2, D3DX_PI / 4, D3DXVECTOR3(0, -1, 0));
	g_pD3DDevice->LightEnable(eLIGHT::E_sCHASLECT_LIGHT1, true);

	m_pBlackImage = new cUIImageView("UI/BlackBackground.png", D3DXVECTOR3(0, 0, 0), 0);
	m_pRoot = m_pBlackImage;
}

void cCharacterSelectScene::Update()
{
	m_pRoot->Update();
}

void cCharacterSelectScene::Render()
{
	m_pRoot->Render(m_pSprite);
}
