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
	SAFE_DELETE(m_pCamera);
}

void cCharacterSelectScene::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	//백그라운드 UI
	SetBackground();

	//메쉬, 라이트 셋업
	SetMesh();

	//사운드 시작
	g_pSoundManager->Play("CharacterSelectScene", 1.0f);
}

void cCharacterSelectScene::Update(cCamera* camera)
{
	m_pCamera = camera;
	//첫 배경 알파값 업데이트
	UpdateSetFirstBackground();
	if (m_isDeleteBackground) m_pGameStart->Update();
	m_pRoot->Update();
	m_pPlayer1->Update();
	m_pPlayer2->Update();

	//케릭터 선택 업데이트
	if (!m_isDeleteBackground) UpdateCharacterSelect();

	//케릭선택 완료시 배경 지우기
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
	static int nAlpha = 0;
	if (nAlpha >= 255) return;
	cUIImageView* Player1 = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER1FACE);
	cUIImageView* Player2 = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER2FACE);
	cUIImageView* Background = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_BACKGROUND);
	cUIImageView* Explain = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_EXPLAIN);
	//cUIButton* Button = (cUIButton*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_BUTTON_START);

	Player1->SetAlpha(nAlpha);
	Player2->SetAlpha(nAlpha);
	if (nAlpha <= 250) Background->SetAlpha(nAlpha);
	if (nAlpha <= 200) Explain->SetAlpha(nAlpha);
	//Button->SetAlpha(nAlpha);

	nAlpha += SETBACKGROUNDSPEED;
}

void cCharacterSelectScene::UpdateCharacterSelect()
{
	///-------------------------------------------------------------
	//                  게임스타트 텍스트 변화
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
		//                  1번 플레이어 선택시
		///-------------------------------------------------------------
		if (PtInRect(&Player1->Getrc(), g_ptMouse))
		{
			//메쉬
			m_pPlayer1->SetIsHidden(false);
			m_pPlayer2->SetIsHidden(true);

			//라이트
			g_pD3DDevice->LightEnable(eLIGHT::S_CHARACTERSELECT_PLAYER1, true);
			g_pD3DDevice->LightEnable(eLIGHT::S_CHARACTERSELECT_PLAYER2, false);

			//텍스트 변경
			pExplain->SetText("       우석 \n\n\n\n성별: 남자\n\n나이: 25 \n\n직업: 씨름선수 \n\n특징: 타고난 식성으로 몸집이 크며, 천하장사를 3번이나 우승한 경력이 있다. \n\n가희를 좋아하고 있다.");
		
			//데이터 메니져에 선택한 데이터 보내주기
			g_pData->m_nPlayerNum1P = 1;
			g_pSocketmanager->AddFlag(FLAG::FLAG_GENDER);

			//내 화살표 띄우기
			p1Text->SetIsHidden(false);
			p1Text->SetPosition(D3DXVECTOR3(70, -25, 0));
		}
		///-------------------------------------------------------------
		//                  2번 플레이어 선택시
		///-------------------------------------------------------------
		else if ((PtInRect(&Player2->Getrc(), g_ptMouse)))
		{
			m_pPlayer1->SetIsHidden(true);
			m_pPlayer2->SetIsHidden(false);

			//라이트
			g_pD3DDevice->LightEnable(eLIGHT::S_CHARACTERSELECT_PLAYER1, false);
			g_pD3DDevice->LightEnable(eLIGHT::S_CHARACTERSELECT_PLAYER1, true);

			//텍스트 변경
			pExplain->SetText("       가희 \n\n\n\n성별: 여자\n\n나이: 22 \n\n직업: 모델\n\n특징: 최근 심한 다이어트로 마른 몸매를 유지하고 있으나 영양이 부족해 쉽게 지친다. \n\n관심은 오로지 자기관리!!");
		
			//데이터 메니져에 선택한 데이터 보내주기
			g_pData->m_nPlayerNum1P = 2;
			g_pSocketmanager->AddFlag(FLAG::FLAG_GENDER);

			//내 화살표 띄우기
			p1Text->SetIsHidden(false);
			p1Text->SetPosition(D3DXVECTOR3(205, -25, 0));
			
		}

		///-------------------------------------------------------------
		//                  게임 시작하려고 할 시
		///-------------------------------------------------------------
		else if ((PtInRect(&text->Getrc(), g_ptMouse)))
		{
			//플레이어가 선택되지 않았으면 리턴
			if (g_pData->m_nPlayerNum1P == 0)
			{
				g_pData->TextOutWarningWord("캐릭터가 선택되지 않았습니다.");
				return;
			}
			//같은 플레이어 선택중이라면 게임시작 안됨
			if (g_pData->m_nPlayerNum1P == g_pData->m_nPlayerNum2P)
			{
				if (g_pData->GetPlayerNum() == 1)
				{
					g_pData->TextOutWarningWord("플레이어2와 다른 캐릭을 선택해 주세요.");
				}
				else if (g_pData->GetPlayerNum() == 2)
				{
					g_pData->TextOutWarningWord("플레이어1과 다른 캐릭을 선택해 주세요.");
				}
				return;
			}

			g_pSoundManager->Stop("CharacterSelectScene");
			g_pSoundManager->Play("LoadingScene", 1.0f);
			m_pCamera->ReTarget(&m_vRetargetPos);
			m_isDeleteBackground = true;
			// << : 여기서 초기화 및 좌표 전송하게 변경해야함
		}


	}

	///-------------------------------------------------------------
	//                  상대방 1P, 2P 띄우기
	///-------------------------------------------------------------
	if (g_pData->m_nPlayerNum2P != 0)
	{
		p2Text->SetIsHidden(false);
		p2Text->SetAlpha(100);

		//남자를 선택하고 있을 때
		if (g_pData->m_nPlayerNum2P == 1)   p2Text->SetPosition(D3DXVECTOR3(70, -130, 0));
		//여자를 선택하고 있을 때
		else p2Text->SetPosition(D3DXVECTOR3(205, -130, 0));
		
	}
}

void cCharacterSelectScene::UpdateBeforGameStart()
{
	///-------------------------------------------------------------
	//                  캐릭터 셀렉시
	///-------------------------------------------------------------
	//카메라 움직이기
	if (m_vRetargetPos.x > -0.5f) m_vRetargetPos.x -= 0.1f;

	static int alpha = 0;
	static int Time = 0;
	static int nImage = 0;
	static D3DXVECTOR3 SavePt = D3DXVECTOR3(-1.0f, 0, 0);
	//배경 세팅
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

	//카메라 흔들기
	if (alpha >= 255)
	{
		alpha = 255;
		Time++;

		//카메라 흔들기
		//if (Time % CAMERASHAKESPEED == 0) m_vRetargetPos = RandomCircle(SavePt, CAMERASHAKERANGE);

		//카메라 거리 좁히기
		static float dis = 5.0f;
		dis -= 0.05f;
		if (dis <= 0.1f) dis = 0.1f;
		m_pCamera->SetCameraDistance(dis);
	}


	//배경이미지 바꿔주기
	if (Time > IMAGECHANGESPEED)
	{
		nImage++;
		Time = 0;


		switch (nImage)
		{
		case 1:
			//다크 라이트 키기
			//g_pD3DDevice->LightEnable(eLIGHT::D_DARK, true);
			//밑에 있는 라이트들 꺼주기
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
			//게임 시작
			img6->SetIsHidden(true);
			g_pData->SetIsStartedGame(true);
			g_pD3DDevice->LightEnable(eLIGHT::D_MAIN_LIGHT, true);
			g_pSoundManager->Stop("LoadingScene");
			m_pCamera->SetCameraDistance(0.1f);
			if(g_pSocketmanager->GetServerRun()) g_pSocketmanager->InitClientData();
			g_pSocketmanager->AddFlag(FLAG::FLAG_POSITION);
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
	//static float x = 1.0f;
	//static float y = 0.9f;
	if (alpha <= 0)
	{
		m_pRoot->SetIsHidden(true);
		return;
	}
	cUIImageView* Background = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_BACKGROUND);
	cUIImageView* explain = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_EXPLAIN);
	cUIImageView* Player1 = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER1FACE);
	cUIImageView* Player2 = (cUIImageView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER2FACE);
	//cUIButton* button = (cUIButton*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_BUTTON_START);
	cUITextView* text = (cUITextView*)m_pRoot->FindChildByTag(eUITAG::E_CHARACTERSELECT_TEXT_EXPLAIN);

	Background->SetAlpha(alpha);
	explain->SetAlpha(alpha);
	Player1->SetAlpha(alpha);
	Player2->SetAlpha(alpha);
	text->SetIsHidden(true);
	//button->SetScaling(D3DXVECTOR3(x, y, 0));

	alpha -= DELETEBACKGROUNDSPEED;
	//if(x > 0) x -= 0.05f;
	//if(y > 0) y -= 0.05f;

	//if (x <= 0) x = 0;
	//if (y <= 0) y = 0;

}

void cCharacterSelectScene::SetBackground()
{
	cUIImageView* pBackgroundImage = new cUIImageView("UI/CharacterSelectScene/size_Amnesia.jpg", D3DXVECTOR3(0, 0, 1.0f), 0);
	pBackgroundImage->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_BACKGROUND);
	m_pRoot = pBackgroundImage;

	cUIImageView* ExplainImage = new cUIImageView("UI/CharacterSelectScene/scroll_tall.png", D3DXVECTOR3(870, 140, 0), 0);
	ExplainImage->SetScaling(D3DXVECTOR3(0.45f, 0.65f, 1.0f));
	ExplainImage->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_EXPLAIN);
	m_pRoot->AddChild(ExplainImage);

	cUIImageView* pPlyer1Text = new cUIImageView("UI/CharacterSelectScene/arrow1.png", D3DXVECTOR3(-500, 0, 0), 255);
	pPlyer1Text->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER1TEXT);
	pPlyer1Text->SetIsHidden(true);
	pPlyer1Text->SetScaling(D3DXVECTOR3(1.0f, 0.5f, 0));
	ExplainImage->AddChild(pPlyer1Text);

	cUIImageView* pPlyer2Text = new cUIImageView("UI/CharacterSelectScene/arrow2.png", D3DXVECTOR3(-100, 0, 0), 255);
	pPlyer2Text->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER2TEXT);
	pPlyer2Text->SetIsHidden(true);
	pPlyer2Text->SetScaling(D3DXVECTOR3(1.0f, 0.5f, 0));
	ExplainImage->AddChild(pPlyer2Text);

	cUIImageView* pPlyer1Image = new cUIImageView("UI/CharacterSelectScene/cha1.png", D3DXVECTOR3(60, -100, 0), 0);
	pPlyer1Image->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER1FACE);
	ExplainImage->AddChild(pPlyer1Image);

	cUIImageView* pPlyer2Image = new cUIImageView("UI/CharacterSelectScene/cha2.png", D3DXVECTOR3(190, -100, 0), 0);
	pPlyer2Image->SetTag(eUITAG::E_CHARACTERSELECT_IMAGE_PLAYER2FACE);
	ExplainImage->AddChild(pPlyer2Image);

	/*cUIButton*   pStartButton = new cUIButton("UI/button/BlackButton_Normal.png", "UI/button/BlackButton_Over.png",
	"UI/button/BlackButton_Down.png", D3DXVECTOR3(40, 490, 0));
	pStartButton->SetTag(eUITAG::E_CHARACTERSELECT_BUTTON_START);
	pStartButton->SetScaling(D3DXVECTOR3(2.0f, 0.45f, 0));
	pStartButton->SetDelegate(this);
	pStartButton->SetAlpha(200);
	ExplainImage->AddChild(pStartButton);*/

	cUITextView* text = new cUITextView("GAME START", D3DXVECTOR3(60, 500, 0), D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f),
		ST_SIZEN(250, 40), 20, 40, 900);
	text->SetTag(eUITAG::E_CHARACTERSELECT_TEXT_GAMESTART);
	//text->SetIsHidden(true);
	ExplainImage->AddChild(text);

	cUITextView* pExplain = new cUITextView(" ", D3DXVECTOR3(35, 26, 0),
		D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), ST_SIZEN(280, 500), 13, 20, 500);
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

//플레이어 메쉬, 조명 셋업
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

	//다크 라이트 세팅
	g_pLightManager->SetDirectionLight(eLIGHT::D_DARK, D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f),
		D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f), D3DXVECTOR3(0, 0, 1));
}