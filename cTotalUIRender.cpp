#include "stdafx.h"
#include "cTotalUIRender.h"
#include "cStartScene.h"
#include "cCharacterSelectScene.h"


cTotalUIRender::cTotalUIRender()
	:m_pChaSelectScene(NULL),
	m_pStartScene(NULL)
{
}


cTotalUIRender::~cTotalUIRender()
{
	SAFE_DELETE(m_pStartScene);
	SAFE_DELETE(m_pChaSelectScene);
}

void cTotalUIRender::Setup()
{
	m_pStartScene = new cStartScene;
	m_pStartScene->Setup();
}

void cTotalUIRender::Update()
{
	if (m_pStartScene) m_pStartScene->Update();
	if (m_pChaSelectScene) m_pChaSelectScene->Update();
}

void cTotalUIRender::Render()
{
	if (m_pStartScene) m_pStartScene->Render();
	if (m_pChaSelectScene) m_pChaSelectScene->Render();

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
