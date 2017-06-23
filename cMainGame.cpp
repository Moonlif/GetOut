#include "stdafx.h"
#include "cMainGame.h"

//������
#include <process.h>
unsigned __stdcall SetupPlayer(LPVOID lpParam)
{
	CharacterManager* pPlayer = (CharacterManager*)lpParam;
	pPlayer->Setup();
	g_nThreadCount++;
	return 0;
}
unsigned __stdcall SetupInteract(LPVOID lpParam)
{
	g_pData->Setup();
	cInteract* pInteract = (cInteract*)lpParam;
	pInteract->Setup();
	g_nThreadCount++;
	return 0;
}
unsigned __stdcall SetupMap(LPVOID lpParam)
{
	cMap* pInteract = (cMap*)lpParam;
	pInteract->Setup();
	g_nThreadCount++;
	return 0;
}

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
	//�ڵ� �߰�
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

	//�ڵ� �߰�
	{
		g_pData->AddSound();
		//g_pData->Setup();

		//character
		m_pCharacter = new CharacterManager;
		//m_pCharacter->Setup();
		m_pSkybox = new SkyBox;
		m_pSkybox->Initialize(D3DXVECTOR3(0, 0, 0));

		//map
		m_pMap = new cMap;
		//m_pMap->Setup();

		//interact
		m_pInteract = new cInteract;
		//m_pInteract->Setup();

		//ui
		m_pTotalUIRender = new cTotalUIRender;
		m_pTotalUIRender->Setup();

		//light
		g_pLightManager->SetDirectionLight(eLIGHT::D_MAIN_LIGHT, D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f),
		D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f), D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f),	D3DXVECTOR3(-1, -1, -1));

		m_pCamera->ReTarget(&m_pTotalUIRender->GetCamraStartPos());
	}

	//������
	{
		//player
		thPlayerSetup = (HANDLE)_beginthreadex(NULL, 0, (unsigned(_stdcall*)(void*))SetupPlayer, m_pCharacter, 0, NULL);
		//interact
		thInteractSetup = (HANDLE)_beginthreadex(NULL, 0, (unsigned(_stdcall*)(void*))SetupInteract, m_pInteract, 0, NULL);
		//map
		thMapSetup = (HANDLE)_beginthreadex(NULL, 0, (unsigned(_stdcall*)(void*))SetupMap, m_pMap, 0, NULL);
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


	//�ڵ� �߰�
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

	//��ŸƮ������ �ƹ�Ű�� ������ �����ϸ� ������Ʈ, ���� ���ϱ� ����. by ���� 17.05.30
	if (m_pTotalUIRender) m_pTotalUIRender->WndProc(hWnd, message, wParam, lParam);

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
