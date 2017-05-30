#include "stdafx.h"
#include "cMainGame.h"
#include "cCamera.h"

//map
#include "cMapObject.h"

//character


//ui
#include "cTotalUIRender.h"


cMainGame::cMainGame()
	: m_pCamera(NULL)
{	 
}


cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pTotalUIRender);

	//코드 추가
	{
		//map
		SAFE_DELETE(m_pMapObject);

		//character

		//ui
	}

	g_pTextureManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	m_pCamera = new cCamera;
	m_pCamera->Setup(NULL);

	//코드 추가
	{
		//map
		m_pMapObject = new cMapObject;
		m_pMapObject->Setup();

		//character

		//ui
		m_pTotalUIRender = new cTotalUIRender;
		m_pTotalUIRender->Setup();
	}

	m_pCamera->ReTarget(&m_pTotalUIRender->GetCameraTarget());

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
	}
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	
	//코드 추가
	{
		//map
		//m_pMapObject->Render();

		//character

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