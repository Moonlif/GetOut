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

	//������ �̵���
	MoveItem();
}

void cInventory::Render()
{
	if (m_pUIBase) m_pUIBase->Render(m_pSprite);
	if (g_pUIvarius->GetIsBagFull()) BagIsFull();

	//���𰡸� ���ϰ� ������ �����ϱ�
	if (m_IsPick) PickedRender();
}

//�κ��丮 ù ����
void cInventory::SetInventoryBase()
{
	cUIImageView *BlackBackground = new cUIImageView("UI/BlackBackground.png", D3DXVECTOR3(0, 0, 0), 250);
	BlackBackground->SetTag(eUITAG::INVENTORY_IMAGE_BACKGROUND);
	m_pUIBase = BlackBackground;


	///-----------------------------------------------------------------------------------------------------
	//���� �̹��� ũ���� �����
	float MultipleWidth = 10.2f;
	float MultipleHeight = 2.53f;

	//������, ���� ��ġ
	float Right = MultipleWidth * 64;
	float Bottom = MultipleHeight * 128;
 

	///-----------------------------------------------------------------
	//						���� �κ��丮â �̹���
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
	//					������â 21�� �ڽ� �̹���
	///-----------------------------------------------------------------
	D3DXVECTOR3 InveSize(2.3f, 1.1f, 1.0f);
	int			nAlpha = 150;

	//������â 1������
	
	cUIInvenItem *inven = new cUIInvenItem("UI/Inventory/inventory_oil_bg.tga", D3DXVECTOR3(- 5, 15, 0), nAlpha);
	inven->SetScaling(InveSize);
	inven->SetTag(eUITAG::INVENTORY_1);
	m_pInven = inven;
	upLine->AddChild(m_pInven);
	//���� ����
	for (int i = 1; i < 21; ++i)
	{
		cUIInvenItem *inven1 = new cUIInvenItem("UI/Inventory/inventory_oil_bg.tga", D3DXVECTOR3((i % 7) * 95 + 320,(i / 7) * 105 + 50, 0), nAlpha);
		inven1->SetScaling(InveSize);
		inven1->SetTag(eUITAG::INVENTORY_1 + i);
		m_pInven->AddChild(inven1);
	}

	///-----------------------------------------------------------------
	//						���� �׵θ� �̹���
	///-----------------------------------------------------------------

	cUIInvenItem *combine1 = new cUIInvenItem("UI/Inventory/inventory_slot.tga", D3DXVECTOR3(350, 420, 0), 250);
	combine1->SetScaling(D3DXVECTOR3(2.0f, 1.5f, 1.0f));
	combine1->SetTag(eUITAG::INVENTORY_COMBINE_1);
	m_pInven->AddChild(combine1);

	cUIInvenItem *combine2 = new cUIInvenItem("UI/Inventory/inventory_slot.tga", D3DXVECTOR3(570, 420, 0), 250);
	combine2->SetScaling(D3DXVECTOR3(2.0f, 1.5f, 1.0f));
	combine2->SetTag(eUITAG::INVENTORY_COMBINE_2);
	m_pInven->AddChild(combine2);

	cUIInvenItem *combine3 = new cUIInvenItem("UI/Inventory/inventory_slot.tga", D3DXVECTOR3(790, 420, 0), 250);
	combine3->SetScaling(D3DXVECTOR3(2.0f, 1.5f, 1.0f));
	combine3->SetTag(eUITAG::INVENTORY_COMBINE_3);
	m_pInven->AddChild(combine3);

	///-----------------------------------------------------------------
	//						���� �ؽ�Ʈ
	///-----------------------------------------------------------------
	cUITextView* Text1 = new cUITextView("�������1", D3DXVECTOR3(20, 200, 0), D3DCOLOR_XRGB(255, 255, 255),
		ST_SIZEN(300, 100), 15, 20, 500);
	combine1->AddChild(Text1);

	cUITextView* Text2 = new cUITextView("�������2", D3DXVECTOR3(20, 200, 0), D3DCOLOR_XRGB(255, 255, 255),
		ST_SIZEN(300, 100), 15, 20, 500);
	combine2->AddChild(Text2);

	cUITextView* Text3 = new cUITextView("�������3", D3DXVECTOR3(20, 200, 0), D3DCOLOR_XRGB(255, 255, 255),
		ST_SIZEN(300, 100), 15, 20, 500);
	combine3->AddChild(Text3);

	///-----------------------------------------------------------------
	//						��������
	///-----------------------------------------------------------------
	cUIImageView *garbageCan = new cUIImageView("UI/Inventory/inventory_tinderboxes.tga", D3DXVECTOR3(-200, 450, 0), 250);
	garbageCan->SetScaling(D3DXVECTOR3(1.7f, 1.7f, 1.0f));
	upLine->AddChild(garbageCan);

	///-----------------------------------------------------------------
	//						��������
	///-----------------------------------------------------------------
	cUIInvenItem *UseInven = new cUIInvenItem("UI/Inventory/inventory_oil_fg.tga", D3DXVECTOR3(1020, 400, 0), 250);
	UseInven->SetScaling(D3DXVECTOR3(3.1f, 1.5f, 1.0f));
	m_pInven->AddChild(UseInven);

	///-----------------------------------------------------------------
	//						��� �ؽ�Ʈ
	///-----------------------------------------------------------------
	cUITextView *UseInvenText = new cUITextView("��� ������", D3DXVECTOR3(470, 380, 0), D3DCOLOR_XRGB(255, 255, 255),
		ST_SIZEN(300, 100), 15, 20, 500);
	UseInven->AddChild(UseInvenText);
}

//������ ����� �θ��� �Լ�
void cInventory::SetItem(StuffCode ItemName)
{
	cUIInvenItem* EmptyInven = m_pInven->FindEmptyInven();

	//������ Ǯ�� ��
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

//���� �� ã�� �� �ؽ�Ʈ ����
void cInventory::BagIsFull()
{	 
	g_pFontManager->TextOut2D(m_pFontBagFull, "Bag is Full",550, 20, 750, 220);
}

//������ �ű��
void cInventory::MoveItem()
{
	static cUIInvenItem* FirstClick = NULL;
	static cUIInvenItem* SecondClick = NULL;
	eUITAG FirstTag = eUITAG::EMPTY;
	eUITAG SecondTag = eUITAG::EMPTY;
	//Ű�ٿ�
	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
	{
		//���� Ŭ���� �������� �ƹ��͵� ���� ��
		if (!m_IsPick)
		{
			//Ŭ���� �� ��ǥ�� �̿��� �±׹�ȣ ã��
			FirstTag = CarcCuruntPtInven();

			//���� �κ��丮�� �ƴѰ��� Ŭ���ߴٸ�
			if (FirstTag == eUITAG::EMPTY) return;

			//�±׹�ȣ�� Ŭ���� ���� UIObjectã��
			FirstClick = (cUIInvenItem*)m_pInven->FindChildByTag(FirstTag);

			//�κ��� �������� ������ ����
			if (FirstClick->GetItemTexture() == NULL) return;

			//������ �ڵ� ����
			FirstCode = FirstClick->GetItemCode();
			m_FirstInvenItemNum = FirstClick->GetItemNum();

			//Ŭ���Ѱ� ������ �ʱ�ȭ
			FirstClick->SetItemTexture(NULL);
			FirstClick->SetItemType(eITEMTYPE::ITEMTYPE_NONE);
			FirstClick->SetItemNum(0);
			FirstClick->SetrcItem(RECT{ 0,0,0,0 });
			FirstClick->SetItemCode(StuffCode::STUFF_NONE);

			//���콺�����Ϳ� �ؽ��� �����ϱ� ���� ��
			m_IsPick = true;

			//���콺�� ��� �ؽ���, ��Ʈ ����
			m_pTexture = g_pUIvarius->m_mapItemInfo[FirstCode].Texture;
			m_rcItem = g_pUIvarius->m_mapItemInfo[FirstCode].rc;
		}

		//Ŭ���� �������� ���� ��
		else if (m_IsPick)
		{
			//�� �� ��ǥ ����
			SecondTag = CarcCuruntPtInven();

			//���� �κ��丮�� �ƴѰ��� Ŭ���ߴٸ�
			if (SecondTag == eUITAG::EMPTY) return;

			//�±׹�ȣ�� Ŭ���� ���� UIObjectã��
			SecondClick = (cUIInvenItem*)m_pInven->FindChildByTag(SecondTag);

			///2��° Ŭ���� ���� �������� �ƹ��͵� ���� ��
			if (SecondClick->GetItemTexture() == NULL)
			{
				//������ ���� ���� Ŭ���� �� ������ ���� ����
				SecondClick->SetItemTexture(g_pUIvarius->m_mapItemInfo[FirstCode].Texture);
				SecondClick->SetItemType(g_pUIvarius->m_mapItemInfo[FirstCode].ItemType);
				SecondClick->SetItemNum(m_FirstInvenItemNum);
				SecondClick->SetrcItem(g_pUIvarius->m_mapItemInfo[FirstCode].rc);
				SecondClick->SetItemCode(FirstCode);
			}
			///2��° Ŭ���� ���� �������� ���� ��
			else
			{
				//������ �ڵ� ����
				SecondCode = SecondClick->GetItemCode();
				m_SecondInvenItemNum = SecondClick->GetItemNum();

				//������ ��ȯ
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
			
			//���콺�� �����ϴ� �� �ʱ�ȭ
			m_IsPick = false;
			m_pTexture = NULL;
			m_rcItem = { 0,0,0,0 };
		}
	}
	////Ű�ٿ���
	//if (GetKeyState(VK_LBUTTON) & 0x8000)
	//{
	//

	//}
	//if(GetKeyState(VK_LBUTTON) & 0x8000)
	//{
	//	if (m_IsPick)
	//	{
	//		//���� �� ��ǥ ����
	//		UpTag = CarcCuruntPtInven();

	//		//�±׹�ȣ�� Ŭ���� ���� UIObjectã��
	//		ClickUp = (cUIInvenItem*)m_pInven->FindChildByTag(UpTag);

	//		//Ŭ���� ���� �������� ���ٸ�
	//		if (ClickUp->GetItemTexture() == NULL)
	//		{
	//			//������ ���� ���� Ŭ���� �� ������ ���� ����
	//			ClickUp->SetItemTexture(g_pUIvarius->m_mapItemInfo[ClickDownCode].Texture);
	//			ClickUp->SetItemType(g_pUIvarius->m_mapItemInfo[ClickDownCode].ItemType);
	//			ClickUp->SetItemNum(m_ClickDownItemNum);
	//		}
	//		//���Ѱ��� �������� �ִٸ�
	//		else
	//		{
	//			//���Ѱ� ���� ����
	//			ClickUpCode = ClickUp->GetItemCode();
	//			m_ClickUpItemNum = ClickUp->GetItemNum();

	//			//�ٿ��Ѱ��� ���Ѱ��� ���� �־��ֱ�
	//			ClickDown->SetItemTexture(g_pUIvarius->m_mapItemInfo[ClickUpCode].Texture);
	//			ClickDown->SetItemType(g_pUIvarius->m_mapItemInfo[ClickUpCode].ItemType);
	//			ClickDown->SetItemNum(m_ClickUpItemNum);
	//		}

	//		

	//		m_IsPick = false;
	//	}
	//
	//}

}

//������ �� ���� �� ���콺�� ����
void cInventory::PickedRender()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	int width = m_rcItem.right - m_rcItem.left;
	int height = m_rcItem.bottom - m_rcItem.top;
	//�������̹���
	D3DXMATRIXA16 matS, matT, matWorld;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matWorld);
	//�����ϸ�
	D3DXMatrixScaling(&matS, 1.60f, 1.8f, 1.0f);
	//Ʈ�������̼�
	D3DXMatrixTranslation(&matT, g_ptMouse.x - width/ 2, g_ptMouse.y - height, 0.0f);
	//���� ���ϱ�
	matWorld = matS * matT;
	m_pSprite->SetTransform(&matWorld);

	m_pSprite->Draw(m_pTexture, &m_rcItem, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(200, 255, 255, 255));

	m_pSprite->End();
}

//���� � �κ��� Ŭ���ߴ���
eUITAG cInventory::CarcCuruntPtInven()
{
	

	int left = 314;
	int top = 64;

	//�κ� ���� Ŭ���ߴٸ� ����
	if (g_ptMouse.x < left || g_ptMouse.x > left + 7 * 95) return eUITAG::EMPTY;
	if (g_ptMouse.y < top || g_ptMouse.y > top + 3 * 105) return eUITAG::EMPTY;

	//�κ��丮 �� �˻�
	for (int i = 0; i < 21; ++i)
	{
		if (g_ptMouse.x >= left + 95 * (i % 7) &&
			g_ptMouse.x < left + 95 * (i % 7) + 95 &&
			g_ptMouse.y >= top + 105 * (i / 7) &&
			g_ptMouse.y < top + 105 * (i / 7) + 105)
		{
			switch (i)
			{
			case 0:
				return eUITAG::INVENTORY_1;
			case 1:
				return eUITAG::INVENTORY_2;
			case 2:
				return eUITAG::INVENTORY_3;
			case 3:
				return eUITAG::INVENTORY_4;
			case 4:
				return eUITAG::INVENTORY_5;
			case 5:
				return eUITAG::INVENTORY_6;
			case 6:
				return eUITAG::INVENTORY_7;
			case 7:
				return eUITAG::INVENTORY_8;
			case 8:
				return eUITAG::INVENTORY_9;
			case 9:
				return eUITAG::INVENTORY_10;
			case 10:
				return eUITAG::INVENTORY_11;
			case 11:
				return eUITAG::INVENTORY_12;
			case 12:
				return eUITAG::INVENTORY_13;
			case 13:
				return eUITAG::INVENTORY_14;
			case 14:
				return eUITAG::INVENTORY_15;
			case 15:
				return eUITAG::INVENTORY_16;
			case 16:
				return eUITAG::INVENTORY_17;
			case 17:
				return eUITAG::INVENTORY_18;
			case 18:
				return eUITAG::INVENTORY_19;
			case 19:
				return eUITAG::INVENTORY_20;
			case 20:
				return eUITAG::INVENTORY_21;
			default:
				return eUITAG::EMPTY;
			}
		}

	}


	

}
