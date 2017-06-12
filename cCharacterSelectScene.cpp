#include "stdafx.h"
#include "cCharacterSelectScene.h"

#include "cUIImageView.h"
#include "cUIObject.h"
#include "cUIMesh.h"
#include "cUILight.h"
#include "cUITextView.h"
#include "cCamera.h"

cCharacterSelectScene::cCharacterSelectScene()
	:m_pSprite(NULL)
	, m_pRoot(NULL)
	, m_pPlayer1(NULL)
	, m_pPlayer2(NULL)
	, m_isDeleteBackground(false)
	, m_vRetargetPos(0,0,0)
	, m_Player1_Number(0)
	, m_Player2_Number(0)
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

	//��׶��� UI
	SetBackground();

	//�޽�, ����Ʈ �¾�
	SetMesh();
}

void cCharacterSelectScene::Update(cCamera* camera)
{
	m_pCamera = camera;
	//ù ��� ���İ� ������Ʈ
	UpdateSetFirstBackground();
	if (m_isDeleteBackground) m_pGameStart->Update();
	m_pRoot->Update();
	m_pPlayer1->Update();
	m_pPlayer2->Update();
	//�ɸ��� ���� ������Ʈ
	UpdateCharacterSelect();

	//�ɸ����� �Ϸ�� ��� �����
	if(m_isDeleteBackground) DeleteBackground();
}

void cCharacterSelectScene::Render()
{
	if (m_isDeleteBackground) m_pGameStart->Render(m_pSprite);
	m_pRoot->Render(m_pSprite);
	m_pPlayer1->Render(m_pSprite);
	m_pPlayer2->Render(m_pSprite);
	

}


void cCharacterSelectScene::UpdateSetFirstBackground()
{
	static int nAlpha = 0;
	if (nAlpha >= 255) return;
	cUIImageView* Player1 = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER1);
	cUIImageView* Player2 = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER2);
	cUIImageView* Background = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_BACKGROUND);
	cUIImageView* Explain = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_EXPLAIN);
	cUIButton* Button = (cUIButton*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_BUTTON_START);

	Player1->SetAlpha(nAlpha);
	Player2->SetAlpha(nAlpha);
	if (nAlpha <= 250) Background->SetAlpha(nAlpha);
	if (nAlpha <= 200) Explain->SetAlpha(nAlpha);
	Button->SetAlpha(nAlpha);

	nAlpha += SETBACKGROUNDSPEED;
}

void cCharacterSelectScene::UpdateCharacterSelect()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
	{		
		cUIImageView* Player1 = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER1);
		cUIImageView* Player2 = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER2);
		cUITextView* pExplain = (cUITextView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_TEXT_EXPLAIN);
		//�÷��̾� 1�� ���ý�
		if (PtInRect(&Player1->Getrc(), g_ptMouse))
		{
			//�޽�
			m_pPlayer1->SetIsHidden(false);
			m_pPlayer2->SetIsHidden(true);

			//����Ʈ
			g_pD3DDevice->LightEnable(eLIGHT::S_CHARACTERSELECT_PLAYER1, true);
			g_pD3DDevice->LightEnable(eLIGHT::S_CHARACTERSELECT_PLAYER2, false);

			//�ؽ�Ʈ ����
			pExplain->SetText("���� ĳ���� \n\n����:\n���� �ؼ� ���ſ� ��ü�� �ű� �� �ִ�. \n\n����:\n������ Ŀ�� ���� ���� ���� ���Ѵ�.");

			//������ �޴����� ������ ������ �����ֱ�
			m_Player1_Number = 1;
			g_pData->m_nPlayerNum1P = 1;
		}
		//�÷��̾� 2�� ���ý�
		else if ((PtInRect(&Player2->Getrc(), g_ptMouse)))
		{
			m_pPlayer1->SetIsHidden(true);
			m_pPlayer2->SetIsHidden(false);

			//����Ʈ
			g_pD3DDevice->LightEnable(eLIGHT::S_CHARACTERSELECT_PLAYER1, false);
			g_pD3DDevice->LightEnable(eLIGHT::S_CHARACTERSELECT_PLAYER1, true);

			//�ؽ�Ʈ ����
			pExplain->SetText("���� ĳ���� \n\n����:\n������ �����ϰ� �۾� ���� ������ �� �� �ִ�. \n\n����:\n���� ���� ���ſ� ��ü�� �ű��� ���Ѵ�.");

			//������ �޴����� ������ ������ �����ֱ�
			m_Player1_Number = 2;
			g_pData->m_nPlayerNum1P = 2;
		}
	}

}

void cCharacterSelectScene::UpdateBeforGameStart()
{
	//ī�޶� �����̱�
	if (m_vRetargetPos.x > -0.5f) m_vRetargetPos.x -= 0.1f;

	static int alpha = 0;
	static int Time = 0;
	static int nImage = 0;
	static D3DXVECTOR3 SavePt = D3DXVECTOR3(-1.0f, 0, 0);
	//��� ����
	cUIImageView* img1 = (cUIImageView*)m_pGameStart->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_GAMESTART1);
	cUIImageView* img2 = (cUIImageView*)m_pGameStart->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_GAMESTART2);
	cUIImageView* img3 = (cUIImageView*)m_pGameStart->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_GAMESTART3);
	cUIImageView* img4 = (cUIImageView*)m_pGameStart->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_GAMESTART4);
	cUIImageView* img5 = (cUIImageView*)m_pGameStart->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_GAMESTART5);
	cUIImageView* img6 = (cUIImageView*)m_pGameStart->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_GAMESTART6);

	if (alpha < 255) alpha += 4;
	img1->SetAlpha(alpha);
	img2->SetAlpha(alpha);
	img3->SetAlpha(alpha);
	img4->SetAlpha(alpha);
	img5->SetAlpha(alpha);
	img6->SetAlpha(alpha);
	
	//ī�޶� ����
	if (alpha >= 255)
	{
		alpha = 255;
		Time++;
		
		//ī�޶� ����
		if (Time % CAMERASHAKESPEED == 0) m_vRetargetPos = RandomCircle(SavePt, CAMERASHAKERANGE);

		//ī�޶� �Ÿ� ������
		static float dis = 5.0f;
		dis -= 0.05f;
		if (dis <= 0.1f) dis = 0.1f;
		m_pCamera->SetCameraDistance(dis);
	}
	

	//����̹��� �ٲ��ֱ�
	if (Time > IMAGECHANGESPEED)
	{
		nImage++;
		Time = 0;
		

		switch (nImage)
		{
		case 1:
			//��ũ ����Ʈ Ű��
			//g_pD3DDevice->LightEnable(eLIGHT::D_DARK, true);
			//�ؿ� �ִ� ����Ʈ�� ���ֱ�
			g_pD3DDevice->LightEnable(eLIGHT::S_CHARACTERSELECT_PLAYER1, false);
			g_pD3DDevice->LightEnable(eLIGHT::S_CHARACTERSELECT_PLAYER2, false);
			img1->SetIsHidden(true);
			img2->SetPosition(D3DXVECTOR3(0, 0, 0));
			break;
		case 2:
			img2->SetIsHidden(true);
			img3->SetPosition(D3DXVECTOR3(0, 0, 0));
			break;
		case 3:
			img3->SetIsHidden(true);
			img4->SetPosition(D3DXVECTOR3(0, 0, 0));
			break;
		case 4:
			img4->SetIsHidden(true);
			img5->SetPosition(D3DXVECTOR3(0, 0, 0));
			break;
		case 5:
			img5->SetIsHidden(true);
			break;
		case 6:
			//���� ����
			img6->SetIsHidden(true);
			g_pData->SetIsStartedGame(true);
			g_pD3DDevice->LightEnable(eLIGHT::D_MAIN_LIGHT, true);
			m_pCamera->SetCameraDistance(0.1f);

			//ī�޶� ��Ÿ���� ĳ���Ϳ��� �ٲ��ֱ�
			break;
		default:
			break;
		}
	}
}

void cCharacterSelectScene::DeleteBackground()
{
	UpdateBeforGameStart();

	static int alpha = 200;
	static float x = 1.0f;
	static float y = 0.9f;
	if (alpha <= 0)
	{
		m_pRoot->SetIsHidden(true);
		return;
	}
	cUIImageView* Background = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_BACKGROUND);
	cUIImageView* explain = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_EXPLAIN);
	cUIImageView* Player1 = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER1);
	cUIImageView* Player2 = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER2);
	cUIButton* button = (cUIButton*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_BUTTON_START);
	cUITextView* text = (cUITextView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_TEXT_EXPLAIN);
	
	Background->SetAlpha(alpha);
	explain->SetAlpha(alpha);
	Player1->SetAlpha(alpha);
	Player2->SetAlpha(alpha);
	text->SetIsHidden(true);
	button->SetScaling(D3DXVECTOR3(x, y, 0));
	
	alpha -= DELETEBACKGROUNDSPEED;
	if(x > 0) x -= 0.05f;
	if(y > 0) y -= 0.05f;

	if (x <= 0) x = 0;
	if (y <= 0) y = 0;

}

D3DXVECTOR3 cCharacterSelectScene::RandomCircle(D3DXVECTOR3 pos, float range)
{
	float RandomX = 0;
	float RandomY = 0;

	RandomX = RND->getFloatFromTo(pos.x, pos.x + range * 2);
	RandomY = RND->getFloatFromTo(pos.y - range, pos.y + range);

	return D3DXVECTOR3(RandomX, RandomY, pos.z);
}

void cCharacterSelectScene::OnClick(cUIButton * pSender)
{
	if (pSender->GetTag() == eUITAG::E_CHARACTERSELECT_BUTTON_START)
	{

		m_pCamera->ReTarget(&m_vRetargetPos);
		m_isDeleteBackground = true;
	}
}

void cCharacterSelectScene::SetBackground()
{
	cUIImageView* pBackgroundImage = new cUIImageView("UI/CharacterSelectScene/size_Amnesia.jpg", D3DXVECTOR3(0, 0, 1.0f), 0);
	pBackgroundImage->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_BACKGROUND);
	m_pRoot = pBackgroundImage;

	cUIImageView* ExplainImage = new cUIImageView("UI/CharacterSelectScene/scroll_tall.png", D3DXVECTOR3(890, 170, 0), 0);
	ExplainImage->SetScaling(D3DXVECTOR3(0.4f, 0.45f, 1.0f));
	ExplainImage->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_EXPLAIN);
	m_pRoot->AddChild(ExplainImage);

	cUIImageView* pPlyer1Image = new cUIImageView("UI/CharacterSelectScene/cha1.png", D3DXVECTOR3(50, -75, 0), 0);
	pPlyer1Image->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER1);
	ExplainImage->AddChild(pPlyer1Image);

	cUIImageView* pPlyer2Image = new cUIImageView("UI/CharacterSelectScene/cha2.png", D3DXVECTOR3(170, -75, 0), 0);
	pPlyer2Image->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER2);
	ExplainImage->AddChild(pPlyer2Image);

	cUIButton*	pStartButton = new cUIButton("UI/button/master_button_normal.png", "UI/button/master_button_over.png",
		"UI/button/master_button_selected.png", D3DXVECTOR3(970, 560, 0));
	pStartButton->SetTag(eUITAG::E_CHARACTERSELECT_BUTTON_START);
	pStartButton->SetScaling(D3DXVECTOR3(1.0f, 0.9f, 0));
	pStartButton->SetDelegate(this);
	m_pRoot->AddChild(pStartButton);

	cUITextView* pExplain = new cUITextView(" ", D3DXVECTOR3(35,60,0), 
		D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), ST_SIZEN(230, 500), 13,20, 500);
	pExplain->SetTag(eUITAG::E_CHARACTERSELECT_TEXT_EXPLAIN);
	ExplainImage->AddChild(pExplain);

	//------------------------------------------------------------------------------
	cUIImageView* gameStart6 = new cUIImageView("UI/CharacterSelectScene/welcome_bg06.jpg", D3DXVECTOR3(0, 0, 1.0f), 0);
	gameStart6->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_GAMESTART6);
	m_pGameStart = gameStart6;

	cUIImageView* gameStart1 = new cUIImageView("UI/CharacterSelectScene/welcome_bg01.jpg", D3DXVECTOR3(0, 0, 0), 0);
	gameStart1->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_GAMESTART1);
	m_pGameStart->AddChild(gameStart1);

	cUIImageView* gameStart2 = new cUIImageView("UI/CharacterSelectScene/welcome_bg02.jpg", D3DXVECTOR3(0, 0, 1.0f), 0);
	gameStart2->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_GAMESTART2);
	m_pGameStart->AddChild(gameStart2);

	cUIImageView* gameStart3 = new cUIImageView("UI/CharacterSelectScene/welcome_bg03.jpg", D3DXVECTOR3(0, 0, 1.0f), 0);
	gameStart3->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_GAMESTART3);
	m_pGameStart->AddChild(gameStart3);

	cUIImageView* gameStart4 = new cUIImageView("UI/CharacterSelectScene/welcome_bg04.jpg", D3DXVECTOR3(0, 0, 1.0f), 0);
	gameStart4->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_GAMESTART4);
	m_pGameStart->AddChild(gameStart4);


	cUIImageView* gameStart5 = new cUIImageView("UI/CharacterSelectScene/welcome_bg05.jpg", D3DXVECTOR3(0, 0, 1.0f), 0);
	gameStart5->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_GAMESTART5);
	m_pGameStart->AddChild(gameStart5);
	
}

//�÷��̾� �޽�, ���� �¾�
void cCharacterSelectScene::SetMesh()
{
	cUIMesh* pPlayer1 = new cUIMesh(cUIMesh::eMESHTYPE::MALE, D3DXVECTOR3(-0.5f, -1, 1));
	pPlayer1->SetTag(eUITAG::E_CHARACTERSELECT_MESH_PLAYER1);
	pPlayer1->SetIsHidden(true);
	m_pPlayer1 = pPlayer1;

	cUIMesh* pPlayer2 = new cUIMesh(cUIMesh::eMESHTYPE::FEMALE, D3DXVECTOR3(-0.5f, -1, 1));
	pPlayer2->SetTag(eUITAG::E_CHARACTERSELECT_MESH_PLAYER2);
	pPlayer2->SetIsHidden(true);
	m_pPlayer2 = pPlayer2;

	D3DXCOLOR color(0.8f, 0.8f, 0.0f, 1.0f);

	cUILight* pLight1 = new cUILight;
	pLight1->SetSpotLight(eLIGHT::S_CHARACTERSELECT_PLAYER1, color, D3DXVECTOR3(0, -2.3f, 0), 
		10.0f, D3DX_PI / 2, D3DX_PI / 4, D3DXVECTOR3(0, 1, 0));
	pLight1->SetTag(eUITAG::E_CHARACTERSELECT_LIGHT_PLAYER1);
	m_pPlayer1->AddChild(pLight1);

	cUILight* pLight2 = new cUILight;
	pLight2->SetSpotLight(eLIGHT::S_CHARACTERSELECT_PLAYER2, color, D3DXVECTOR3(0, -2.3f, 0),
		10.0f, D3DX_PI / 2, D3DX_PI / 4, D3DXVECTOR3(0, 1, 0));
	pLight2->SetTag(eUITAG::E_CHARACTERSELECT_LIGHT_PLAYER2);
	m_pPlayer2->AddChild(pLight2);

	//��ũ ����Ʈ ����
	g_pLightManager->SetDirectionLight(eLIGHT::D_DARK, D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f),
		D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), D3DXVECTOR3(0, 0, 1));
}
