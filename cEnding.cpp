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

	//각각 하는일
	m_pText = "   김정훈\n    - 게임 기획\n    - 오브젝트 상호작용 및 피킹 구현\n    - 오브젝트 파티클 구현\n\n\n";
	m_pText += "   손영현\n    - 오프닝 & 캐릭터선택 & 엔딩씬 구현\n    - 인벤토리 UI 구현\n    - 채팅 시스템 구현\n\n\n";
	m_pText += "   최진호\n    - 맵 & 맵 오브젝트 구현\n    - 캐릭터 이동 판단 구현\n\n\n";
	m_pText += "   김균영\n    - 캐릭터 클래스 구현\n    - 카메라 조작\n    - 스카이박스 구현\n\n\n";
	m_pText += "   유지상\n    - 서버\n    - 클라이언트 통신 설계\n\n";


	cUIImageView* backGround = new cUIImageView("UI/BlackBackground.png", D3DXVECTOR3(0, 0, 0), 1.0f);
	m_pRoot = backGround;

	cUITextView* text = new cUITextView(m_pText, D3DXVECTOR3(0, WINSIZEY, 0), D3DXCOLOR(0.2f, 0.2f, 0.3f, 1.0f),
		ST_SIZEN(WINSIZEX, WINSIZEY * 10), 30, 60, 900);
	text->SetDrawTextFormat(DT_LEFT | DT_TOP);

	text->SetTag(eUITAG::ENDING_TEXT);
	m_pRoot->AddChild(text);

}

void cEnding::Update()
{
	cUITextView* text1 = (cUITextView*)m_pRoot->FindChildByTag(eUITAG::ENDING_TEXT);
	
	static D3DXVECTOR3 pos = text1->GetPosition();

	//텍스트가 점점 위로 올라감
	pos.y -= CREDITSPEED;
	
	text1->SetPosition(pos);

	if (m_pRoot) m_pRoot->Update();
}

void cEnding::Render()
{
	if (m_pRoot) m_pRoot->Render(m_pSprite);
}

