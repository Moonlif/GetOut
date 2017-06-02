#include "stdafx.h"
#include "cMainGame.h"
#include "cCamera.h"

//map
#include "cMapObject.h"

//character


//ui
#include "cTotalUIRender.h"

//interact
#include "cInteract.h"


cMainGame::cMainGame()
	: m_pCamera(NULL)
	, m_pMapObject(NULL)
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
		SAFE_DELETE(m_pMapObject);

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

	//light
	Set_Light();

	//�ڵ� �߰�
	{
		g_pData->Setup();

		//map
		m_pMapObject = new cMapObject;
		m_pMapObject->Setup();

		//character

		//ui
		m_pTotalUIRender = new cTotalUIRender;
		m_pTotalUIRender->Setup();

		//interact
		//m_pInteract = new cInteract;
		//m_pInteract->Setup();
	}

	m_pCamera->ReTarget(NULL);

	g_pSocketmanager->Setup();
	g_pSocketmanager->Setup_Chat();

}

void cMainGame::Update()
{
	g_pTimeManager->Update();
	if (m_pCamera) m_pCamera->Update();
	if (GetAsyncKeyState(VK_F10) & 0x0001)
	{
		string Text = "�ȳ��ϼ���";
		g_pData->Chat(Text);
	}
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
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	
	//�ڵ� �߰�
	{
		//map
		m_pMapObject->Render();

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