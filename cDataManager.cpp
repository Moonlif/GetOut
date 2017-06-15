#include "stdafx.h"
#include "cDataManager.h"
#include "cMtlTex.h"

#include "cObjLoader.h"

cDataManager::cDataManager()
	:m_IsInvenOpen(false)
	, m_IsStartedGame(false)
	, m_IsOnChat(false)
	, m_IsMiniGamePrisonBreak(false)
	, m_IsPossibleMove(false)
	, m_PickUpItemCode(StuffCode::STUFF_NONE)
{
}


cDataManager::~cDataManager()
{
}

void cDataManager::Setup()
{
	//¡§»∆ - √Êµπ ø¿∫Í¡ß∆Æ ¡§∫∏
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
	}

	//¡§»∆ - ∏  ¡§∫∏
	{
		for (int i = 0; i < SWITCH_LASTNUM; ++i)
		{
			m_bStuffSwitch[i] = false;
		}

		m_bStuffSwitch[SWITCH_ONMAP_CROWBAR] = true;
		m_vStuffPosition[SWITCH_ONMAP_CROWBAR] = D3DXVECTOR3(-40, 12, 12);
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
	}
}

void cDataManager::Destroy()
{
	//¡§»∆
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

//æ∆¿Ã≈€ »πµÊ π◊ µÂ∂¯
void cDataManager::DropItem(StuffCode itemCode)
{
	if (itemCode < STUFF_CROWBAR || itemCode > STUFF_BRICK5) return;

	m_bStuffSwitch[itemCode] = true;
	m_vStuffPosition[itemCode] = m_vPosition1P;
	m_vStuffRotation[itemCode] = D3DXVECTOR3(0, m_vRotation1P, 0);
	cout << "πˆ∏±∂ß : " << itemCode << endl;
}

void cDataManager::GetItem(StuffCode itemCode)
{
	if (itemCode < STUFF_CROWBAR || itemCode > STUFF_BRICK5) return;

	m_bStuffSwitch[itemCode] = false;
	m_PickUpItemCode = itemCode;
	cout << "¡ﬁ¿ª∂ß : " << itemCode << endl;
}


void cDataManager::TextOutWarningWord(string str)
{
	m_isWarning = true;
	m_strWarningWord = str;
}
