#include "stdafx.h"
#include "cUI_globalVarius.h"

cUI_globalVarius::cUI_globalVarius()
	:m_IsStartedGame(false)
	, m_IsInvenOpen(false)
{
	SetItemInfo();
}


cUI_globalVarius::~cUI_globalVarius()
{
}



void cUI_globalVarius::SetItemInfo()
{
	ITEMINFO itemInfo;
	itemInfo.Texture = g_pTextureManager->GetTexture("UI/Item/key_study.tga");
	itemInfo.ItemType = eITEMTYPE::KEY;
	m_mapItemInfo.insert(make_pair(StuffCode::STUFF_KEY1, itemInfo));

	itemInfo.ItemType = eITEMTYPE::KEY;
	itemInfo.Texture = g_pTextureManager->GetTexture("UI/Item/key_tomb.tga");
	m_mapItemInfo.insert(make_pair(StuffCode::STUFF_KEY2, itemInfo));

	itemInfo.ItemType = eITEMTYPE::KEY;
	itemInfo.Texture = g_pTextureManager->GetTexture("UI/Item/key_tomb_rusty.tga");
	m_mapItemInfo.insert(make_pair(StuffCode::STUFF_KEY3, itemInfo));

	itemInfo.ItemType = eITEMTYPE::KEY;
	itemInfo.Texture = g_pTextureManager->GetTexture("UI/Item/key_torture_chamber.tga");
	m_mapItemInfo.insert(make_pair(StuffCode::STUFF_KEY4, itemInfo));

	itemInfo.ItemType = eITEMTYPE::KEY;
	itemInfo.Texture = g_pTextureManager->GetTexture("UI/Item/key_tower.tga");
	m_mapItemInfo.insert(make_pair(StuffCode::STUFF_KEY5, itemInfo));

	itemInfo.ItemType = eITEMTYPE::COMBINE;
	itemInfo.Texture = g_pTextureManager->GetTexture("UI/Texture/maps/academy.png");
	m_mapItemInfo.insert(make_pair(StuffCode::STUFF_PAPER1, itemInfo));

	itemInfo.ItemType = eITEMTYPE::COMBINE;
	itemInfo.Texture = g_pTextureManager->GetTexture("UI/Texture/maps/game.png");
	m_mapItemInfo.insert(make_pair(StuffCode::STUFF_PAPER2, itemInfo));

	itemInfo.ItemType = eITEMTYPE::COMBINE;
	itemInfo.Texture = g_pTextureManager->GetTexture("UI/Texture/maps/seoul.png");
	m_mapItemInfo.insert(make_pair(StuffCode::STUFF_PAPER3, itemInfo));
}