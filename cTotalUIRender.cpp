#include "stdafx.h"
#include "cTotalUIRender.h"
#include "cStartScene.h"
#include "cCharacterSelectScene.h"
#include "cInventory.h"
#include "cChat.h"

cTotalUIRender::cTotalUIRender()
	:m_pChaSelectScene(NULL),
	m_pStartScene(NULL)
	, m_pCamraStartPos(0, 0, 0)
	, m_pInventory(NULL)
{
}


cTotalUIRender::~cTotalUIRender()
{
	SAFE_DELETE(m_pStartScene);
	SAFE_DELETE(m_pChaSelectScene);
	SAFE_DELETE(m_pInventory);
	SAFE_DELETE(m_pChat);
}

void cTotalUIRender::Setup()
{
	m_pInventory = new cInventory;
	m_pInventory->Setup();

	m_pStartScene = new cStartScene;
	m_pStartScene->Setup();

	m_pChat = new cChat;
	m_pChat->Setup();

	m_pCamraStartPos = D3DXVECTOR3(0, 0, 0);
}

void cTotalUIRender::Update(cCamera* camera)
{

	if (m_pChat) m_pChat->Update();
	if (m_pStartScene && !g_pData->GetIsStartedGame()) m_pStartScene->Update();
	if (m_pChaSelectScene && !g_pData->GetIsStartedGame()) m_pChaSelectScene->Update(camera);
	if (m_pInventory && g_pData->GetIsInvenOpen()) m_pInventory->Update();

	//챗이 켜지면 인벤토리 안열림
	if (!g_pData->GetIsOnChat())
	{
		if (GetAsyncKeyState('I') & 0x0001)
		{
			//게임이 시작되야 인벤이 켜짐
			//if (!g_pData->GetIsStartedGame()) return;

			if (g_pData->GetIsInvenOpen()) g_pData->SetIsInvenOpen(false);
			else g_pData->SetIsInvenOpen(true);
		}
	}

	//테스트용
	if (GetAsyncKeyState('0') & 0x0001)
	{
		int nRnd = RND->getInt(5);
		if (nRnd == 1)	m_pInventory->SetItem(StuffCode::STUFF_PAPER1);
		else if (nRnd == 2)	m_pInventory->SetItem(StuffCode::STUFF_PAPER2);
		else if (nRnd == 3)	m_pInventory->SetItem(StuffCode::STUFF_PAPER3);
		else if (nRnd == 3)	m_pInventory->SetItem(StuffCode::STUFF_PAPER2);
		else 	m_pInventory->SetItem(StuffCode::STUFF_PAPER1);
	}
}

void cTotalUIRender::Render()
{
	if (m_pStartScene && !g_pData->GetIsStartedGame()) m_pStartScene->Render();
	if (m_pChaSelectScene && !g_pData->GetIsStartedGame()) m_pChaSelectScene->Render();
	if (m_pInventory && g_pData->GetIsInvenOpen()) m_pInventory->Render();
	if (m_pChat) m_pChat->Render();

	//스타트씬 클릭되면 케릭터셀렉씬 셋업하는과정
	if (!m_pStartScene->GetIsStartSceneOpen())
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

void cTotalUIRender::SetItem(StuffCode ItemName)
{
	m_pInventory->SetItem(ItemName);
}

void cTotalUIRender::SetupChaSelectScene()
{
	m_pChaSelectScene = new cCharacterSelectScene;
	m_pChaSelectScene->Setup();
}
