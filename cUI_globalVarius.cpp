#include "stdafx.h"
#include "cUI_globalVarius.h"

cUI_globalVarius::cUI_globalVarius()
	:m_IsBagFull(false)
{
	SetItemInfo();
}


cUI_globalVarius::~cUI_globalVarius()
{
}



void cUI_globalVarius::SetItemInfo()
{
	D3DXIMAGE_INFO stImageInfo;
	int width, height;

	ITEMINFO itemInfo;
	itemInfo.Texture = g_pTextureManager->GetTexture("UI/Item/key_study.tga", &stImageInfo);	
	itemInfo.ItemType = eITEMTYPE::ITEMTYPE_KEY;
	width = stImageInfo.Width;
	height = stImageInfo.Height;
	itemInfo.rc = { 0, 0, width, height };
	m_mapItemInfo.insert(make_pair(StuffCode::STUFF_KEY1, itemInfo));

	itemInfo.ItemType = eITEMTYPE::ITEMTYPE_KEY;
	itemInfo.Texture = g_pTextureManager->GetTexture("UI/Item/key_tomb.tga", &stImageInfo);
	width = stImageInfo.Width;
	height = stImageInfo.Height;
	itemInfo.rc = { 0, 0, width, height };
	m_mapItemInfo.insert(make_pair(StuffCode::STUFF_KEY2, itemInfo));

	itemInfo.ItemType = eITEMTYPE::ITEMTYPE_KEY;
	itemInfo.Texture = g_pTextureManager->GetTexture("UI/Item/key_tomb_rusty.tga", &stImageInfo);
	width = stImageInfo.Width;
	height = stImageInfo.Height;
	itemInfo.rc = { 0, 0, width, height };
	m_mapItemInfo.insert(make_pair(StuffCode::STUFF_KEY3, itemInfo));

	itemInfo.ItemType = eITEMTYPE::ITEMTYPE_KEY;
	itemInfo.Texture = g_pTextureManager->GetTexture("UI/Item/key_torture_chamber.tga", &stImageInfo);
	width = stImageInfo.Width;
	height = stImageInfo.Height;
	itemInfo.rc = { 0, 0, width, height };
	m_mapItemInfo.insert(make_pair(StuffCode::STUFF_KEY4, itemInfo));

	itemInfo.ItemType = eITEMTYPE::ITEMTYPE_KEY;
	itemInfo.Texture = g_pTextureManager->GetTexture("UI/Item/key_tower.tga", &stImageInfo);
	width = stImageInfo.Width;
	height = stImageInfo.Height;
	itemInfo.rc = { 0, 0, width, height };
	m_mapItemInfo.insert(make_pair(StuffCode::STUFF_KEY5, itemInfo));

	itemInfo.ItemType = eITEMTYPE::ITEMTYPE_COMBINE;
	itemInfo.Texture = g_pTextureManager->GetTexture("UI/Item/academy.png", &stImageInfo);
	width = stImageInfo.Width;
	height = stImageInfo.Height;
	itemInfo.rc = { 0, 0, width, height };
	m_mapItemInfo.insert(make_pair(StuffCode::STUFF_PAPER1, itemInfo));

	itemInfo.ItemType = eITEMTYPE::ITEMTYPE_COMBINE;
	itemInfo.Texture = g_pTextureManager->GetTexture("UI/Item/game.png", &stImageInfo);
	width = stImageInfo.Width;
	height = stImageInfo.Height;
	itemInfo.rc = { 0, 0, width, height };
	m_mapItemInfo.insert(make_pair(StuffCode::STUFF_PAPER2, itemInfo));

	itemInfo.ItemType = eITEMTYPE::ITEMTYPE_COMBINE;
	itemInfo.Texture = g_pTextureManager->GetTexture("UI/Item/seoul.png", &stImageInfo);
	width = stImageInfo.Width;
	height = stImageInfo.Height;
	itemInfo.rc = { 0, 0, width, height };
	m_mapItemInfo.insert(make_pair(StuffCode::STUFF_PAPER3, itemInfo));
}


ITEMINFO cUI_globalVarius::GetItemInfo(StuffCode ItemName)
{
	return m_mapItemInfo[ItemName];
}