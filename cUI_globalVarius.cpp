#include "stdafx.h"
#include "cUI_globalVarius.h"


//STUFF_BRICK,
//STUFF_CROWBAR,
//STUFF_KEY1,
//STUFF_KEY2,
//STUFF_KEY3,
//STUFF_KEY4,
//STUFF_KEY5,
//
//STUFF_PAPER1,
//STUFF_PAPER2,

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
	//itemInfo.tagName = StuffCode::STUFF_KEY1;
	//m_mapItemInfo.insert(make_pair(StuffCode,))

	itemInfo.ItemType = eITEMTYPE::KEY;
	itemInfo.Texture = g_pTextureManager->GetTexture("UI/Item/key_tomb.tga");
	//itemInfo.tagName = StuffCode::STUFF_KEY2;

	itemInfo.ItemType = eITEMTYPE::KEY;
	itemInfo.Texture = g_pTextureManager->GetTexture("UI/Item/key_tomb_rusty.tga");
	//itemInfo.tagName = StuffCode::STUFF_KEY3;

	itemInfo.ItemType = eITEMTYPE::KEY;
	itemInfo.Texture = g_pTextureManager->GetTexture("UI/Item/key_torture_chamber.tga");
	//itemInfo.tagName = StuffCode::STUFF_KEY4;

	itemInfo.ItemType = eITEMTYPE::KEY;
	itemInfo.Texture = g_pTextureManager->GetTexture("UI/Item/key_tower.tga");
	//itemInfo.tagName = StuffCode::STUFF_KEY5;

	itemInfo.ItemType = eITEMTYPE::COMBINE;
	itemInfo.Texture = g_pTextureManager->GetTexture("UI/Texture/maps/academy.png");

	itemInfo.ItemType = eITEMTYPE::COMBINE;
	itemInfo.Texture = g_pTextureManager->GetTexture("UI/Texture/maps/game.png");

	itemInfo.ItemType = eITEMTYPE::COMBINE;
	itemInfo.Texture = g_pTextureManager->GetTexture("UI/Texture/maps/seoul.png");
}