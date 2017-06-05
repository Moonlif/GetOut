#include "stdafx.h"
#include "cInventory.h"
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIInvenItem.h"

cInventory::cInventory()
{
}


cInventory::~cInventory()
{
	m_pUIBase->Destroy();
	SAFE_RELEASE(m_pSprite);
}

void cInventory::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	SetInventoryBase();
}

void cInventory::Update()
{
	if (m_pUIBase) m_pUIBase->Update();

	//테스트용
	if (GetAsyncKeyState('0') & 0x0001)
	{

	}
}

void cInventory::Render()
{
	if (m_pUIBase) m_pUIBase->Render(m_pSprite);
}

void cInventory::SetInventoryBase()
{
	cUIImageView *BlackBackground = new cUIImageView("UI/BlackBackground.png", D3DXVECTOR3(0, 0, 0), 250);
	BlackBackground->SetTag(eUITAG::INVENTORY_IMAGE_BACKGROUND);
	m_pUIBase = BlackBackground;


	///-----------------------------------------------------------------------------------------------------
	//원래 이미지 크기의 배수들
	float MultipleWidth = 10.2f;
	float MultipleHeight = 2.53f;

	//오른쪽, 바텀 위치
	float Right = MultipleWidth * 64;
	float Bottom = MultipleHeight * 128;
 

	///-----------------------------------------------------------------
	//						메인 인벤토리창 이미지
	///-----------------------------------------------------------------
	cUIImageView *upLine = new cUIImageView("UI/Inventory/inventory_frame_generic_border_u.tga", D3DXVECTOR3(320, 50, 0), 250);
	upLine->SetScaling(D3DXVECTOR3(MultipleWidth, 1.0f, 1.0f));
	m_pUIBase->AddChild(upLine);

	cUIImageView *leftLine = new cUIImageView("UI/Inventory/inventory_frame_generic_border_l.tga", D3DXVECTOR3(-20, 20, 0), 250);
	leftLine->SetScaling(D3DXVECTOR3(1.0f, MultipleHeight, 1.0f));
	upLine->AddChild(leftLine);

	cUIImageView *BottomLine = new cUIImageView("UI/Inventory/inventory_frame_generic_border_d.tga", D3DXVECTOR3(0, Bottom, 0), 250);
	BottomLine->SetScaling(D3DXVECTOR3(MultipleWidth, 1.0f, 1.0f));
	upLine->AddChild(BottomLine);

	cUIImageView *RightLine = new cUIImageView("UI/Inventory/inventory_frame_generic_border_r.tga", D3DXVECTOR3(Right, 20, 0), 250);
	RightLine->SetScaling(D3DXVECTOR3(1.0f, MultipleHeight, 1.0f));
	upLine->AddChild(RightLine);
	
	cUIImageView *lu = new cUIImageView("UI/Inventory/inventory_frame_generic_corner_lu.tga", D3DXVECTOR3(-20, 0, 0), 250);
	upLine->AddChild(lu);

	cUIImageView *ru = new cUIImageView("UI/Inventory/inventory_frame_generic_corner_ru.tga", D3DXVECTOR3(Right, 0, 0), 250);
	upLine->AddChild(ru);

	cUIImageView *ld = new cUIImageView("UI/Inventory/inventory_frame_generic_corner_ld.tga", D3DXVECTOR3(-20, Bottom, 0), 250);
	upLine->AddChild(ld);

	cUIImageView *rd = new cUIImageView("UI/Inventory/inventory_frame_generic_corner_rd.tga", D3DXVECTOR3(Right, Bottom, 0), 250);
	upLine->AddChild(rd);

	///-----------------------------------------------------------------
	//					아이템창 21개 박스 이미지
	///-----------------------------------------------------------------
	D3DXVECTOR3 InveSize(2.3f, 1.1f, 1.0f);
	int			nAlpha = 150;

	//아이템창 1번설정
	
	cUIInvenItem *inven = new cUIInvenItem("UI/Inventory/inventory_oil_bg.tga", D3DXVECTOR3(- 5, 15, 0), nAlpha);
	inven->SetScaling(InveSize);
	inven->SetTag(eUITAG::INVENTORY_1);
	m_pInven = inven;
	upLine->AddChild(m_pInven);
	//이후 설정
	for (int i = 1; i < 21; ++i)
	{
		cUIInvenItem *inven1 = new cUIInvenItem("UI/Inventory/inventory_oil_bg.tga", D3DXVECTOR3((i % 7) * 95 + 320,(i / 7) * 105 + 50, 0), nAlpha);
		inven1->SetScaling(InveSize);
		inven1->SetTag(eUITAG::INVENTORY_1 + i);
		m_pInven->AddChild(inven1);
	}

	///-----------------------------------------------------------------
	//						조합 이미지
	///-----------------------------------------------------------------
	cUIImageView *combine1 = new cUIImageView("UI/Inventory/inventory_slot.tga", D3DXVECTOR3(20, 400, 0), 250);
	combine1->SetScaling(D3DXVECTOR3(2.0f, 1.5f, 1.0f));
	upLine->AddChild(combine1);

	cUIImageView *combine2 = new cUIImageView("UI/Inventory/inventory_slot.tga", D3DXVECTOR3(240, 400, 0), 250);
	combine2->SetScaling(D3DXVECTOR3(2.0f, 1.5f, 1.0f));
	upLine->AddChild(combine2);

	cUIImageView *combine3 = new cUIImageView("UI/Inventory/inventory_slot.tga", D3DXVECTOR3(460, 400, 0), 250);
	combine3->SetScaling(D3DXVECTOR3(2.0f, 1.5f, 1.0f));
	upLine->AddChild(combine3);

	///-----------------------------------------------------------------
	//						조합 텍스트
	///-----------------------------------------------------------------
	cUITextView* Text1 = new cUITextView("조합재료1", D3DXVECTOR3(340, 230, 0), D3DCOLOR_XRGB(255, 255, 255),
		ST_SIZEN(300, 100), 15, 20, 500);
	combine1->AddChild(Text1);

	cUITextView* Text2 = new cUITextView("조합재료2", D3DXVECTOR3(340, 230, 0), D3DCOLOR_XRGB(255, 255, 255),
		ST_SIZEN(300, 100), 15, 20, 500);
	combine2->AddChild(Text2);

	cUITextView* Text3 = new cUITextView("조합재료3", D3DXVECTOR3(340, 230, 0), D3DCOLOR_XRGB(255, 255, 255),
		ST_SIZEN(300, 100), 15, 20, 500);
	combine3->AddChild(Text3);

	///-----------------------------------------------------------------
	//						쓰레기통
	///-----------------------------------------------------------------
	cUIImageView *garbageCan = new cUIImageView("UI/Inventory/inventory_tinderboxes.tga", D3DXVECTOR3(80, 80, 0), 250);
	garbageCan->SetScaling(D3DXVECTOR3(1.7f, 1.7f, 1.0f));
	combine1->AddChild(garbageCan);

	///-----------------------------------------------------------------
	//						사용아이템
	///-----------------------------------------------------------------
	cUIImageView *UseInven = new cUIImageView("UI/Inventory/inventory_oil_fg.tga", D3DXVECTOR3(560, 50, 0), 250);
	UseInven->SetScaling(D3DXVECTOR3(3.1f, 1.5f, 1.0f));
	combine3->AddChild(UseInven);

	///-----------------------------------------------------------------
	//						사용 텍스트
	///-----------------------------------------------------------------
	cUITextView *UseInvenText = new cUITextView("사용 아이템", D3DXVECTOR3(470, 580, 0), D3DCOLOR_XRGB(255, 255, 255),
		ST_SIZEN(300, 100), 15, 20, 500);
	UseInven->AddChild(UseInvenText);
}

void cInventory::SetItem(StuffCode ItemName)
{
	
}
