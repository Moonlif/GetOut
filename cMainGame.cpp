#include "stdafx.h"
#include "cMainGame.h"

cMainGame::cMainGame()
	: m_pCamera(NULL)
	, m_pMap(NULL)
	, m_p1Player(NULL)
	, m_p2Player(NULL)
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
		SAFE_DELETE(m_p1Player);
		SAFE_DELETE(m_p2Player);

		//ui
		//SAFE_DELETE(m_pTotalUIRender);

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

	//�ڵ� �߰�
	{
		g_pData->Setup();

		//map
		m_pMap = new cMap;
		m_pMap->Setup();
	
		//character
		m_p1Player = new Player;
		m_p1Player->Setup(PLAYER_TYPE::MALE);
		m_p2Player = new Player;
		m_p2Player->Setup(PLAYER_TYPE::FEMALE);

		//interact
		m_pInteract = new cInteract;
		m_pInteract->Setup();

	
		//ui
		//m_pTotalUIRender = new cTotalUIRender;
		//m_pTotalUIRender->Setup();

		//test light
		g_pLightManager->SetDirectionLight(eLIGHT::D_MAIN_LIGHT, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f),
			D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f),	D3DXVECTOR3(0, 1, 1));
		g_pD3DDevice->LightEnable(eLIGHT::D_MAIN_LIGHT, true);

		//m_pCamera->ReTarget(&m_pTotalUIRender->GetCamraStartPos());
	}

	//g_pSocketmanager->Setup();
	//g_pSocketmanager->Setup_Chat();
}

void cMainGame::Update()
{

	g_pTimeManager->Update();
	if (m_pCamera) m_pCamera->Update();
	{
		//map

		//character
		if (g_pUIvarius->GetIsStartedGame() && m_p1Player) m_p1Player->Update(m_pMap);//g_pData->m_nPlayerNum);
		if (g_pUIvarius->GetIsStartedGame() && m_p2Player) m_p2Player->Update(m_pMap);//g_pData->m_nPlayerNum);


		//ui
	//	if (m_pTotalUIRender) m_pTotalUIRender->Update(m_pCamera);

		//interact
		if (m_pInteract) m_pInteract->Update();
	}
	
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(200, 200, 200), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	
	//�ڵ� �߰�
	{
		//map
		//if (m_pMap && g_pUIvarius->GetIsStartedGame()) m_pMap->Render();
		if (m_pMap) m_pMap->Render();
		
		//character
		if (g_pUIvarius->GetIsStartedGame() && m_p1Player) m_p1Player->Render();
		if (g_pUIvarius->GetIsStartedGame() && m_p2Player) m_p2Player->Render();

		//interact stuff
		if (m_pInteract && g_pUIvarius->GetIsStartedGame()) m_pInteract->Render();

		//ui
		
	}

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera) m_pCamera->WndProc(hWnd, message, wParam, lParam);

	//��ŸƮ������ �ƹ�Ű�� ������ �����ϸ� ������Ʈ, ���� ���ϱ� ����. by ���� 17.05.30
	//if (m_pTotalUIRender) m_pTotalUIRender->WndProc(hWnd, message, wParam, lParam);

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