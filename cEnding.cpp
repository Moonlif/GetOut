#include "stdafx.h"
#include "cEnding.h"
#include "cUITextView.h"
#include "cUIImageView.h"


cEnding::cEnding()
{
}


cEnding::~cEnding()
{
	m_pRoot->Destroy();
	SAFE_RELEASE(m_pSprite);
}

void cEnding::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	m_pText = "±èÁ¤ÈÆ \n¼Õ¿µÇö\nÃÖÁøÈ£\n±è±Õ¿µ\nÀ¯Áö»ó";

	cUIImageView* backGround = new cUIImageView("UI/BlackBackground.png", D3DXVECTOR3(0, 0, 0), 1.0f);
	m_pRoot = backGround;


	cUITextView* text = new cUITextView(m_pText, D3DXVECTOR3(0, WINSIZEY, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		ST_SIZEN(WINSIZEX, WINSIZEY * 10), 30, 45, 900);
	text->SetDrawTextFormat(DT_CENTER | DT_TOP);
	text->SetTag(eUITAG::ENDING_TEXT);
	m_pRoot->AddChild(text);


}

void cEnding::Update()
{
	cUITextView* text1 = (cUITextView*)m_pRoot->FindChildByTag(eUITAG::ENDING_TEXT);
	
	static D3DXVECTOR3 pos = text1->GetPosition();

	pos.y--;
	
	text1->SetPosition(pos);

	if (m_pRoot) m_pRoot->Update();
}

void cEnding::Render()
{

	if (m_pRoot) m_pRoot->Render(m_pSprite);
}

