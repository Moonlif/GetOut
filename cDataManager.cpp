#include "stdafx.h"
#include "cDataManager.h"
#include "cMtlTex.h"

#include "cObjLoader.h"

cDataManager::cDataManager()
	:m_IsInvenOpen(false)
	, m_IsStartedGame(false)
	, m_IsOnChat(false)
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
		m_mapStuffMesh[STUFF_BOARDBLOCK] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_BOARDBLOCK], "Objects/clickable", "boardblock.obj", 1);
		m_mapStuffMesh[STUFF_BOX1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_BOX1], "Objects/clickable", "box1.obj", 1);
		m_mapStuffMesh[STUFF_BRICK] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_BRICK], "Objects/clickable", "brick.obj", 1);
		m_mapStuffMesh[STUFF_BRICKPILE] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_BRICKPILE], "Objects/clickable", "brickpile.obj", 1);
		m_mapStuffMesh[STUFF_CHEST2] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_CHEST2], "Objects/clickable", "chest2.obj", 1);
		m_mapStuffMesh[STUFF_CHEST3] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_CHEST3], "Objects/clickable", "chest3.obj", 1);
		m_mapStuffMesh[STUFF_CROWBAR] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_CROWBAR], "Objects/clickable", "crowbar.obj", 1);

		//m_mapStuffMesh[STUFF_DOOR1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_DOOR1], "Objects/clickable", "door1.obj", 1);
		m_mapStuffMesh[STUFF_EMPTYBOX] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_EMPTYBOX], "Objects/clickable", "emptybox.obj", 1);
		//m_mapStuffMesh[STUFF_KEY1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_KEY1], "Objects/clickable", "key1.obj", 1);
		//m_mapStuffMesh[STUFF_KEY2] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_KEY2], "Objects/clickable", "key2.obj", 1);
		//m_mapStuffMesh[STUFF_KEY3] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_KEY3], "Objects/clickable", "key3.obj", 1);
		//m_mapStuffMesh[STUFF_KEY4] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_KEY4], "Objects/clickable", "key4.obj", 1);
		//m_mapStuffMesh[STUFF_KEY5] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_KEY5], "Objects/clickable", "key5.obj", 1);
		//m_mapStuffMesh[STUFF_PAPER1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_PAPER1], "Objects/clickable", "paper1.obj", 1);
		//m_mapStuffMesh[STUFF_PAPER2] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_PAPER2], "Objects/clickable", "paper2.obj", 1);
		//m_mapStuffMesh[STUFF_PAPER3] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_PAPER3], "Objects/clickable", "paper2.obj", 1);
		//m_mapStuffMesh[STUFF_POSTER1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_POSTER1], "Objects/clickable", "poster1.obj", 1);
		//m_mapStuffMesh[STUFF_POSTER2] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_POSTER2], "Objects/clickable", "poster2.obj", 1);
		//m_mapStuffMesh[STUFF_POSTER3] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_POSTER3], "Objects/clickable", "poster3.obj", 1);
		//m_mapStuffMesh[STUFF_POSTER4] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_POSTER4], "Objects/clickable", "poster4.obj", 1);
		m_mapStuffMesh[STUFF_TRAP] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_TRAP], "Objects/clickable", "trap.obj", 0);
		m_mapStuffMesh[STUFF_VALVE1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_VALVE1], "Objects/clickable", "valve1.obj", 1);
		m_mapStuffMesh[STUFF_VALVE2] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_VALVE2], "Objects/clickable", "valve1.obj", 1);
		m_mapStuffMesh[STUFF_WOOD1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_WOOD1], "Objects/clickable", "wood1.obj", 1);
		m_mapStuffMesh[STUFF_WOOD2] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_WOOD2], "Objects/clickable", "wood2.obj", 1);
		m_mapStuffMesh[STUFF_WOOD3] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_WOOD3], "Objects/clickable", "wood3.obj", 1);
		m_mapStuffMesh[STUFF_WOODBOARD1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_WOODBOARD1], "Objects/clickable", "woodboard1.obj", 1);
		m_mapStuffMesh[STUFF_WOODBOARD2] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_WOODBOARD2], "Objects/clickable", "woodboard2.obj", 1);
	}

	//¡§»∆ - ∏  ¡§∫∏
	{
		for (int i = 0; i < SWITCH_LASTNUM; ++i)
		{
			m_bStuffSwitch[i] = false;
		}
	}
	m_vStuffPosition[SWITCH_FIRSTFLOOR_WOODBOARD1] = D3DXVECTOR3(-7, 12, 19.5f);
	//m_vStuffRotation[SWITCH_FIRSTFLOOR_WOODBOARD1] = D3DXVECTOR3(0, D3DX_PI / 2.0f, 0);
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