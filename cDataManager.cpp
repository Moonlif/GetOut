#include "stdafx.h"
#include "cDataManager.h"
#include "cMtlTex.h"

#include "cObjLoader.h"

cDataManager::cDataManager()
	: m_IsInvenOpen(false)
	, m_IsStartedGame(false)
	, m_IsOnChat(false)
	, m_PickUpItemCode(StuffCode::STUFF_NONE)
	, m_IsLoadItem(false)
	, m_isHandOn(false)
	, m_bValve1(false)
	, m_bValve2(false)
	, m_n2FValve1Count(0)
	, m_n2FValve2Count(0)
	, m_nBrickCount(0)
	, m_nPlayer(0)
	, m_IsCollisionWall(false)
{

	for (int i = 0; i < TOTALINVENSIZE; ++i)
	{
		m_arrSaveInvenItem[i] = StuffCode::STUFF_NONE;
		m_arrLoadInvenItem[i] = StuffCode::STUFF_NONE;
	}
}

cDataManager::~cDataManager()
{
}

void cDataManager::Setup()
{

	//사운드 추가
	AddSound();

	//정훈 - 충돌 오브젝트 정보
	{
		cObjLoader loader;

		m_mapStuffMesh[STUFF_CROWBAR] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_CROWBAR], "Objects/clickable", "crowbar.obj", 1);
		m_mapStuffMesh[STUFF_PAPER1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_PAPER1], "Objects/clickable", "paper1.obj", 1);
		m_mapStuffMesh[STUFF_PAPER2] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_PAPER2], "Objects/clickable", "paper2.obj", 1);
		m_mapStuffMesh[STUFF_PAPER3] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_PAPER3], "Objects/clickable", "paper2.obj", 1);
		m_mapStuffMesh[STUFF_KEY1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_KEY1], "Objects/clickable", "key1.obj", 1);
		m_mapStuffMesh[STUFF_KEY2] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_KEY2], "Objects/clickable", "key2.obj", 1);
		m_mapStuffMesh[STUFF_KEY3] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_KEY3], "Objects/clickable", "key3.obj", 1);
		m_mapStuffMesh[STUFF_BRICK1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_BRICK1], "Objects/clickable", "brick.obj", 1);
		m_mapStuffMesh[STUFF_BRICK2] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_BRICK2], "Objects/clickable", "brick.obj", 1);
		m_mapStuffMesh[STUFF_BRICK3] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_BRICK3], "Objects/clickable", "brick.obj", 1);
		m_mapStuffMesh[STUFF_BRICK4] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_BRICK4], "Objects/clickable", "brick.obj", 1);
		m_mapStuffMesh[STUFF_BRICK5] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_BRICK5], "Objects/clickable", "brick.obj", 1);

		m_mapStuffMesh[STUFF_BOARDBLOCK] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_BOARDBLOCK], "Objects/clickable", "boardblock.obj", 1);
		m_mapStuffMesh[STUFF_BOX1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_BOX1], "Objects/clickable", "box1.obj", 1);
		m_mapStuffMesh[STUFF_BRICK] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_BRICK], "Objects/clickable", "brick.obj", 1);
		m_mapStuffMesh[STUFF_BRICKPILE] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_BRICKPILE], "Objects/clickable", "brickpile.obj", 1);
		m_mapStuffMesh[STUFF_CHEST2] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_CHEST2], "Objects/clickable", "chest2.obj", 1);
		m_mapStuffMesh[STUFF_CHEST3] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_CHEST3], "Objects/clickable", "chest3.obj", 1);
		m_mapStuffMesh[STUFF_EMPTYBOX] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_EMPTYBOX], "Objects/clickable", "emptybox.obj", 1);
		m_mapStuffMesh[STUFF_TRAP] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_TRAP], "Objects/clickable", "trap.obj", 0);
		m_mapStuffMesh[STUFF_VALVE1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_VALVE1], "Objects/clickable", "valve1.obj", 1);
		m_mapStuffMesh[STUFF_VALVE2] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_VALVE2], "Objects/clickable", "valve1.obj", 1);
		m_mapStuffMesh[STUFF_WOOD1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_WOOD1], "Objects/clickable", "wood1.obj", 1);
		m_mapStuffMesh[STUFF_WOOD2] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_WOOD2], "Objects/clickable", "wood2.obj", 1);
		m_mapStuffMesh[STUFF_WOOD3] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_WOOD3], "Objects/clickable", "wood3.obj", 1);
		m_mapStuffMesh[STUFF_WOODBOARD1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_WOODBOARD1], "Objects/clickable", "woodboard1.obj", 1);
		m_mapStuffMesh[STUFF_WOODBOARD2] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_WOODBOARD2], "Objects/clickable", "woodboard2.obj", 1);
		m_mapStuffMesh[STUFF_BUTTON1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_BUTTON1], "Objects/clickable", "button1.obj", 1);
		m_mapStuffMesh[STUFF_BUTTON2] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_BUTTON2], "Objects/clickable", "button2.obj", 1);
		m_mapStuffMesh[STUFF_BUTTON3] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_BUTTON3], "Objects/clickable", "button1.obj", 1);
		m_mapStuffMesh[STUFF_BUTTON4] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_BUTTON4], "Objects/clickable", "button2.obj", 1);

		m_mapStuffMesh[STUFF_DOOR_PRISON] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_DOOR_PRISON], "Objects/clickable/door", "PrisonDoor3.obj", 1);
		m_mapStuffMesh[STUFF_DOOR_1STROOM] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_DOOR_1STROOM], "Objects/clickable/door", "RoomDoor.obj", 1);
		m_mapStuffMesh[STUFF_DOOR_1STTOILET] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_DOOR_1STTOILET], "Objects/clickable/door", "PrisonDoor2.obj", 1);
		m_mapStuffMesh[STUFF_DOOR_2NDROOM1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_DOOR_2NDROOM1], "Objects/clickable/door", "WoodDoor.obj", 1);
		m_mapStuffMesh[STUFF_DOOR_2NDROOM2] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_DOOR_2NDROOM2], "Objects/clickable/door", "PrisonDoor.obj", 1);
		m_mapStuffMesh[STUFF_DOOR_FINAL] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_DOOR_FINAL], "Objects/clickable/door", "PrisonDoor2.obj", 1);
	}

	//정훈 - 맵 정보
	{
		for (int i = 0; i < SWITCH_LASTNUM; ++i)
		{
			m_bStuffSwitch[i] = false;
		}

		m_bStuffSwitch[SWITCH_ONMAP_CROWBAR] = true;
		m_vStuffPosition[SWITCH_ONMAP_CROWBAR] = D3DXVECTOR3(-40, 12.2f, 12);
		m_vStuffRotation[SWITCH_ONMAP_CROWBAR] = D3DXVECTOR3(0, D3DX_PI / 2.2f, 0);

		m_bStuffSwitch[SWITCH_ONMAP_PAPER1] = true;
		m_vStuffPosition[SWITCH_ONMAP_PAPER1] = D3DXVECTOR3(10, 0.7f, 18);
		m_vStuffRotation[SWITCH_ONMAP_PAPER1] = D3DXVECTOR3(0, 0, 0);

		m_bStuffSwitch[SWITCH_ONMAP_PAPER2] = true;
		m_vStuffPosition[SWITCH_ONMAP_PAPER2] = D3DXVECTOR3(-38, 12.7f, -6);
		m_vStuffRotation[SWITCH_ONMAP_PAPER2] = D3DXVECTOR3(0, 0, 0);

		m_bStuffSwitch[SWITCH_ONMAP_PAPER3] = true;
		m_vStuffPosition[SWITCH_ONMAP_PAPER3] = D3DXVECTOR3(-17.5f, 27.7f, -10.5f);
		m_vStuffRotation[SWITCH_ONMAP_PAPER3] = D3DXVECTOR3(0, 0, 0);

		m_bStuffSwitch[SWITCH_ONMAP_KEY1] = true;
		m_vStuffPosition[SWITCH_ONMAP_KEY1] = D3DXVECTOR3(-14.0f, 0.3f, 1.5f);
		m_vStuffRotation[SWITCH_ONMAP_KEY1] = D3DXVECTOR3(0, D3DX_PI / 2.5f, 0);

		m_bStuffSwitch[SWITCH_ONMAP_KEY2] = true;
		m_vStuffPosition[SWITCH_ONMAP_KEY2] = D3DXVECTOR3(-30, 12.3f, -13);
		m_vStuffRotation[SWITCH_ONMAP_KEY2] = D3DXVECTOR3(0, 0.3f, 0);

		m_bStuffSwitch[SWITCH_ONMAP_KEY3] = false;
		m_vStuffPosition[SWITCH_ONMAP_KEY3] = D3DXVECTOR3(0, 0, 0);
		m_vStuffRotation[SWITCH_ONMAP_KEY3] = D3DXVECTOR3(0, 0, 0);

		for (int i = SWITCH_ONMAP_BRICK1; i <= SWITCH_ONMAP_BRICK5; ++i)
		{
			m_bStuffSwitch[i] = false;
			m_vStuffPosition[i] = D3DXVECTOR3(0, 0, 0);
			m_vStuffRotation[i] = D3DXVECTOR3(0, 0, 0);
		}

		m_vStuffPosition[SWITCH_FIRSTFLOOR_WOODBOARD1] = D3DXVECTOR3(-7, 12, 19.5f);

		m_bValve1 = false;
		m_bValve2 = false;
		m_n2FValve1Count = 0;
		m_n2FValve2Count = 0;
		m_nBrickCount = 0;
	}
}

void cDataManager::Destroy()
{
	//정훈
	for each (auto it in m_mapStuffMesh)
	{
		SAFE_RELEASE(it.second);
	}
	for each(auto it in m_mapStuffVecMtlTex)
	{
		for (int i = 0; i < it.second.size(); i++)
		{
			SAFE_RELEASE(it.second[i]);
		}
	}
}

void cDataManager::Chat(string Text)
{
	m_listChat_SEND.push_back(Text);
}

string cDataManager::GetText()
{
	if (m_listChat_SEND.empty())
	{
		string size;
		size = m_listChat_SEND.size();
		return size;
	}

	string Text = m_listChat_SEND.front();
	m_listChat_SEND.pop_front();
	return Text;
}

//아이템 획득 및 드랍
void cDataManager::DropItem(StuffCode itemCode)
{
	if (itemCode < STUFF_CROWBAR || itemCode > STUFF_BRICK5) return;

	m_bStuffSwitch[itemCode] = true;
	m_vStuffPosition[itemCode] = m_vPosition1P;
	m_vStuffRotation[itemCode] = D3DXVECTOR3(0, m_vRotation1P, 0);

	if (itemCode == STUFF_KEY1 || itemCode == STUFF_KEY2 || itemCode == STUFF_KEY3) g_pSoundManager->Play("drop_key", 0.5f);
	else g_pSoundManager->Play("drop_generic", 0.4f);
}

void cDataManager::GetItem(StuffCode itemCode)
{
	if (itemCode < STUFF_CROWBAR || itemCode > STUFF_BRICK5) return;

	m_bStuffSwitch[itemCode] = false;
	m_PickUpItemCode = itemCode;

	if (itemCode == STUFF_CROWBAR) g_pSoundManager->Play("pick_knife", 0.5f);
	else if (itemCode == STUFF_KEY1 || itemCode == STUFF_KEY2 || itemCode == STUFF_KEY3) g_pSoundManager->Play("pick_key", 0.5f);
	else if (itemCode == STUFF_PAPER1 || itemCode == STUFF_PAPER2 || itemCode == STUFF_PAPER3) g_pSoundManager->Play("pick_paper", 0.5f);
	else g_pSoundManager->Play("pick_generic", 0.5f);
}

//경고문구 띄우기
void cDataManager::TextOutWarningWord(string str)
{
	m_isWarning = true;
	m_strWarningWord = str;
}

//사운드 추가
void cDataManager::AddSound()
{
	//영현
	g_pSoundManager->AddSound("StartScene", "Sound/Background/StartScene.ogg", true, true);
	g_pSoundManager->AddSound("LoadingScene", "Sound/Background/LoadingScene.ogg", true, true);
	g_pSoundManager->AddSound("CharacterSelectScene", "Sound/Background/CharacterSelectScene.ogg", true, true);

	//진호
	g_pSoundManager->AddSound("break_wood", "Sound/EffectSound/break_wood.ogg", true, false);
	g_pSoundManager->AddSound("BackGround", "Sound/BackGround/BackGround.ogg", true, true);
	
	//정훈 사운드 정보
	{
		g_pSoundManager->AddSound("pick_generic", "Sound/EffectSound/Interaction/pick_generic.ogg", false, false);
		g_pSoundManager->AddSound("pick_key", "Sound/EffectSound/Interaction/pick_key.ogg", false, false);
		g_pSoundManager->AddSound("pick_knife", "Sound/EffectSound/Interaction/pick_knife.ogg", false, false);
		g_pSoundManager->AddSound("pick_paper", "Sound/EffectSound/Interaction/pick_paper.ogg", false, false);

		g_pSoundManager->AddSound("drop_key", "Sound/EffectSound/Interaction/25_drop_key.ogg", false, false);
		g_pSoundManager->AddSound("drop_generic", "Sound/EffectSound/Interaction/pickaxe_charge.ogg", false, false);

		g_pSoundManager->AddSound("door_prison", "Sound/EffectSound/Interaction/door_prison_open.ogg", false, false);
		g_pSoundManager->AddSound("door_1stRoom", "Sound/EffectSound/Interaction/door_mansion_close.ogg", false, false);
		g_pSoundManager->AddSound("door_2ndRoom1", "Sound/EffectSound/Interaction/01_door.ogg", false, false);
		g_pSoundManager->AddSound("door_2ndRoom2", "Sound/EffectSound/Interaction/move_gate.ogg", false, false);
		g_pSoundManager->AddSound("door_final", "Sound/EffectSound/Interaction/29_exit_door.ogg", false, false);

		g_pSoundManager->AddSound("base_box", "Sound/EffectSound/Interaction/door_level_wood_close.ogg", false, false);
		g_pSoundManager->AddSound("base_chest", "Sound/EffectSound/Interaction/gameplay_open_chest.ogg", false, false);
		g_pSoundManager->AddSound("1st_wood1", "Sound/EffectSound/Interaction/16_ladder_down.ogg", false, false);
		g_pSoundManager->AddSound("1st_wood2", "Sound/EffectSound/Interaction/04_place_wood.ogg", false, false);
		g_pSoundManager->AddSound("1st_woodblock", "Sound/EffectSound/Interaction/18_touch_bridge1.ogg", false, false);
		g_pSoundManager->AddSound("2nd_button", "Sound/EffectSound/Interaction/roll_rock.ogg", false, false);
		g_pSoundManager->AddSound("2nd_valve", "Sound/EffectSound/Interaction/13_attach_wheel.ogg", false, false);
		g_pSoundManager->AddSound("2nd_valvelock", "Sound/EffectSound/Interaction/12_valve_stuck.ogg", false, false);
		g_pSoundManager->AddSound("cancle", "Sound/EffectSound/Interaction/cancle.mp3", false, false);

	}
}