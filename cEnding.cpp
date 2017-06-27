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

	//���� �ϴ���
	m_pText = "   ������\n    - ���� ��ȹ\n    - ������Ʈ ��ȣ�ۿ� �� ��ŷ ����\n    - ������Ʈ ��ƼŬ ����\n\n\n";
	m_pText += "   �տ���\n    - ������ & ĳ���ͼ��� & ������ ����\n    - �κ��丮 UI ����\n    - ä�� �ý��� ����\n\n\n";
	m_pText += "   ����ȣ\n    - �� & �� ������Ʈ ����\n    - ĳ���� �̵� �Ǵ� ����\n\n\n";
	m_pText += "   ��տ�\n    - ĳ���� Ŭ���� ����\n    - ī�޶� ����\n    - ��ī�̹ڽ� ����\n\n\n";
	m_pText += "   ������\n    - ����\n    - Ŭ���̾�Ʈ ��� ����\n\n";


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

	//�ؽ�Ʈ�� ���� ���� �ö�
	pos.y -= CREDITSPEED;
	
	text1->SetPosition(pos);

	if (m_pRoot) m_pRoot->Update();
}

void cEnding::Render()
{
	if (m_pRoot) m_pRoot->Render(m_pSprite);
}

