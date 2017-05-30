#include "stdafx.h"
#include "cMainGame.h"
#include "cCamera.h"

#include "cObjLoader.h"
#include "cGroup.h"

//map

//character

cMainGame::cMainGame()
	: m_pCamera(NULL)
{	 
}


cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pCamera);

	//코드 추가
	{
		//map
		//17.05.30 최진호
		for each(auto p in m_vecGroup)
		{
			SAFE_DELETE(p);
		}


		//character
	}

	g_pFontManager->Destroy();
	g_pTextureManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	m_pCamera = new cCamera;
	m_pCamera->Setup(NULL);

	//light
	Set_Light();

	//코드 추가
	{
		//map
		Setup_Obj(); //<<17.05.30 최진호 맵 오브젝트 로더
		//character
	}

	m_pCamera->ReTarget(NULL);

	
}

void cMainGame::Update()
{
	g_pTimeManager->Update();
	if (m_pCamera) m_pCamera->Update();

	//코드 추가
	{
		//map

		//character
	}
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	//코드 추가
	{
		//map
		Render_Obj(); //17.05.30 최진호 
		//character
	}

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera) m_pCamera->WndProc(hWnd, message, wParam, lParam);

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
/*
	맵 오브젝트 로더 
	작성자: 최진호
	작성일: 17_05_30
*/
void cMainGame::Setup_Obj()
{
	cObjLoader loadMesh;
	loadMesh.Load(m_vecGroup, "obj", "cs_office.obj", true);
}

/*
	맵 오브젝트 렌더
	작성자: 최진호
	작성일: 17_05_30
*/
void cMainGame::Render_Obj()
{
	D3DXMATRIXA16 matWorld, matS, matR, matT;
	D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);
	//D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F); 
	D3DXMatrixTranslation(&matT, 0, 0, 0);
	matWorld = matS * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	for each(auto p in m_vecGroup)
	{
		p->Render();
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