#include "stdafx.h"
#include "cTotalUIRender.h"
#include "cStartScene.h"
#include "cCharacterSelectScene.h"
#include "cInventory.h"
#include "cChat.h"
#include "cGamePlay_UI.h"
#include "cEnding.h"

cTotalUIRender::cTotalUIRender()
	:m_pChaSelectScene(NULL),
	m_pStartScene(NULL)
	, m_vCamraStartPos(0, 0, 0)
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
	SAFE_DELETE(m_pGamePlay);
	SAFE_DELETE(m_pEnding);
}

void cTotalUIRender::Setup()
{
	m_pInventory = new cInventory;
	m_pInventory->Setup();

	m_pStartScene = new cStartScene;
	m_pStartScene->Setup();

	m_pChaSelectScene = new cCharacterSelectScene;
	m_pChaSelectScene->Setup();

	m_pChat = new cChat;
	m_pChat->Setup();

	m_pGamePlay = new cGamePlay_UI;
	m_pGamePlay->Setup();

	m_pEnding = new cEnding;
	m_pEnding->Setup();

	m_vCamraStartPos = D3DXVECTOR3(0, 0, 0);

	//경고 폰트 셋업
	g_pFontManager->CreateFont2D(m_pFontWarning, 15, 30, 500);
}

void cTotalUIRender::Update(cCamera* camera)
{

	if (m_pChat) m_pChat->Update();
	if (m_pStartScene && !g_pData->GetIsStartedGame()) m_pStartScene->Update();
	if (m_pChaSelectScene && !g_pData->GetIsStartedGame() && !m_pStartScene->GetIsStartSceneOpen()) m_pChaSelectScene->Update(camera);
	if (m_pInventory && g_pData->GetIsInvenOpen()) m_pInventory->Update();
	if (m_pGamePlay && g_pData->GetIsStartedGame() && !g_pData->GetIsInvenOpen() && g_pData->m_isHandOn) m_pGamePlay->Update();
	if (m_pEnding && g_pData->GetIsEnding()) m_pEnding->Update();
	if (GetAsyncKeyState('I') & 0x0001)
	{
		//게임이 시작되야 인벤이 켜짐
		if (!g_pData->GetIsStartedGame()) return;

		//채팅중이면 리턴
		if (g_pData->GetIsOnChat()) return;

		//이미 인벤이 열려 있었던 상태면 끄기
		if (g_pData->GetIsInvenOpen()) g_pData->SetIsInvenOpen(false);
		
		//인벤이 닫혀 있었던 상태면 인벤 열기
		else g_pData->SetIsInvenOpen(true);
		

	}

	//나갔다 다시 들어온 경우 저장된 아이템 로드하는 부분
	if (g_pData->GetIsLoadItem())
	{
		m_pInventory->LoadInvenInfo();
	}

	//경고 문구 띄우기
	if (g_pData->GetisWarning()) LimitWarningTextCount();

	//아이템 습득시
	if (g_pData->GetPickUpItemCode() != StuffCode::STUFF_NONE)
	{
		SetItem(g_pData->GetPickUpItemCode());
		g_pData->SetPickUpItemCode(StuffCode::STUFF_NONE);
	}
}

void cTotalUIRender::Render()
{
	//스타트씬
	if (m_pStartScene && !g_pData->GetIsStartedGame()) m_pStartScene->Render();
	//셀렉씬
	if (m_pChaSelectScene && !g_pData->GetIsStartedGame() && !m_pStartScene->GetIsStartSceneOpen()) m_pChaSelectScene->Render();
	//인벤토리
	if (m_pInventory && g_pData->GetIsInvenOpen()) m_pInventory->Render();
	//채팅
	if (m_pChat) m_pChat->Render();
	//게임플레이 UI
	if (m_pGamePlay && g_pData->GetIsStartedGame() && !g_pData->GetIsInvenOpen() && g_pData->m_isHandOn) m_pGamePlay->Render();
	//엔딩
	if (m_pEnding && g_pData->GetIsEnding()) m_pEnding->Render();

	RECT rc{ 0, 30, WINSIZEX, 100 };
	if (g_pData->GetisWarning()) g_pFontManager->TextOut2D(m_pFontWarning, 
		g_pData->GetWarningWord(), rc, D3DXCOLOR(1.0f, 1.0f, 0, 1.0f), 
		DT_CENTER | DT_TOP | DT_NOCLIP);
}

void cTotalUIRender::WndProc(UINT message)
{
	m_pStartScene->WndProc(message);
}

void cTotalUIRender::SetItem(StuffCode ItemName)
{
	m_pInventory->SetItem(ItemName);
}

StuffCode cTotalUIRender::GetPreparedUsingItem()
{	
	return m_pInventory->GetPreparedUsingItem();
}

//경고문구 제한시간 관련 업데이트
void cTotalUIRender::LimitWarningTextCount()
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
