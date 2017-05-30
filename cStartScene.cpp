#include "stdafx.h"
#include "cStartScene.h"
#include "cUIImageView.h"
#include "cUITextView.h"

cStartScene::cStartScene()
	:m_pStartScene(NULL)
	, m_pSprite(NULL)
	, m_IsStartSceneOpen(true)
{
}


cStartScene::~cStartScene()
{
	m_pStartScene->Destroy();
	SAFE_RELEASE(m_pSprite);
}

void cStartScene::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	cUIImageView* pStart = new cUIImageView;
	pStart->SetPosition(D3DXVECTOR3(0,0,0));
	pStart->SetTexture("UI/StartScene/1_StartScene.JPG");
	m_pStartScene = pStart;

	m_pStartText = new cUITextView("Press any key to start", D3DXVECTOR3(400, 500, 0), D3DCOLOR_ARGB(255, 255, 255, 0),
		ST_SIZEN(500, 200), 20, 20, 500, "굴림체");
	m_pStartScene->AddChild(m_pStartText);
}

void cStartScene::Update()
{
	m_pStartScene->Update();

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
}

void cStartScene::Render()
{
	m_pStartScene->Render(m_pSprite);
}
