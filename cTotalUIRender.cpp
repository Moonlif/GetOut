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
	SAFE_RELEASE(m_pFontWarning);
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

	//��� ��Ʈ �¾�
	g_pFontManager->CreateFont2D(m_pFontWarning, 15, 20, 500);
}

void cTotalUIRender::Update(cCamera* camera)
{

	if (m_pChat) m_pChat->Update();
	if (m_pStartScene && !g_pData->GetIsStartedGame()) m_pStartScene->Update();
	if (m_pChaSelectScene && !g_pData->GetIsStartedGame()) m_pChaSelectScene->Update(camera);
	if (m_pInventory && g_pData->GetIsInvenOpen()) m_pInventory->Update();

	if (GetAsyncKeyState('I') & 0x0001)
	{
		//������ ���۵Ǿ� �κ��� ����
		if (!g_pData->GetIsStartedGame()) return;

		//ä�����̸� ����
		if (g_pData->GetIsOnChat()) return;

		if (g_pData->GetIsInvenOpen())
		{
			g_pData->SetIsInvenOpen(false);
			g_pData->SetIsPossibleMove(true);
		}
		else
		{
			g_pData->SetIsInvenOpen(true);
			g_pData->SetIsPossibleMove(false);
		}

	}
	//��� ���� ����
	if (g_pData->GetisWarning()) LimitWarningTextOutTime();

	//�κ��丮 �׽�Ʈ��
	if (GetAsyncKeyState('0') & 0x0001)
	{
		static int nRnd = 0;
		if (nRnd == 1)	m_pInventory->SetItem(StuffCode::STUFF_PAPER1);
		else if (nRnd == 2)	m_pInventory->SetItem(StuffCode::STUFF_PAPER2);
		else if (nRnd == 3)	m_pInventory->SetItem(StuffCode::STUFF_PAPER3);
		else if (nRnd == 4)	m_pInventory->SetItem(StuffCode::STUFF_BRICK1);
		else if (nRnd == 5)	m_pInventory->SetItem(StuffCode::STUFF_BRICK2);
		else if (nRnd == 6)	m_pInventory->SetItem(StuffCode::STUFF_BRICK3);
		else if (nRnd == 7)	m_pInventory->SetItem(StuffCode::STUFF_BRICK4);
		else if (nRnd == 8)	m_pInventory->SetItem(StuffCode::STUFF_BRICK5);
		else if (nRnd == 9)	m_pInventory->SetItem(StuffCode::STUFF_CROWBAR);
		else if (nRnd == 10)	m_pInventory->SetItem(StuffCode::STUFF_KEY1);
		else if (nRnd == 11)	m_pInventory->SetItem(StuffCode::STUFF_KEY2);
		else if (nRnd == 12)	m_pInventory->SetItem(StuffCode::STUFF_KEY3);
		
		nRnd++;
		if (nRnd > 12) nRnd = 0;
	}

	//�̴ϰ��� �׽�Ʈ��
	if (GetAsyncKeyState('G') & 0x0001)
	{
		if (g_pData->GetIsMiniGamePrisonBreak())
		{
			//�̴ϰ��� ���� �����̰�
			g_pData->SetIsMiniGamePrisonBreak(false);
			g_pData->SetIsPossibleMove(true);
		}
		else
		{
			//�̴ϰ��� �Ѱ� �������̰�
			g_pData->SetIsMiniGamePrisonBreak(true);
			g_pData->SetIsPossibleMove(false);
		}

		
	}
}

void cTotalUIRender::Render()
{
	if (m_pStartScene && !g_pData->GetIsStartedGame()) m_pStartScene->Render();
	if (m_pChaSelectScene && !g_pData->GetIsStartedGame()) m_pChaSelectScene->Render();
	if (m_pInventory && g_pData->GetIsInvenOpen()) m_pInventory->Render();
	if (m_pChat) m_pChat->Render();

	//��ŸƮ�� Ŭ���Ǹ� �ɸ��ͼ����� �¾��ϴ°���
	if (!m_pStartScene->GetIsStartSceneOpen())
	{
		static bool IsSelectSceneOpen = true;
		if (IsSelectSceneOpen) SetupChaSelectScene();
		IsSelectSceneOpen = false;
	}

	RECT rc{ 0, 30, WINSIZEX, 100 };
	if (g_pData->GetisWarning()) g_pFontManager->TextOut2D(m_pFontWarning, 
		g_pData->GetWarningWord(), rc, D3DXCOLOR(1.0f, 1.0f, 0, 1.0f), 
		DT_CENTER | DT_TOP | DT_NOCLIP);
}

void cTotalUIRender::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_pStartScene->WndProc(hWnd, message, wParam, lParam);
}

void cTotalUIRender::SetItem(StuffCode ItemName)
{
	m_pInventory->SetItem(ItemName);
}

StuffCode cTotalUIRender::GetPreparedUsingItem()
{	
	return m_pInventory->GetPreparedUsingItem();
}

void cTotalUIRender::SetupChaSelectScene()
{
	m_pChaSelectScene = new cCharacterSelectScene;
	m_pChaSelectScene->Setup();
}

void cTotalUIRender::LimitWarningTextOutTime()
{
	static int countBag = 0;

	countBag++;

	if (countBag > 100)
	{
		countBag = 0;
		g_pData->SetisWarning(false);
		g_pData->SetWarningWord(" ");
	}
}
