#include "stdafx.h"
#include "cMiniGame_PrisonBreak.h"
#include "cUIImageView.h"
#include "cObjLoader.h"

cMiniGame_PrisonBreak::cMiniGame_PrisonBreak()
{
}


cMiniGame_PrisonBreak::~cMiniGame_PrisonBreak()
{
	m_pRoot->Destroy();
	SAFE_RELEASE(m_pSprite);
}

void cMiniGame_PrisonBreak::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	cUIImageView* background = new cUIImageView("UI/PrisonBreak/PrisonBreak1.png", D3DXVECTOR3(0, 0, 0.2f), 255);
	m_pRoot = background;

	cUIImageView* black = new cUIImageView("UI/BlackBackground.png", D3DXVECTOR3(0, 0, 0.0f), 120);
	m_pRoot->AddChild(black);
	
	/*cUIImageView* Lock = new cUIImageView("UI/PrisonBreak/Lock.png", D3DXVECTOR3(0, 0, 0), 200);
	Lock->SetScaling(D3DXVECTOR3(0.2f, 0.2f, 0.2f));
	m_pRoot->AddChild(Lock);*/


}

void cMiniGame_PrisonBreak::Update()
{
	m_pRoot->Update();
}

void cMiniGame_PrisonBreak::Render()
{
	m_pRoot->Render(m_pSprite);
}

