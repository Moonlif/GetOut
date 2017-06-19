#include "stdafx.h"
#include "cUI_globalVarius.h"

cUI_globalVarius::cUI_globalVarius()
	:m_CurClickItemType(eITEMTYPE::ITEMTYPE_NONE)
{
	SetItemInfo();
	D3DXMatrixIdentity(&m_matCameraRot);
}


cUI_globalVarius::~cUI_globalVarius()
{
}



void cUI_globalVarius::SetSound()
{
	
}

void cUI_globalVarius::SetItemInfo()
{
	SetItem(eITEMTYPE::ITEMTYPE_KEY, StuffCode::STUFF_KEY1, "UI/Item/key_study.tga");
	SetItem(eITEMTYPE::ITEMTYPE_KEY, StuffCode::STUFF_KEY2, "UI/Item/key_tomb.tga");
	SetItem(eITEMTYPE::ITEMTYPE_KEY, StuffCode::STUFF_KEY3, "UI/Item/SeoulGameAcademy.png");

	SetItem(eITEMTYPE::ITEMTYPE_COMBINE, StuffCode::STUFF_PAPER1, "UI/Item/academy.png");
	SetItem(eITEMTYPE::ITEMTYPE_COMBINE, StuffCode::STUFF_PAPER2, "UI/Item/game.png");
	SetItem(eITEMTYPE::ITEMTYPE_COMBINE, StuffCode::STUFF_PAPER3, "UI/Item/seoul.png");

	SetItem(eITEMTYPE::ITEMTYPE_THROW, StuffCode::STUFF_BRICK1, "UI/Item/Brick.png");
	SetItem(eITEMTYPE::ITEMTYPE_THROW, StuffCode::STUFF_BRICK2, "UI/Item/Brick.png");
	SetItem(eITEMTYPE::ITEMTYPE_THROW, StuffCode::STUFF_BRICK3, "UI/Item/Brick.png");
	SetItem(eITEMTYPE::ITEMTYPE_THROW, StuffCode::STUFF_BRICK4, "UI/Item/Brick.png");
	SetItem(eITEMTYPE::ITEMTYPE_THROW, StuffCode::STUFF_BRICK5, "UI/Item/Brick.png");

	SetItem(eITEMTYPE::ITEMTYPE_ATTACK, StuffCode::STUFF_CROWBAR, "UI/Item/crowbar.tga");

	SetItem(eITEMTYPE::ITEMTYPE_ATTACK, StuffCode::STUFF_KEY3, "UI/Item/crowbar.tga");
}

void cUI_globalVarius::SetItem(eITEMTYPE itemType, StuffCode itemCode, char * fullPath)
{
	D3DXIMAGE_INFO stImageInfo;

	ITEMINFO itemInfo;
	itemInfo.Texture = g_pTextureManager->GetTexture(fullPath, &stImageInfo);
	itemInfo.ItemType = itemType;
	itemInfo.rc = { 0, 0, (int)stImageInfo.Width,  (int)stImageInfo.Height };
	m_mapItemInfo.insert(make_pair(itemCode, itemInfo));
}

ITEMINFO cUI_globalVarius::GetItemInfo(StuffCode ItemName)
{
	return m_mapItemInfo[ItemName];
}