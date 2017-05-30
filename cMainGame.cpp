#include "stdafx.h"
#include "cMainGame.h"

#include "cCamera.h"
#include "cTotalUIRender.h"

//map

//character

cMainGame::cMainGame()
	: m_pCamera(NULL)
{	 
}


cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pTotalUIRender);
	
	g_pTextureManager->Destroy();
	g_pDeviceManager->Destroy();
	g_pSocketmanager->m_vPostion
}

void cMainGame::Setup()
{
	m_pCamera = new cCamera;
	m_pCamera->Setup(NULL);


	m_pTotalUIRender = new cTotalUIRender;
	m_pTotalUIRender->Setup();

	m_pCamera->ReTarget(NULL);

	Set_Light();
}

void cMainGame::Update()
{
	g_pTimeManager->Update();
	if (m_pCamera) m_pCamera->Update();
	if (m_pTotalUIRender) m_pTotalUIRender->Update();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(100, 100, 100), 1.0f, 0);
	g_pD3DDevice->BeginScene();
	///---------------------------------------------------
	if (m_pTotalUIRender) m_pTotalUIRender->Render();
	///----------------------------------------------------
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera) m_pCamera->WndProc(hWnd, message, wParam, lParam);
	//스타트씬에서 아무키나 눌러서 시작하면 업데이트, 렌더 안하기 위함.
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


//light
void cMainGame::Set_Light()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, true);

	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));

	//directional light
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	D3DXVECTOR3 vDir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;

	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);
}