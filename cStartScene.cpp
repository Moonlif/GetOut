#include "stdafx.h"
#include "cStartScene.h"
#include "cUIImageView.h"
#include "cUITextView.h"

cStartScene::cStartScene()
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

	cUITextView* pTextView = new cUITextView;
	pTextView->SetFontStyle("Press any key to start", D3DXVECTOR3(400, 450, 0), D3DCOLOR_XRGB(255, 255, 0), 
		ST_SIZEN(500,200) , 20, 20, 500, "±¼¸²Ã¼");
	m_pStartScene->AddChild(pTextView);

}

void cStartScene::Update()
{
	m_pStartScene->Update();
}

void cStartScene::Render()
{
	m_pStartScene->Render(m_pSprite);
}
