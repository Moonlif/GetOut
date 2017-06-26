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
	, m_vRetargetPos(0, 0, 0)
	, m_isSelect(false)
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
	//��������Ʈ ����
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	//��׶��� UI
	SetBackground();

	//�޽�, ����Ʈ �¾�
	SetMesh();

	//���� ����
	g_pSoundManager->Play("CharacterSelectScene", 1.0f);
}

void cCharacterSelectScene::Update(cCamera* camera)
{
	//ī�޶� ��Ÿ���� ���� ��
	m_pCamera = camera;
	//ù ��� ���İ� ������Ʈ
	UpdateSetFirstBackground();
	if (m_isDeleteBackground) m_pGameStart->Update();
	m_pRoot->Update();
	m_pPlayer1->Update();
	m_pPlayer2->Update();

	//�ɸ��� ���� ������Ʈ
	if (!m_isDeleteBackground) UpdateCharacterSelect();

	//�ɸ����� �Ϸ�� ��� �����
	if (m_isDeleteBackground) DeleteBackground();

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
	//���İ� �ʱ�ȭ
	static int nAlpha = 0;
	
	//���İ��� 255������ ������Ʈ ����
	if (nAlpha >= 255) return;

	//�±װ����� �� UI ã��
	cUIImageView* Player1 = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER1FACE);
	cUIImageView* Player2 = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER2FACE);
	cUIImageView* Background = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_BACKGROUND);
	cUIImageView* Explain = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_EXPLAIN);

	//�� UI ���İ��� ���� �����ϰ� 
	Player1->SetAlpha(nAlpha);
	Player2->SetAlpha(nAlpha);
	if (nAlpha <= 250) Background->SetAlpha(nAlpha);
	if (nAlpha <= 200) Explain->SetAlpha(nAlpha);

	nAlpha += SETBACKGROUNDSPEED;
}

void cCharacterSelectScene::UpdateCharacterSelect()
{
	///-------------------------------------------------------------
	//                  ���ӽ�ŸƮ �ؽ�Ʈ ��ȭ
	///-------------------------------------------------------------
	cUIImageView* p1Text = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER1TEXT);
	cUIImageView* p2Text = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER2TEXT);

	cUITextView* text = (cUITextView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_TEXT_GAMESTART);
	if (PtInRect(&text->Getrc(), g_ptMouse)) text->SetTextColor(D3DXCOLOR(0.8f, 0.8f, 0.0f, 1.0f));
	else                            text->SetTextColor(D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f));


	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
	{
		cUIImageView* Player1 = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER1FACE);
		cUIImageView* Player2 = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER2FACE);
		cUITextView* pExplain = (cUITextView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_TEXT_EXPLAIN);

		///-------------------------------------------------------------
		//                  1�� �÷��̾� ���ý�
		///-------------------------------------------------------------
		if (PtInRect(&Player1->Getrc(), g_ptMouse))
		{
			//�޽�
			m_pPlayer1->SetIsHidden(false);
			m_pPlayer2->SetIsHidden(true);

			//����Ʈ
			g_pD3DDevice->LightEnable(eLIGHT::S_CHARACTERSELECT_PLAYER1, true);
			g_pD3DDevice->LightEnable(eLIGHT::S_CHARACTERSELECT_PLAYER2, false);

			//�ؽ�Ʈ ����
			pExplain->SetText("       �켮 \n\n\n\n����: ����\n\n����: 25\n����: �������� \n\nSTR    17\nWeight 95kg\n\nƯ¡:\n������ ����� ���ſ� ���ǵ鵵 ���� �ű��. \n\n���� �����ϰ� �ִ�.");

			//������ �޴����� ������ ������ �����ֱ�
			g_pData->m_nPlayerNum1P = 1;
			g_pSocketmanager->AddFlag(FLAG::FLAG_GENDER);

			//�� ȭ��ǥ ����
			p1Text->SetIsHidden(false);
			p1Text->SetPosition(D3DXVECTOR3(70, -25, 0));

			//���� Ŭ���� ����� 1P
			if (!m_isSelect)
			{
				if (g_pData->m_nPlayerNum2P == 0)	g_pData->SetPlayerNum(1);
				else	g_pData->SetPlayerNum(2);

			}
		}
		///-------------------------------------------------------------
		//                  2�� �÷��̾� ���ý�
		///-------------------------------------------------------------
		else if ((PtInRect(&Player2->Getrc(), g_ptMouse)))
		{
			m_pPlayer1->SetIsHidden(true);
			m_pPlayer2->SetIsHidden(false);

			//����Ʈ
			g_pD3DDevice->LightEnable(eLIGHT::S_CHARACTERSELECT_PLAYER1, false);
			g_pD3DDevice->LightEnable(eLIGHT::S_CHARACTERSELECT_PLAYER1, true);

			//�ؽ�Ʈ ����
			pExplain->SetText("       ���� \n\n\n\n����: ����\n\n����: 22 \n����: ��\n\nSTR    10\nWeight 47kg\n\nƯ¡:\n������ �۾� ���� ���� ���� ��� �����ϴ�. \n\n������ ������ �ڱ����!!");
		
			//������ �޴����� ������ ������ �����ֱ�
			g_pData->m_nPlayerNum1P = 2;
			g_pSocketmanager->AddFlag(FLAG::FLAG_GENDER);

			//�� ȭ��ǥ ����
			p1Text->SetIsHidden(false);
			p1Text->SetPosition(D3DXVECTOR3(205, -25, 0));
			
			//���� Ŭ���� ����� 1P
			if (!m_isSelect)
			{
				if (g_pData->m_nPlayerNum2P == 0)	g_pData->SetPlayerNum(1);				
				else	g_pData->SetPlayerNum(2);
				
			}
		}

		///-------------------------------------------------------------
		//                  ���� �����Ϸ��� �� ��
		///-------------------------------------------------------------
		else if ((PtInRect(&text->Getrc(), g_ptMouse)))
		{
			//�÷��̾ ���õ��� �ʾ����� ����
			if (g_pData->m_nPlayerNum1P == 0)
			{
				g_pData->TextOutWarningWord("ĳ���Ͱ� ���õ��� �ʾҽ��ϴ�.");
				return;
			}
			//���� �÷��̾� �������̶�� ���ӽ��� �ȵ�
			if (g_pData->m_nPlayerNum1P == g_pData->m_nPlayerNum2P)
			{
				g_pData->TextOutWarningWord("����� �ٸ� ĳ���� ������ �ּ���.");

				return;
			}

			//���� ��ž, ����
			g_pSoundManager->Stop("CharacterSelectScene");
			g_pSoundManager->Play("LoadingScene", 1.0f);

			//ī�޶� �̵�
			m_pCamera->ReTarget(&m_vRetargetPos);

			//��׶��� ���ֱ� Ʈ��
			m_isDeleteBackground = true;
		}


	}

	///-------------------------------------------------------------
	//                  ���� 1P, 2P ����
	///-------------------------------------------------------------
	if (g_pData->m_nPlayerNum2P != 0)
	{
		p2Text->SetIsHidden(false);
		p2Text->SetAlpha(100);

		//���ڸ� �����ϰ� ���� ��
		if (g_pData->m_nPlayerNum2P == 1)   p2Text->SetPosition(D3DXVECTOR3(70, -130, 0));
		//���ڸ� �����ϰ� ���� ��
		else p2Text->SetPosition(D3DXVECTOR3(205, -130, 0));
		
	}
}

void cCharacterSelectScene::UpdateBeforGameStart()
{
	///-------------------------------------------------------------
	//                  ĳ���� ������
	///-------------------------------------------------------------
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

	//���İ� ����
	if (alpha < 255) alpha += 4;
	img1->SetAlpha(alpha);
	img2->SetAlpha(alpha);
	img3->SetAlpha(alpha);
	img4->SetAlpha(alpha);
	img5->SetAlpha(alpha);
	img6->SetAlpha(alpha);


	if (alpha >= 255)
	{
		alpha = 255;
		Time++;

		//ī�޶� �Ÿ� ������
		static float dis = 5.0f;
		dis -= 0.05f;
		if (dis <= 0.1f) dis = 0.1f;
		m_pCamera->SetCameraDistance(dis);
	}


	//����̹��� �ٲ��ֱ�
	//���� �ð��� ������ ������ �̹��� ����
	if (Time > IMAGECHANGESPEED)
	{
		nImage++;
		if (nImage >= 6) nImage = 6;
		Time = 0;

		switch (nImage)
		{
		case 1:
			//ĳ���� �ؿ� �ִ� ����Ʈ�� ���ֱ�
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
			//���� ����Ʈ Ŵ
			g_pD3DDevice->LightEnable(eLIGHT::D_MAIN_LIGHT, true);
			//���� ��ž �� ��ŸƮ
			g_pSoundManager->Stop("LoadingScene");
			g_pSoundManager->Play("BackGround", 1.0f);
			//1��Ī ������ ���� ī�޶� ���Ͻ�
			m_pCamera->SetCameraDistance(0.1f);

			//����
			if(g_pSocketmanager->GetServerRun()) g_pSocketmanager->InitClientData();
			g_pSocketmanager->AddFlag(FLAG::FLAG_POSITION);	
			break;
		default:
			break;
		}
	}
}

//���� ���۽� UI ���İ� �ٿ����� ������ ����
void cCharacterSelectScene::DeleteBackground()
{
	UpdateBeforGameStart();

	static int alpha = 200;
	if (alpha <= 0)
	{
		m_pRoot->SetIsHidden(true);
		return;
	}
	cUIImageView* Background = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_BACKGROUND);
	cUIImageView* explain = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_EXPLAIN);
	cUIImageView* Player1 = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER1FACE);
	cUIImageView* Player2 = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER2FACE);
	cUITextView* text = (cUITextView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_TEXT_EXPLAIN);

	Background->SetAlpha(alpha);
	explain->SetAlpha(alpha);
	Player1->SetAlpha(alpha);
	Player2->SetAlpha(alpha);
	text->SetIsHidden(true);

	alpha -= DELETEBACKGROUNDSPEED;


}

//ù ����
void cCharacterSelectScene::SetBackground()
{
	//����̹���
	cUIImageView* pBackgroundImage = new cUIImageView("UI/CharacterSelectScene/size_Amnesia.jpg", D3DXVECTOR3(0, 0, 1.0f), 0);
	pBackgroundImage->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_BACKGROUND);
	m_pRoot = pBackgroundImage;

	//ĳ���� ���� �̹���
	cUIImageView* ExplainImage = new cUIImageView("UI/CharacterSelectScene/scroll_tall.png", D3DXVECTOR3(870, 140, 0), 0);
	ExplainImage->SetScaling(D3DXVECTOR3(0.45f, 0.65f, 1.0f));
	ExplainImage->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_EXPLAIN);
	m_pRoot->AddChild(ExplainImage);

	//1p ���� ȭ��ǥ
	cUIImageView* pPlyer1Text = new cUIImageView("UI/CharacterSelectScene/arrow1.png", D3DXVECTOR3(-500, 0, 0), 255);
	pPlyer1Text->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER1TEXT);
	pPlyer1Text->SetIsHidden(true);
	pPlyer1Text->SetScaling(D3DXVECTOR3(1.0f, 0.5f, 0));
	ExplainImage->AddChild(pPlyer1Text);

	//2p ���� ȭ��ǥ
	cUIImageView* pPlyer2Text = new cUIImageView("UI/CharacterSelectScene/arrow2.png", D3DXVECTOR3(-100, 0, 0), 255);
	pPlyer2Text->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER2TEXT);
	pPlyer2Text->SetIsHidden(true);
	pPlyer2Text->SetScaling(D3DXVECTOR3(1.0f, 0.5f, 0));
	ExplainImage->AddChild(pPlyer2Text);

	//���� ĳ���� �̹���
	cUIImageView* pPlyer1Image = new cUIImageView("UI/CharacterSelectScene/cha1.png", D3DXVECTOR3(60, -100, 0), 0);
	pPlyer1Image->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER1FACE);
	ExplainImage->AddChild(pPlyer1Image);

	//���� ĳ���� �̹���
	cUIImageView* pPlyer2Image = new cUIImageView("UI/CharacterSelectScene/cha2.png", D3DXVECTOR3(190, -100, 0), 0);
	pPlyer2Image->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER2FACE);
	ExplainImage->AddChild(pPlyer2Image);

	//���ӽ��� �ؽ�Ʈ
	cUITextView* text = new cUITextView("GAME START", D3DXVECTOR3(60, 500, 0), D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f),
		ST_SIZEN(250, 40), 20, 40, 900);
	text->SetTag(eUITAG::E_CHARACTERSELECT_TEXT_GAMESTART);
	ExplainImage->AddChild(text);

	//ĳ�� ���� �ؽ�Ʈ
	cUITextView* pExplain = new cUITextView(" ", D3DXVECTOR3(35, 26, 0),
		D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), ST_SIZEN(280, 500), 10, 20, 900);
	pExplain->SetTag(eUITAG::E_CHARACTERSELECT_TEXT_EXPLAIN);
	ExplainImage->AddChild(pExplain);

	//------------------------------------------------------------------------------
	//���� ���Խ� �̹���
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
	//1���ɸ�
	cUIMesh* pPlayer1 = new cUIMesh(cUIMesh::eMESHTYPE::MALE, D3DXVECTOR3(-0.5f, -1, 1));
	pPlayer1->SetTag(eUITAG::E_CHARACTERSELECT_MESH_PLAYER1);
	pPlayer1->SetIsHidden(true);
	m_pPlayer1 = pPlayer1;

	//2���ɸ�
	cUIMesh* pPlayer2 = new cUIMesh(cUIMesh::eMESHTYPE::FEMALE, D3DXVECTOR3(-0.5f, -1, 1));
	pPlayer2->SetTag(eUITAG::E_CHARACTERSELECT_MESH_PLAYER2);
	pPlayer2->SetIsHidden(true);
	m_pPlayer2 = pPlayer2;

	D3DXCOLOR color(0.8f, 0.8f, 0.0f, 1.0f);

	//1���ɸ� ����
	cUILight* pLight1 = new cUILight;
	pLight1->SetSpotLight(eLIGHT::S_CHARACTERSELECT_PLAYER1, color, D3DXVECTOR3(0, -2.3f, 0),
		10.0f, D3DX_PI / 2, D3DX_PI / 4, D3DXVECTOR3(0, 1, 0));
	pLight1->SetTag(eUITAG::E_CHARACTERSELECT_LIGHT_PLAYER1);
	m_pPlayer1->AddChild(pLight1);

	//2���ɸ� ����
	cUILight* pLight2 = new cUILight;
	pLight2->SetSpotLight(eLIGHT::S_CHARACTERSELECT_PLAYER2, color, D3DXVECTOR3(0, -2.3f, 0),
		10.0f, D3DX_PI / 2, D3DX_PI / 4, D3DXVECTOR3(0, 1, 0));
	pLight2->SetTag(eUITAG::E_CHARACTERSELECT_LIGHT_PLAYER2);
	m_pPlayer2->AddChild(pLight2);

	//��ũ ����Ʈ ����
	g_pLightManager->SetDirectionLight(eLIGHT::D_DARK, D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f),
		D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), D3DXVECTOR3(0, 0, 1));
}