#include "stdafx.h"
#include "cMainGame.h"

cMainGame::cMainGame()
	: m_pCamera(NULL)
	, m_pMap(NULL)
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

	//코드 추가
	{
		g_pData->Setup();

		//map
		m_pMap = new cMap;
		m_pMap->Setup();

		//character

		//interact
		m_pInteract = new cInteract;
		m_pInteract->Setup();

		//ui
		m_pTotalUIRender = new cTotalUIRender;
		m_pTotalUIRender->Setup();

		//test light
		g_pLightManager->SetDirectionLight(0, D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f), D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f), D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f),
			D3DXVECTOR3(0, 1, 1));
		g_pD3DDevice->LightEnable(0, true);

		m_pCamera->ReTarget(&m_pTotalUIRender->GetCamraStartPos());
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

		//ui
		if (m_pTotalUIRender) m_pTotalUIRender->Update();

		//interact
		if (m_pInteract) m_pInteract->Update();
	}
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(200, 200, 200), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	
	//코드 추가
	{
		//map
		//if (m_pMap) m_pMap->Render();

		//character

		//interact stuff
		if (m_pInteract) m_pInteract->Render();

		//ui
		if (m_pTotalUIRender) m_pTotalUIRender->Render();
	}



	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera) m_pCamera->WndProc(hWnd, message, wParam, lParam);

	//스타트씬에서 아무키나 눌러서 시작하면 업데이트, 렌더 안하기 위함. by 영현 17.05.30
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