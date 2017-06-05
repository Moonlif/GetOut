#include "stdafx.h"
#include "cTotalUIRender.h"
#include "cStartScene.h"
#include "cCharacterSelectScene.h"
#include "cInventory.h"


cTotalUIRender::cTotalUIRender()
	:m_pChaSelectScene(NULL),
	m_pStartScene(NULL)
	, m_pCamraStartPos(0,0,0)
	, m_pInventory(NULL)
{
}


cTotalUIRender::~cTotalUIRender()
{
	SAFE_DELETE(m_pStartScene);
	SAFE_DELETE(m_pChaSelectScene);
	SAFE_DELETE(m_pInventory);
}

void cTotalUIRender::Setup()
{
	m_pInventory = new cInventory;
	m_pInventory->Setup();

	m_pStartScene = new cStartScene;
	m_pStartScene->Setup();

	m_pCamraStartPos = D3DXVECTOR3(0, 0, 0);
}

void cTotalUIRender::Update(cCamera* camera)
{
	if (m_pStartScene) m_pStartScene->Update();
	if (m_pChaSelectScene) m_pChaSelectScene->Update(camera);
	if (m_pInventory && g_pUIvarius->GetIsInvenOpen()) m_pInventory->Update();
	
	if (GetAsyncKeyState('I') & 0x0001)
	{
		if(g_pUIvarius->GetIsInvenOpen()) g_pUIvarius->SetIsInvenOpen(false);
		else g_pUIvarius->SetIsInvenOpen(true);
	}
}

void cTotalUIRender::Render()
{
	if (m_pStartScene) m_pStartScene->Render();
	if (m_pChaSelectScene) m_pChaSelectScene->Render();
	if (m_pInventory && g_pUIvarius->GetIsInvenOpen()) m_pInventory->Render();

	//½ºÅ¸Æ®¾À Å¬¸¯µÇ¸é ÄÉ¸¯ÅÍ¼¿·º¾À ¼Â¾÷ÇÏ´Â°úÁ¤
	if(!m_pStartScene->GetIsStartSceneOpen())
	{
		static bool IsSelectSceneOpen = true;
		if (IsSelectSceneOpen) SetupChaSelectScene();	
		IsSelectSceneOpen = false;
	}
}

void cTotalUIRender::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_pStartScene->WndProc(hWnd, message, wParam, lParam);
}

void cTotalUIRender::SetupChaSelectScene()
{
	m_pChaSelectScene = new cCharacterSelectScene;
	m_pChaSelectScene->Setup();
}
