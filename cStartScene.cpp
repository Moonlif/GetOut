#include "stdafx.h"
#include "cStartScene.h"
#include "cUIImageView.h"
#include "cUITextView.h"

cStartScene::cStartScene()
	:m_pStartSceneRoot(NULL)
	, m_pSprite(NULL)
	, m_IsStartSceneOpen(true)
{
}


cStartScene::~cStartScene()
{
	m_pStartSceneRoot->Destroy();
	SAFE_RELEASE(m_pSprite);
}

void cStartScene::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	m_pStartSceneImage = new cUIImageView("UI/StartScene/1_StartScene.JPG", D3DXVECTOR3(0, 0, 1.0f), 255);
	m_pStartSceneRoot = m_pStartSceneImage;

	m_pStartText = new cUITextView("Press any key to start", D3DXVECTOR3(400, 500, 0), D3DCOLOR_ARGB(255, 255, 255, 0),
		ST_SIZEN(500, 200), 20, 20, 500, "굴림체");
	m_pStartSceneRoot->AddChild(m_pStartText);

	g_pSoundManager->Play("StartScene", 1.0f);
}

void cStartScene::Update()
{

	m_pStartSceneRoot->Update();

	//Press any key to start 키 알파값 업데이트
	{
		static bool IsAlpha = false;
		static int	nAlpha = 255;

		if (IsAlpha)	nAlpha -= 3;
		else			nAlpha += 3;

		if (nAlpha >= 253) IsAlpha = true;
		else if (nAlpha <= 3) IsAlpha = false;

		D3DCOLOR TextColor = D3DCOLOR_ARGB(nAlpha, 255, 255, 0);

		m_pStartText->SetTextColor(TextColor);
	}

	//스타트씬 이미지 알파값 업데이트
	if (!m_IsStartSceneOpen)
	{
		static int	nImageAlpha = 255;
		nImageAlpha -= 5;

		m_pStartSceneImage->SetAlpha(nImageAlpha);

		if (nImageAlpha <= 0)
		{
			nImageAlpha = 0;
			m_pStartSceneRoot->SetIsHidden(true);
		}
	}
}

void cStartScene::Render()
{
	m_pStartSceneRoot->Render(m_pSprite);
}

void cStartScene::WndProc(UINT message)
{
	switch (message)
	{
	case WM_KEYDOWN:
		m_pStartText->SetIsHidden(true);
		m_IsStartSceneOpen = false;
		g_pSoundManager->Stop("StartScene");
	case WM_LBUTTONDOWN:
		m_pStartText->SetIsHidden(true);
		m_IsStartSceneOpen = false;
		g_pSoundManager->Stop("StartScene");
		break;
	case WM_RBUTTONDOWN:
		m_pStartText->SetIsHidden(true);
		m_IsStartSceneOpen = false;
		g_pSoundManager->Stop("StartScene");
		break;
	}
}
