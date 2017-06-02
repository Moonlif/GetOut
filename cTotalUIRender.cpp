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



	m_vCameraTarget = D3DXVECTOR3(0, 5, -800);

	//빠르게 넘어가기 위해 임시.
	SetupChaSelectScene();
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

	//스타트씬 클릭되면 케릭터셀렉씬 셋업하는과정
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
