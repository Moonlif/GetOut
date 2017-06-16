#include "stdafx.h"
#include "cInventory.h"
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIInvenItem.h"

cInventory::cInventory()
	: m_IsPick(false)
{
}


cInventory::~cInventory()
{
	m_pUIBase->Destroy();
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);

}

void cInventory::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
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
	

	//���𰡸� ���ϰ� ������ �����ϱ�
	if (m_IsPick) PickedRender();
}

//�κ��丮 ù ����
void cInventory::SetInventoryBase()
{
	cUIImageView *BlackBackground = new cUIImageView("UI/BlackBackground.png", D3DXVECTOR3(0, 0, 0.0f), 250);
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
	cUIImageView *upLine = new cUIImageView("UI/Inventory/inventory_frame_generic_border_u.tga", D3DXVECTOR3(270, 50, 0), 250);
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
	cUIInvenItem *inven = new cUIInvenItem("UI/BlackBackground.png", D3DXVECTOR3(-55, 15, 0), nAlpha);
	inven->SetScaling(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	inven->SetItemTexture(g_pTextureManager->GetTexture("UI/Inventory/inventory_oil_bg.tga"));
	m_pInven = inven;
	upLine->AddChild(m_pInven);
	//���� ����
	for (int i = 0; i < 21; ++i)
	{
		cUIInvenItem *inven1 = new cUIInvenItem("UI/Inventory/inventory_oil_bg.tga", D3DXVECTOR3((i % 7) * 95 + 320, (i / 7) * 105 + 50, 0), nAlpha);
		inven1->SetScaling(InveSize);
		inven1->SetTag(eUITAG::INVENTORY_1 + i);
		m_pInven->AddChild(inven1);
	}

	///-----------------------------------------------------------------
	//						���� �׵θ� �̹���
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
	//						���� �ؽ�Ʈ
	///-----------------------------------------------------------------
	cUITextView* Text1 = new cUITextView("�������1", D3DXVECTOR3(-30, 200, 0), D3DCOLOR_XRGB(255, 255, 255),
		ST_SIZEN(300, 100), 15, 20, 500);
	combine1->AddChild(Text1);

	cUITextView* Text2 = new cUITextView("�������2", D3DXVECTOR3(-30, 200, 0), D3DCOLOR_XRGB(255, 255, 255),
		ST_SIZEN(300, 100), 15, 20, 500);
	combine2->AddChild(Text2);

	cUITextView* Text3 = new cUITextView("�������3", D3DXVECTOR3(-30, 200, 0), D3DCOLOR_XRGB(255, 255, 255),
		ST_SIZEN(300, 100), 15, 20, 500);
	combine3->AddChild(Text3);

	///-----------------------------------------------------------------
	//						��������
	///-----------------------------------------------------------------
	cUIImageView *garbageCan = new cUIImageView("UI/Inventory/inventory_tinderboxes.tga", D3DXVECTOR3(-170, 420, 0), 250);
	garbageCan->SetScaling(D3DXVECTOR3(1.7f, 1.7f, 1.0f));
	garbageCan->SetTag(eUITAG::INVENTORY_GABAGE);
	upLine->AddChild(garbageCan);

	///-----------------------------------------------------------------
	//						��������
	///-----------------------------------------------------------------
	cUIInvenItem *UseInven = new cUIInvenItem("UI/Inventory/inventory_oil_fg.tga", D3DXVECTOR3(1070, 120, 0), 250);
	UseInven->SetScaling(D3DXVECTOR3(3.1f, 1.5f, 1.0f));
	UseInven->SetTag(eUITAG::INVENTORY_USINGITEM);
	m_pInven->AddChild(UseInven);

	///-----------------------------------------------------------------
	//						��� �ؽ�Ʈ
	///-----------------------------------------------------------------
	cUITextView *UseInvenText = new cUITextView("��� ������", D3DXVECTOR3(-40, 200, 0), D3DCOLOR_XRGB(255, 255, 255),
		ST_SIZEN(300, 100), 15, 20, 500);
	UseInven->AddChild(UseInvenText);

	///-----------------------------------------------------------------
	//						���� ����
	///-----------------------------------------------------------------
	cUIButton* CombineButton = new cUIButton("UI/button/BlackButton_Normal.png", "UI/button/BlackButton_Over.png",
		"UI/button/BlackButton_Down.png", D3DXVECTOR3(230, 60, 0));
	CombineButton->SetAlpha(100);
	CombineButton->SetScaling(D3DXVECTOR3(1.2f, 0.65f, 0.0f));
	CombineButton->SetDelegate(this);
	CombineButton->SetTag(eUITAG::INVENTORY_BUTTON_COMBINE);
	combine3->AddChild(CombineButton);

	cUITextView* CombineText = new cUITextView("�� ��", D3DXVECTOR3(845, 445, 0), D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f),
		ST_SIZEN(200, 100), 15, 30, 900);
	CombineText->SetTag(eUITAG::INVENTORY_TEXT_COMBINE);
	CombineButton->AddChild(CombineText);
}

//������ ����� �θ��� �Լ�
void cInventory::SetItem(StuffCode ItemName)
{
	cUIInvenItem* EmptyInven = m_pInven->FindEmptyInven();

	//������ Ǯ�� ��
	if (EmptyInven == NULL)
	{
		g_pData->TextOutWarningWord("������ �� á���ϴ�.");
		return;
	}
	EmptyInven->SetItemTexture(g_pUIvarius->m_mapItemInfo[ItemName].Texture);
	EmptyInven->SetItemType(g_pUIvarius->m_mapItemInfo[ItemName].ItemType);
	EmptyInven->SetrcItem(g_pUIvarius->m_mapItemInfo[ItemName].rc);
	EmptyInven->SetItemCode(ItemName);

	//������ ������ ����
	SaveInvenInfo();
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

			//���� ������ Ÿ�� ����
			g_pUIvarius->SetCurClickItemType(FirstClick->GetItemType());

			//�κ��� �������� ������ ����
			if (FirstClick->GetItemTexture() == NULL) return;

			//������ �ڵ� ����
			FirstCode = FirstClick->GetItemCode();

			//Ŭ���Ѱ� ������ �ʱ�ȭ
			FirstClick->SetItemTexture(NULL);
			FirstClick->SetItemType(eITEMTYPE::ITEMTYPE_NONE);
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
			///-------------------------------------------------------
			//			�ι�° Ŭ���� ���� ������ ���� ��
			///--------------------------------------------------------
			cUIObject* gabage = m_pUIBase->FindChildByTag(eUITAG::INVENTORY_GABAGE);
			if (PtInRect(&gabage->Getrc(), g_ptMouse))
			{
				//���콺�� �����ϴ� �� �ʱ�ȭ
				m_IsPick = false;
				m_pTexture = NULL;
				m_rcItem = { 0,0,0,0 };

				g_pData->DropItem(FirstCode);

				return;
			}
			///-------------------------------------------------------
			//			�ι�° Ŭ���� ���� �������� �� ��
			///--------------------------------------------------------
			cUIInvenItem* UsingIven = (cUIInvenItem*)m_pUIBase->FindChildByTag(eUITAG::INVENTORY_USINGITEM);
			if (PtInRect(&UsingIven->Getrc(), g_ptMouse))
			{
				//��밡���� �������� �� (����, Ű, ����)
				if (g_pUIvarius->GetCurClickItemType() == eITEMTYPE::ITEMTYPE_THROW ||
					g_pUIvarius->GetCurClickItemType() == eITEMTYPE::ITEMTYPE_KEY ||
					g_pUIvarius->GetCurClickItemType() == eITEMTYPE::ITEMTYPE_ATTACK)
				{
					g_pData->SetUseItem(FirstCode);
					cout << g_pData->GetUseItem() << endl;
				}
				//���Ұ����� �������� ��
				else
				{
					g_pData->TextOutWarningWord("��� �Ұ����� �������Դϴ�.");
					return;
				}

			}

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
				SecondClick->SetrcItem(g_pUIvarius->m_mapItemInfo[FirstCode].rc);
				SecondClick->SetItemCode(FirstCode);
			}
			///2��° Ŭ���� ���� �������� ���� ��
			else
			{
				//������ �ڵ� ����
				SecondCode = SecondClick->GetItemCode();

				//������ ��ȯ
				SecondClick->SetItemTexture(g_pUIvarius->m_mapItemInfo[FirstCode].Texture);
				SecondClick->SetItemType(g_pUIvarius->m_mapItemInfo[FirstCode].ItemType);
				SecondClick->SetrcItem(g_pUIvarius->m_mapItemInfo[FirstCode].rc);
				SecondClick->SetItemCode(FirstCode);

				FirstClick->SetItemTexture(g_pUIvarius->m_mapItemInfo[SecondCode].Texture);
				FirstClick->SetItemType(g_pUIvarius->m_mapItemInfo[SecondCode].ItemType);
				FirstClick->SetrcItem(g_pUIvarius->m_mapItemInfo[SecondCode].rc);
				FirstClick->SetItemCode(SecondCode);
			}

			//������ ������ ����
			//SaveInvenInfo();

			//���콺�� �����ϴ� �� �ʱ�ȭ
			m_IsPick = false;
			m_pTexture = NULL;
			m_rcItem = { 0,0,0,0 };
		}
	}
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

	//�̹��� ũ�⿡ ���� ����
	if (FirstCode == StuffCode::STUFF_PAPER1 || FirstCode == StuffCode::STUFF_PAPER2 ||
		FirstCode == StuffCode::STUFF_PAPER3)
	{
		//�����ϸ�
		D3DXMatrixScaling(&matS, 1.40f, 1.2f, 1.0f);
	}
	else
	{
		//�����ϸ�
		D3DXMatrixScaling(&matS, 1.60f, 1.8f, 1.0f);
	}

	//Ʈ�������̼�
	D3DXMatrixTranslation(&matT, g_ptMouse.x - width / 2, g_ptMouse.y - height, 0.0f);
	//���� ���ϱ�
	matWorld = matS * matT;
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(m_pTexture, &m_rcItem, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->End();
}

//���� � �κ��� Ŭ���ߴ���
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

StuffCode cInventory::GetPreparedUsingItem()
{
	cUIInvenItem* item = (cUIInvenItem*)m_pInven->FindChildByTag(eUITAG::INVENTORY_USINGITEM);
	return item->GetItemCode();
}

//�κ��� ������ ������ ����
void cInventory::SaveInvenInfo()
{
	for (int i = 0; i < m_pInven->GetChild().size(); ++i)
	{
		cUIInvenItem* p = (cUIInvenItem*)m_pInven->GetChild()[i];
		g_pData->SaveInvenInfo(i, p->GetItemCode());
	}
}

void cInventory::LoadInvenInfo()
{
	for (int i = 0; i < m_pInven->GetChild().size(); ++i)
	{
		//�κ�
		cUIInvenItem* p = (cUIInvenItem*)m_pInven->GetChild()[i];
		//����� �ڵ�
		StuffCode code = g_pData->LoadInvenInfo(i);
		//�ڵ�� �ҷ����� ������ ����
		ITEMINFO itemInfo;
		itemInfo = g_pUIvarius->m_mapItemInfo[code];

		p->SetItemTexture(itemInfo.Texture);
		p->SetItemType(itemInfo.ItemType);
		p->SetrcItem(itemInfo.rc);
		p->SetItemCode(code);
	}


}

void cInventory::OnClick(cUIButton * pSender)
{
	if (pSender->GetTag() == eUITAG::INVENTORY_BUTTON_COMBINE)
	{
		cUIInvenItem* combine1 = (cUIInvenItem*)m_pInven->FindChildByTag(eUITAG::INVENTORY_COMBINE_1);
		cUIInvenItem* combine2 = (cUIInvenItem*)m_pInven->FindChildByTag(eUITAG::INVENTORY_COMBINE_2);
		cUIInvenItem* combine3 = (cUIInvenItem*)m_pInven->FindChildByTag(eUITAG::INVENTORY_COMBINE_3);

		//���� ������ ��
		if (combine1->GetItemType() == eITEMTYPE::ITEMTYPE_COMBINE ||
			combine2->GetItemType() == eITEMTYPE::ITEMTYPE_COMBINE ||
			combine3->GetItemType() == eITEMTYPE::ITEMTYPE_COMBINE)
		{

			//���հ����� ��
			//������ ���վ����۵��� �� �ٸ���, �� ���� ������ �ʾ��� ��
			if ((combine1->GetItemCode() != combine2->GetItemCode() &&
				combine1->GetItemCode() != combine3->GetItemCode() &&
				combine2->GetItemCode() != combine3->GetItemCode()) &&
				(combine1->GetItemTexture() != NULL && combine2->GetItemTexture() != NULL &&
					combine3->GetItemTexture() != NULL))
			{
				g_pData->TextOutWarningWord("���� �Ϸ�");

				//���� ������ �ʱ�ȭ
				combine1->SetItemTexture(NULL);
				combine1->SetItemType(eITEMTYPE::ITEMTYPE_NONE);
				combine1->SetrcItem(RECT{ 0,0,0,0 });
				combine1->SetItemCode(StuffCode::STUFF_NONE);

				//���� ������ �ʱ�ȭ
				combine2->SetItemTexture(NULL);
				combine2->SetItemType(eITEMTYPE::ITEMTYPE_NONE);
				combine2->SetrcItem(RECT{ 0,0,0,0 });
				combine2->SetItemCode(StuffCode::STUFF_NONE);

				//���� ������ �ʱ�ȭ
				combine3->SetItemTexture(NULL);
				combine3->SetItemType(eITEMTYPE::ITEMTYPE_NONE);
				combine3->SetrcItem(RECT{ 0,0,0,0 });
				combine3->SetItemCode(StuffCode::STUFF_NONE);

				//������ ����
				SetItem(StuffCode::STUFF_KEY1);
				return;
			}
			else
			{
				g_pData->TextOutWarningWord("������ �Ұ��� �մϴ�.");
				return;
			}
		}
		else
		{
			g_pData->TextOutWarningWord("������ �Ұ��� �մϴ�.");
			return;
		}

	}
}
