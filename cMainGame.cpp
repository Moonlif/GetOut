#include "stdafx.h"
#include "cMainGame.h"

cMainGame::cMainGame()
	: m_pCamera(NULL)
	, m_pMap(NULL)
	, m_pCharacter(NULL)
	, m_pMonsterManager(NULL)
	, m_pSkybox(NULL)
	, m_pParticleManager(NULL)
	, m_pTotalUIRender(NULL)
	, m_pInteract(NULL)
{
}


cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pCamera);
	//코드 추가
	{
		//map
		SAFE_DELETE(m_pMap);

		//character
		SAFE_DELETE(m_pCharacter);
		SAFE_DELETE(m_pMonsterManager);
		SAFE_DELETE(m_pSkybox);
		SAFE_DELETE(m_pParticleManager);

		//ui
		SAFE_DELETE(m_pTotalUIRender);

		//interact
		SAFE_DELETE(m_pInteract);
	}

	g_pData->Destroy();
	g_pSocketmanager->Destroy();
	g_pTextureManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	m_pCamera = new cCamera;
	m_pCamera->Setup(NULL);

	g_pSocketmanager->Setup();

	//코드 추가
	{
		g_pData->AddSound();
		g_pData->Setup();

		//character
		m_pCharacter = new CharacterManager;
		m_pCharacter->Setup();
		m_pSkybox = new SkyBox;
		m_pSkybox->Initialize(D3DXVECTOR3(0, 0, 0));

		//map
		m_pMap = new cMap;
		m_pMap->Setup();

		//interact
		m_pInteract = new cInteract;
		m_pInteract->Setup();

		//ui
		m_pTotalUIRender = new cTotalUIRender;
		m_pTotalUIRender->Setup();

		//light
		g_pLightManager->SetDirectionLight(eLIGHT::D_MAIN_LIGHT, D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f),
		D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f), D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f),	D3DXVECTOR3(-1, -1, -1));

		m_pCamera->ReTarget(&m_pTotalUIRender->GetCamraStartPos());
	}
}

void cMainGame::Update()
{
	g_pTimeManager->Update();
	g_pSoundManager->Update();
	g_pSocketmanager->Update();

	if (m_pCamera) m_pCamera->Update();
	{
		if (!g_pData->GetIsEnding())
		{
			//character
			if (m_pCharacter && g_pData->GetIsStartedGame()) m_pCharacter->Update(m_pMap);
			static bool start = false;
			if (g_pData->GetIsStartedGame() && start == false)
			{
				start = true;
				m_pCamera->ReTarget(&m_pCharacter->GetTargetPos());
			}
			if (m_pParticleManager && g_pData->GetIsStartedGame())  m_pParticleManager->Update();

			//interact
			if (m_pInteract && g_pData->GetIsStartedGame()) m_pInteract->Update();
		}


		//ui
		if (m_pTotalUIRender) m_pTotalUIRender->Update(m_pCamera);
	}
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(200, 200, 200), 1.0f, 0);
	g_pD3DDevice->BeginScene();


	//코드 추가
	{
		if (!g_pData->GetIsEnding())
		{
			//map
			if (m_pMap && g_pData->GetIsStartedGame()) m_pMap->Render();

			//character
			if (m_pCharacter && g_pData->GetIsStartedGame()) m_pCharacter->Render();
			if (m_pSkybox && g_pData->GetIsStartedGame()) m_pSkybox->Render();
			if (m_pParticleManager && g_pData->GetIsStartedGame()) m_pParticleManager->Render();

			//interact stuff
			if (m_pInteract && g_pData->GetIsStartedGame()) m_pInteract->Render();

		}
		//ui
		if (m_pTotalUIRender) m_pTotalUIRender->Render();

		g_pSocketmanager->UIRender();
	}

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera) m_pCamera->WndProc(hWnd, message, wParam, lParam);

	//스타트씬에서 아무키나 눌러서 시작하면 업데이트, 렌더 안하기 위함. by 영현 17.05.30
	if (m_pTotalUIRender) m_pTotalUIRender->WndProc(message);

	switch (message)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	}
}
