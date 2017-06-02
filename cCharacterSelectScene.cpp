#include "stdafx.h"
#include "cCharacterSelectScene.h"

#include "cUIImageView.h"
#include "cUIObject.h"
#include "cUIMesh.h"
#include "cUIButton.h"
#include "cUILight.h"

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

	//백그라운드 UI
	SetBackground();

	//메쉬, 라이트 셋업
	SetMesh();
}

void cCharacterSelectScene::Update()
{
	m_pRoot->Update();
	m_pPlayer1->Update();
	m_pPlayer2->Update();

	//케릭터 선택 업데이트
	UpdateCharacterSelect();


}

void cCharacterSelectScene::Render()
{
	m_pRoot->Render(m_pSprite);
	m_pPlayer1->Render(m_pSprite);
	m_pPlayer2->Render(m_pSprite);
}


void cCharacterSelectScene::UpdateCharacterSelect()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
	{
		//cUITextView* pTextView = (cUITextView*)m_pUIRoot->FindChildByTag(E_TEXT_VIEW);
		cUIImageView* Player1 = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER1);
		cUIImageView* Player2 = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER2);
		//플레이어 1번 선택시
		if (PtInRect(&Player1->Getrc(), g_ptMouse))
		{
			m_pPlayer1->SetIsHidden(false);
			m_pPlayer2->SetIsHidden(true);
		}
		//플레이어 2번 선택시
		else if ((PtInRect(&Player2->Getrc(), g_ptMouse)))
		{
			m_pPlayer1->SetIsHidden(true);
			m_pPlayer2->SetIsHidden(false);
		}
	}
	
}

void cCharacterSelectScene::SetBackground()
{
	m_pBackgroundImage = new cUIImageView("UI/CharacterSelectScene/size_Amnesia.jpg", D3DXVECTOR3(0, 0, 1.0f), 220);
	m_pBackgroundImage->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_BACKGROUND);
	m_pRoot = m_pBackgroundImage;

	cUIImageView* ExplainImage = new cUIImageView("UI/CharacterSelectScene/scroll_tall.png", D3DXVECTOR3(890, 170, 0), 200);
	ExplainImage->SetScaling(D3DXVECTOR3(0.4f, 0.45f, 1.0f));
	ExplainImage->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_EXPLAIN);
	m_pRoot->AddChild(ExplainImage);

	cUIImageView* pPlyer1Image = new cUIImageView("UI/CharacterSelectScene/cha1.png", D3DXVECTOR3(940, 95, 0), 255);
	pPlyer1Image->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER1);
	m_pRoot->AddChild(pPlyer1Image);

	cUIImageView* pPlyer2Image = new cUIImageView("UI/CharacterSelectScene/cha2.png", D3DXVECTOR3(1060, 95, 0), 255);
	pPlyer2Image->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER2);
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
	cUIMesh* pPlayer1 = new cUIMesh(cUIMesh::eMESHTYPE::BOX, D3DXVECTOR3(-1, 0, 10));
	pPlayer1->SetTag(eUITAG::E_CHARACTERSELECT_MESH_PLAYER1);
	pPlayer1->SetIsHidden(true);
	m_pPlayer1 = pPlayer1;

	cUIMesh* pPlayer2 = new cUIMesh(cUIMesh::eMESHTYPE::SPHERE, D3DXVECTOR3(-1, 0, 10));
	pPlayer2->SetTag(eUITAG::E_CHARACTERSELECT_MESH_PLAYER2);
	pPlayer2->SetIsHidden(true);
	m_pPlayer2 = pPlayer2;

	cUILight* pLight1 = new cUILight;
	pLight1->SetSpotLight(eL)
}
