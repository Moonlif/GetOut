#include "stdafx.h"
#include "cGamePlay_UI.h"
#include "cObjLoader.h"
#include "cMtlTex.h"
#include "cUIImageView.h"

cGamePlay_UI::cGamePlay_UI()
{
}

cGamePlay_UI::~cGamePlay_UI()
{
	m_pImage->Destroy();
	SAFE_RELEASE(m_pSprite);
}

void cGamePlay_UI::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	m_pImage = new cUIImageView("UI/GamePlay/hand.png", D3DXVECTOR3(WINSIZEX / 2, WINSIZEY / 2, 0)
		, 200);
	m_pImage->SetScaling(D3DXVECTOR3(0.9f, 0.9f, 0.9f));
}

void cGamePlay_UI::Update()
{
	m_pImage->Update();
}

void cGamePlay_UI::Render()
{
	m_pImage->Render(m_pSprite);
}
