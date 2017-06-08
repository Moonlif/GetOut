#include "stdafx.h"
#include "cInventory.h"
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIInvenItem.h"

cInventory::cInventory()
	:m_nBagIsFullTextOutCount(0)
	, m_IsPick(false)
	, m_FirstInvenItemNum(0)
	, m_SecondInvenItemNum(0)
{
}


cInventory::~cInventory()
{
	m_pUIBase->Destroy();
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pFontBagFull);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);

}

void cInventory::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	g_pFontManager->CreateFont2D(m_pFontBagFull, 15, 20, 500);
	SetInventoryBase();
}

void cInventory::Update()
{
	if (m_pUIBase) m_pUIBase->Update();

	//아이템 이동시
	MoveItem();
}

void cInventory::Render()
{
	if (m_pUIBase) m_pUIBase->Render(m_pSprite);
	if (g_pUIvarius->GetIsBagFull()) BagIsFull();

	//무언가를 픽하고 있으면 렌더하기
	if (m_IsPick) PickedRender();
}

//인벤토리 첫 세팅
void cInventory::SetInventoryBase()
{
	cUIImageView *BlackBackground = new cUIImageView("UI/BlackBackground.png", D3DXVECTOR3(0, 0, 1.0f), 250);
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
	cUIInvenItem *inven = new cUIInvenItem("UI/Inventory/key_laboratory.tga", D3DXVECTOR3(- 5, 15, 0), nAlpha);
	inven->SetItemTexture(g_pTextureManager->GetTexture("UI/Inventory/inventory_oil_bg.tga"));
	m_pInven = inven;
	upLine->AddChild(m_pInven);
	//이후 설정
	for (int i = 0; i < 21; ++i)
	{
		cUIInvenItem *inven1 = new cUIInvenItem("UI/Inventory/inventory_oil_bg.tga", D3DXVECTOR3((i % 7) * 95 + 320,(i / 7) * 105 + 50, 0), nAlpha);
		inven1->SetScaling(InveSize);
		inven1->SetTag(eUITAG::INVENTORY_1 + i);
		m_pInven->AddChild(inven1);
	}

	///-----------------------------------------------------------------
	//						조합 테두리 이미지
	///-----------------------------------------------------------------

	cUIInvenItem *combine1 = new cUIInvenItem("UI/Inventory/inventory_slot.tga", D3DXVECTOR3(325, 420, 0), 250);
	combine1->SetScaling(D3DXVECTOR3(2.0f, 1.5f, 1.0f));
	combine1->SetTag(eUITAG::INVENTORY_COMBINE_1);
	m_pInven->AddChild(combine1);

	cUIInvenItem *combine2 = new cUIInvenItem("UI/Inventory/inventory_slot.tga", D3DXVECTOR3(565, 420, 0), 250);
	combine2->SetScaling(D3DXVECTOR3(2.0f, 1.5f, 1.0f));
	combine2->SetTag(eUITAG::INVENTORY_COMBINE_2);
	m_pInven->AddChild(combine2);

	cUIInvenItem *combine3 = new cUIInvenItem("UI/Inventory/inventory_slot.tga", D3DXVECTOR3(805, 420, 0), 250);
	combine3->SetScaling(D3DXVECTOR3(2.0f, 1.5f, 1.0f));
	combine3->SetTag(eUITAG::INVENTORY_COMBINE_3);
	m_pInven->AddChild(combine3);

	///-----------------------------------------------------------------
	//						조합 텍스트
	///-----------------------------------------------------------------
	cUITextView* Text1 = new cUITextView("조합재료1", D3DXVECTOR3(20, 200, 0), D3DCOLOR_XRGB(255, 255, 255),
		ST_SIZEN(300, 100), 15, 20, 500);
	combine1->AddChild(Text1);

	cUITextView* Text2 = new cUITextView("조합재료2", D3DXVECTOR3(20, 200, 0), D3DCOLOR_XRGB(255, 255, 255),
		ST_SIZEN(300, 100), 15, 20, 500);
	combine2->AddChild(Text2);

	cUITextView* Text3 = new cUITextView("조합재료3", D3DXVECTOR3(20, 200, 0), D3DCOLOR_XRGB(255, 255, 255),
		ST_SIZEN(300, 100), 15, 20, 500);
	combine3->AddChild(Text3);

	///-----------------------------------------------------------------
	//						쓰레기통
	///-----------------------------------------------------------------
	cUIImageView *garbageCan = new cUIImageView("UI/Inventory/inventory_tinderboxes.tga", D3DXVECTOR3(-170, 420, 0), 250);
	garbageCan->SetScaling(D3DXVECTOR3(1.7f, 1.7f, 1.0f));
	garbageCan->SetTag(eUITAG::INVENTORY_GABAGE);
	upLine->AddChild(garbageCan);

	///-----------------------------------------------------------------
	//						사용아이템
	///-----------------------------------------------------------------
	cUIInvenItem *UseInven = new cUIInvenItem("UI/Inventory/inventory_oil_fg.tga", D3DXVECTOR3(1020, 420, 0), 250);
	UseInven->SetScaling(D3DXVECTOR3(3.1f, 1.5f, 1.0f));
	UseInven->SetTag(eUITAG::INVENTORY_USINGITEM);
	m_pInven->AddChild(UseInven);

	///-----------------------------------------------------------------
	//						사용 텍스트
	///-----------------------------------------------------------------
	cUITextView *UseInvenText = new cUITextView("사용 아이템", D3DXVECTOR3(10, 200, 0), D3DCOLOR_XRGB(255, 255, 255),
		ST_SIZEN(300, 100), 15, 20, 500);
	UseInven->AddChild(UseInvenText);
}

//아이템 습득시 부르는 함수
void cInventory::SetItem(StuffCode ItemName)
{
	cUIInvenItem* EmptyInven = m_pInven->FindEmptyInven();

	//가방이 풀일 때
	if (EmptyInven == NULL)
	{
		g_pUIvarius->SetIsBagFull(true);
		return;
	}
	EmptyInven->SetItemTexture(g_pUIvarius->m_mapItemInfo[ItemName].Texture);
	EmptyInven->SetItemNum(EmptyInven->GetItemNum() + 1);
	EmptyInven->SetItemType(g_pUIvarius->m_mapItemInfo[ItemName].ItemType);
	EmptyInven->SetrcItem(g_pUIvarius->m_mapItemInfo[ItemName].rc);
	EmptyInven->SetItemCode(ItemName);
}

//가방 꽉 찾을 시 텍스트 렌더
void cInventory::BagIsFull()
{	 
	g_pFontManager->TextOut2D(m_pFontBagFull, "Bag is Full",550, 20, 750, 220);
}

//아이템 옮기기
void cInventory::MoveItem()
{
	static cUIInvenItem* FirstClick = NULL;
	static cUIInvenItem* SecondClick = NULL;
	eUITAG FirstTag = eUITAG::EMPTY;
	eUITAG SecondTag = eUITAG::EMPTY;
	//키다운
	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
	{
		//현재 클릭된 아이템이 아무것도 없을 때
		if (!m_IsPick)
		{
			//클릭한 곳 좌표를 이용해 태그번호 찾기
			FirstTag = CarcCuruntPtInven();

			//만약 인벤토리가 아닌곳을 클릭했다면
			if (FirstTag == eUITAG::EMPTY) return;

			//태그번호로 클릭한 곳의 UIObject찾기
			FirstClick = (cUIInvenItem*)m_pInven->FindChildByTag(FirstTag);

			//인벤에 아이템이 없으면 리턴
			if (FirstClick->GetItemTexture() == NULL) return;

			//아이템 코드 저장
			FirstCode = FirstClick->GetItemCode();
			m_FirstInvenItemNum = FirstClick->GetItemNum();

			//클릭한곳 아이템 초기화
			FirstClick->SetItemTexture(NULL);
			FirstClick->SetItemType(eITEMTYPE::ITEMTYPE_NONE);
			FirstClick->SetItemNum(0);
			FirstClick->SetrcItem(RECT{ 0,0,0,0 });
			FirstClick->SetItemCode(StuffCode::STUFF_NONE);

			//마우스포인터에 텍스쳐 렌더하기 위한 값
			m_IsPick = true;

			//마우스에 띄울 텍스쳐, 렉트 설정
			m_pTexture = g_pUIvarius->m_mapItemInfo[FirstCode].Texture;
			m_rcItem = g_pUIvarius->m_mapItemInfo[FirstCode].rc;
		}

		//클릭된 아이템이 있을 때
		else if (m_IsPick)
		{
			///-------------------------------------------------------
			//			두번째 클릭한 곳이 쓰레기 통일 때
			///--------------------------------------------------------
			cUIObject* gabage = m_pUIBase->FindChildByTag(eUITAG::INVENTORY_GABAGE);
			if (PtInRect(&gabage->Getrc(), g_ptMouse))
			{
				//마우스에 렌더하는 값 초기화
				m_IsPick = false;
				m_pTexture = NULL;
				m_rcItem = { 0,0,0,0 };

				return;
			}
			///-------------------------------------------------------
			//			두번째 클릭한 곳이 사용아이템 일 때
			///--------------------------------------------------------
			cUIObject* UsingIven = m_pUIBase->FindChildByTag(eUITAG::INVENTORY_USINGITEM);
			if (PtInRect(&UsingIven->Getrc(), g_ptMouse))
			{
				//사용가능한 아이템일 때

				//사용불가능한 아이템일 때
				return;
			}



			//한 곳 좌표 저장
			SecondTag = CarcCuruntPtInven();

			//만약 인벤토리가 아닌곳을 클릭했다면
			if (SecondTag == eUITAG::EMPTY) return;

			//태그번호로 클릭한 곳의 UIObject찾기
			SecondClick = (cUIInvenItem*)m_pInven->FindChildByTag(SecondTag);

			///2번째 클릭한 곳의 아이템이 아무것도 없을 떄
			if (SecondClick->GetItemTexture() == NULL)
			{
				//지정된 곳에 이전 클릭한 곳 아이템 정보 저장
				SecondClick->SetItemTexture(g_pUIvarius->m_mapItemInfo[FirstCode].Texture);
				SecondClick->SetItemType(g_pUIvarius->m_mapItemInfo[FirstCode].ItemType);
				SecondClick->SetItemNum(m_FirstInvenItemNum);
				SecondClick->SetrcItem(g_pUIvarius->m_mapItemInfo[FirstCode].rc);
				SecondClick->SetItemCode(FirstCode);
			}
			///2번째 클릭한 곳의 아이템이 있을 때
			else
			{
				//아이템 코드 저장
				SecondCode = SecondClick->GetItemCode();
				m_SecondInvenItemNum = SecondClick->GetItemNum();

				//아이템 교환
				SecondClick->SetItemTexture(g_pUIvarius->m_mapItemInfo[FirstCode].Texture);
				SecondClick->SetItemType(g_pUIvarius->m_mapItemInfo[FirstCode].ItemType);
				SecondClick->SetItemNum(m_FirstInvenItemNum);
				SecondClick->SetrcItem(g_pUIvarius->m_mapItemInfo[FirstCode].rc);
				SecondClick->SetItemCode(FirstCode);

				FirstClick->SetItemTexture(g_pUIvarius->m_mapItemInfo[SecondCode].Texture);
				FirstClick->SetItemType(g_pUIvarius->m_mapItemInfo[SecondCode].ItemType);
				FirstClick->SetItemNum(m_SecondInvenItemNum);
				FirstClick->SetrcItem(g_pUIvarius->m_mapItemInfo[SecondCode].rc);
				FirstClick->SetItemCode(SecondCode);
			}
			
			//마우스에 렌더하는 값 초기화
			m_IsPick = false;
			m_pTexture = NULL;
			m_rcItem = { 0,0,0,0 };
		}
	}
}

//아이템 픽 했을 때 마우스에 렌더
void cInventory::PickedRender()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	int width = m_rcItem.right - m_rcItem.left;
	int height = m_rcItem.bottom - m_rcItem.top;
	//아이템이미지
	D3DXMATRIXA16 matS, matT, matWorld;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matWorld);

	//이미지 크기에 따른 렌더
	if (FirstCode == StuffCode::STUFF_PAPER1 || FirstCode == StuffCode::STUFF_PAPER2 ||
		FirstCode == StuffCode::STUFF_PAPER3)
	{
		//스케일링
		D3DXMatrixScaling(&matS, 1.40f, 1.2f, 1.0f);	
	}
	else
	{
		//스케일링
		D3DXMatrixScaling(&matS, 1.60f, 1.8f, 1.0f);		
	}
	//트렌스레이션
	D3DXMatrixTranslation(&matT, g_ptMouse.x - width / 2, g_ptMouse.y - height, 0.0f);
	//월드 구하기
	matWorld = matS * matT;
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(m_pTexture, &m_rcItem, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->End();
}

//현재 어떤 인벤을 클릭했는지
eUITAG cInventory::CarcCuruntPtInven()
{
	for (int i = 0; i < m_pInven->GetChild().size(); ++i)
	{
		if (PtInRect(&m_pInven->GetChild()[i]->Getrc(), g_ptMouse))
		{
			return (eUITAG)m_pInven->GetChild()[i]->GetTag();
		}
	}
}
