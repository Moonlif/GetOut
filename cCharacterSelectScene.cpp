#include "stdafx.h"
#include "cCharacterSelectScene.h"

#include "cUIImageView.h"
#include "cUIObject.h"
#include "cUIMesh.h"
#include "cUIButton.h"

cCharacterSelectScene::cCharacterSelectScene()
	:m_pSprite(NULL)
	, m_pBackgroundImage(NULL)
	, m_pRoot(NULL)
	, m_pPlayer1(NULL)
	, m_pPlayer2(NULL)
{
}


cCharacterSelectScene::~cCharacterSelectScene()
{
	m_pRoot->Destroy();
	SAFE_RELEASE(m_pSprite);
	m_pPlayer1->Destroy();
	m_pPlayer2->Destroy();
}

void cCharacterSelectScene::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

<<<<<<< HEAD
	//라이트 셋업
	{
		D3DXCOLOR commonColor(0.8f, 0.8f, 0.8f, 1.0f);
		float commonRange = 3.3f;

	m_pBlackImage = new cUIImageView("UI/BlackBackground.png", D3DXVECTOR3(0, 0, 0), 0);
		////오른쪽 아래 라이트
		//g_pLightManager->SetSpotLight(eLIGHT::E_sCHASLECT_RDIGHT, commonColor, commonColor, commonColor, 
		//	D3DXVECTOR3(2, 4.9f, -800), commonRange, D3DX_PI, D3DX_PI / 6, D3DXVECTOR3(0, -1, 0));
		//g_pD3DDevice->LightEnable(eLIGHT::E_sCHASLECT_RDIGHT, true);

		////오른쪽 위 라이트
		//g_pLightManager->SetSpotLight(eLIGHT::E_sCHASLECT_RULIGHT, commonColor, commonColor, commonColor,
		//	D3DXVECTOR3(2, 5.1f, -800), commonRange, D3DX_PI, D3DX_PI / 6, D3DXVECTOR3(0, 1, 0));
		//g_pD3DDevice->LightEnable(eLIGHT::E_sCHASLECT_RULIGHT, false);
		//
		////왼쪽 아래 라이트
		//g_pLightManager->SetSpotLight(eLIGHT::E_sCHASLECT_LDIGHT, commonColor, commonColor, commonColor,
		//	D3DXVECTOR3(-2, 4.9f, -800), commonRange, D3DX_PI, D3DX_PI / 6, D3DXVECTOR3(0, -1, 0));
		//g_pD3DDevice->LightEnable(eLIGHT::E_sCHASLECT_LDIGHT, true);

		////왼쪽 위 라이트
		//g_pLightManager->SetSpotLight(eLIGHT::E_sCHASLECT_LULIGHT, commonColor, commonColor, commonColor,
		//	D3DXVECTOR3(-2, 5.1f, -800), commonRange, D3DX_PI, D3DX_PI / 6, D3DXVECTOR3(0, 1, 0));
		//g_pD3DDevice->LightEnable(eLIGHT::E_sCHASLECT_LULIGHT, false);
	}

	m_pBlackImage = new cUIImageView("UI/BlackBackground.png", D3DXVECTOR3(0, 0, 1.0f), 200);
	m_pRoot = m_pBlackImage;


	//테스트
	TestCharacSetup();
=======
	//백그라운드 UI
	SetBackground();

	//메쉬, 라이트 셋업
	SetMesh();
>>>>>>> da5668ca910b76697a8e3c2917793b5697f70cbb
}

void cCharacterSelectScene::Update()
{
	m_pRoot->Update();
	m_pPlayer1->Update();
	m_pPlayer2->Update();

	
}

void cCharacterSelectScene::Render()
{
	m_pRoot->Render(m_pSprite);
	m_pPlayer1->Render(m_pSprite);
	m_pPlayer2->Render(m_pSprite);
}


void cCharacterSelectScene::SetBackground()
{
	m_pBackgroundImage = new cUIImageView("UI/CharacterSelectScene/size_Amnesia.jpg", D3DXVECTOR3(0, 0, 0), 220);
	m_pRoot = m_pBackgroundImage;

	cUIImageView* ExplainImage = new cUIImageView("UI/CharacterSelectScene/scroll_tall.png", D3DXVECTOR3(890, 170, 0), 200);
	ExplainImage->SetScaling(D3DXVECTOR3(0.4f, 0.45f, 1.0f));
	ExplainImage->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_EXPLAIN);
	m_pRoot->AddChild(ExplainImage);

	cUIImageView* pPlyer1Image = new cUIImageView("UI/CharacterSelectScene/cha1.png", D3DXVECTOR3(940, 95, 0), 255);
	pPlyer1Image->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER1);
	m_pRoot->AddChild(pPlyer1Image);

	cUIImageView* pPlyer2Image = new cUIImageView("UI/CharacterSelectScene/cha2.png", D3DXVECTOR3(1060, 95, 0), 255);
	pPlyer1Image->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER2);
	m_pRoot->AddChild(pPlyer2Image);

	cUIButton*	pStartButton = new cUIButton("UI/button/master_button_normal.png", "UI/button/master_button_over.png",
		"UI/button/master_button_selected.png", D3DXVECTOR3(970, 560, 0));
	pStartButton->SetTag(eUITAG::E_CHARACTERSELECT_BUTTON_START);
	pStartButton->SetScaling(D3DXVECTOR3(1.0f, 0.9f, 0));
	m_pRoot->AddChild(pStartButton);
}

//플레이어 메쉬, 조명 셋업
void cCharacterSelectScene::SetMesh()
{
	cUIMesh* pPlayer1 = new cUIMesh(cUIMesh::eMESHTYPE::BOX, D3DXVECTOR3(-3, 0, 0));
	m_pPlayer1 = pPlayer1;

	cUIMesh* pPlayer2 = new cUIMesh(cUIMesh::eMESHTYPE::BOX, D3DXVECTOR3(0, 0, 3));
	m_pPlayer2 = pPlayer2;
}
