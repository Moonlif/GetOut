#include "stdafx.h"
#include "cDataManager.h"
#include "cMtlTex.h"

#include "cObjLoader.h"

cDataManager::cDataManager()
	:m_IsInvenOpen(false)
	, m_IsStartedGame(false)
{
}


cDataManager::~cDataManager()
{
}

void cDataManager::Setup()
{
	//Using by Interaction - Á¤ÈÆ
	{
		cObjLoader loader; 

		m_mapStuffName[STUFF_BOARDBLOCK] = "boardblock";
		m_mapStuffRadius[STUFF_BOARDBLOCK] = 0.5f;
		m_mapStuffScaling[STUFF_BOARDBLOCK] = 0.5f;
		m_mapStuffMesh[STUFF_BOARDBLOCK] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_BOARDBLOCK], "Objects/clickable", "boardblock.obj", 1);

		m_mapStuffName[STUFF_BOX1] = "box1";
		m_mapStuffRadius[STUFF_BOX1] = 0.5f;
		m_mapStuffScaling[STUFF_BOX1] = 0.5f;
		m_mapStuffMesh[STUFF_BOX1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_BOX1], "Objects/clickable", "box1.obj", 1);

		m_mapStuffName[STUFF_BOX2] = "box2";
		m_mapStuffRadius[STUFF_BOX2] = 0.5f;
		m_mapStuffScaling[STUFF_BOX2] = 0.5f;
		m_mapStuffMesh[STUFF_BOX2] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_BOX2], "Objects/clickable", "box2.obj", 1);

		m_mapStuffName[STUFF_BOX3] = "box3";
		m_mapStuffRadius[STUFF_BOX3] = 0.5f;
		m_mapStuffScaling[STUFF_BOX3] = 0.5f;
		m_mapStuffMesh[STUFF_BOX3] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_BOX3], "Objects/clickable", "box3.obj", 1);

		m_mapStuffName[STUFF_BRICK] = "brick";
		m_mapStuffRadius[STUFF_BRICK] = 0.5f;
		m_mapStuffScaling[STUFF_BRICK] = 0.5f;
		m_mapStuffMesh[STUFF_BRICK] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_BRICK], "Objects/clickable", "brick.obj", 1);

		m_mapStuffName[STUFF_BRICKPILE] = "brickpile";
		m_mapStuffRadius[STUFF_BRICKPILE] = 0.5f;
		m_mapStuffScaling[STUFF_BRICKPILE] = 0.5f;
		m_mapStuffMesh[STUFF_BRICKPILE] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_BRICKPILE], "Objects/clickable", "brickpile.obj", 1);

		m_mapStuffName[STUFF_CHEST2] = "chest2";
		m_mapStuffRadius[STUFF_CHEST2] = 0.5f;
		m_mapStuffScaling[STUFF_CHEST2] = 0.5f;
		m_mapStuffMesh[STUFF_CHEST2] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_CHEST2], "Objects/clickable", "chest2.obj", 1);

		m_mapStuffName[STUFF_CHEST3] = "chest3";
		m_mapStuffRadius[STUFF_CHEST3] = 0.5f;
		m_mapStuffScaling[STUFF_CHEST3] = 0.5f;
		m_mapStuffMesh[STUFF_CHEST3] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_CHEST3], "Objects/clickable", "chest3.obj", 1);

		m_mapStuffName[STUFF_CROWBAR] = "crowbar";
		m_mapStuffRadius[STUFF_CROWBAR] = 0.5f;
		m_mapStuffScaling[STUFF_CROWBAR] = 0.5f;
		m_mapStuffMesh[STUFF_CROWBAR] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_CROWBAR], "Objects/clickable", "crowbar.obj", 1);

		m_mapStuffName[STUFF_DOOR1] = "door1";
		m_mapStuffRadius[STUFF_DOOR1] = 0.5f;
		m_mapStuffScaling[STUFF_DOOR1] = 0.5f;
		m_mapStuffMesh[STUFF_DOOR1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_DOOR1], "Objects/clickable", "door1.obj", 1);

		m_mapStuffName[STUFF_EMPTYBOX] = "emptybox";
		m_mapStuffRadius[STUFF_EMPTYBOX] = 0.5f;
		m_mapStuffScaling[STUFF_EMPTYBOX] = 0.5f;
		m_mapStuffMesh[STUFF_EMPTYBOX] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_EMPTYBOX], "Objects/clickable", "emptybox.obj", 1);

		m_mapStuffName[STUFF_KEY1] = "key1";
		m_mapStuffRadius[STUFF_KEY1] = 0.5f;
		m_mapStuffScaling[STUFF_KEY1] = 0.5f;
		m_mapStuffMesh[STUFF_KEY1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_KEY1], "Objects/clickable", "key1.obj", 1);

		m_mapStuffName[STUFF_KEY2] = "key2";
		m_mapStuffRadius[STUFF_KEY2] = 0.5f;
		m_mapStuffScaling[STUFF_KEY2] = 0.5f;
		m_mapStuffMesh[STUFF_KEY2] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_KEY2], "Objects/clickable", "key2.obj", 1);

		m_mapStuffName[STUFF_KEY3] = "key3";
		m_mapStuffRadius[STUFF_KEY3] = 0.5f;
		m_mapStuffScaling[STUFF_KEY3] = 0.5f;
		m_mapStuffMesh[STUFF_KEY3] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_KEY3], "Objects/clickable", "key3.obj", 1);

		m_mapStuffName[STUFF_KEY4] = "key4";
		m_mapStuffRadius[STUFF_KEY4] = 0.5f;
		m_mapStuffScaling[STUFF_KEY4] = 0.5f;
		m_mapStuffMesh[STUFF_KEY4] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_KEY4], "Objects/clickable", "key4.obj", 1);

		m_mapStuffName[STUFF_KEY5] = "key5";
		m_mapStuffRadius[STUFF_KEY5] = 0.5f;
		m_mapStuffScaling[STUFF_KEY5] = 0.5f;
		m_mapStuffMesh[STUFF_KEY5] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_KEY5], "Objects/clickable", "key5.obj", 1);

		m_mapStuffName[STUFF_NOTE4] = "note4";
		m_mapStuffRadius[STUFF_NOTE4] = 0.5f;
		m_mapStuffScaling[STUFF_NOTE4] = 0.5f;
		m_mapStuffMesh[STUFF_NOTE4] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_NOTE4], "Objects/clickable", "note4.obj", 1);

		m_mapStuffName[STUFF_PAPER1] = "paper1";
		m_mapStuffRadius[STUFF_PAPER1] = 0.5f;
		m_mapStuffScaling[STUFF_PAPER1] = 0.5f;
		m_mapStuffMesh[STUFF_PAPER1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_PAPER1], "Objects/clickable", "paper1.obj", 1);

		m_mapStuffName[STUFF_PAPER2] = "paper2";
		m_mapStuffRadius[STUFF_PAPER2] = 0.5f;
		m_mapStuffScaling[STUFF_PAPER2] = 0.5f;
		m_mapStuffMesh[STUFF_PAPER2] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_PAPER2], "Objects/clickable", "paper2.obj", 1);

		m_mapStuffName[STUFF_PAPER3] = "paper3";
		m_mapStuffRadius[STUFF_PAPER3] = 0.5f;
		m_mapStuffScaling[STUFF_PAPER3] = 0.5f;
		m_mapStuffMesh[STUFF_PAPER3] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_PAPER3], "Objects/clickable", "paper2.obj", 1);

		m_mapStuffName[STUFF_POSTER1] = "poster1";
		m_mapStuffRadius[STUFF_POSTER1] = 0.5f;
		m_mapStuffScaling[STUFF_POSTER1] = 0.5f;
		m_mapStuffMesh[STUFF_POSTER1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_POSTER1], "Objects/clickable", "poster1.obj", 1);

		m_mapStuffName[STUFF_POSTER2] = "poster2";
		m_mapStuffRadius[STUFF_POSTER2] = 0.5f;
		m_mapStuffScaling[STUFF_POSTER2] = 0.5f;
		m_mapStuffMesh[STUFF_POSTER2] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_POSTER2], "Objects/clickable", "poster2.obj", 1);

		m_mapStuffName[STUFF_POSTER3] = "poster3";
		m_mapStuffRadius[STUFF_POSTER3] = 0.5f;
		m_mapStuffScaling[STUFF_POSTER3] = 0.5f;
		m_mapStuffMesh[STUFF_POSTER3] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_POSTER3], "Objects/clickable", "poster3.obj", 1);

		m_mapStuffName[STUFF_POSTER4] = "poster4";
		m_mapStuffRadius[STUFF_POSTER4] = 0.5f;
		m_mapStuffScaling[STUFF_POSTER4] = 0.5f;
		m_mapStuffMesh[STUFF_POSTER4] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_POSTER4], "Objects/clickable", "poster4.obj", 1);

		m_mapStuffName[STUFF_ROCK1] = "rock1";
		m_mapStuffRadius[STUFF_ROCK1] = 0.5f;
		m_mapStuffScaling[STUFF_ROCK1] = 0.5f;
		m_mapStuffMesh[STUFF_ROCK1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_ROCK1], "Objects/clickable", "rock1.obj", 1);

		m_mapStuffName[STUFF_ROCK2] = "rock2";
		m_mapStuffRadius[STUFF_ROCK2] = 0.5f;
		m_mapStuffScaling[STUFF_ROCK2] = 0.5f;
		m_mapStuffMesh[STUFF_ROCK2] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_ROCK2], "Objects/clickable", "rock2.obj", 1);

		m_mapStuffName[STUFF_VALVE1] = "valve1";
		m_mapStuffRadius[STUFF_VALVE1] = 0.5f;
		m_mapStuffScaling[STUFF_VALVE1] = 0.5f;
		m_mapStuffMesh[STUFF_VALVE1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_VALVE1], "Objects/clickable", "valve1.obj", 1);

		m_mapStuffName[STUFF_WOOD1] = "wood1";
		m_mapStuffRadius[STUFF_WOOD1] = 0.5f;
		m_mapStuffScaling[STUFF_WOOD1] = 0.5f;
		m_mapStuffMesh[STUFF_WOOD1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_WOOD1], "Objects/clickable", "wood1.obj", 1);

		m_mapStuffName[STUFF_WOOD2] = "wood2";
		m_mapStuffRadius[STUFF_WOOD2] = 0.5f;
		m_mapStuffScaling[STUFF_WOOD2] = 0.5f;
		m_mapStuffMesh[STUFF_WOOD2] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_WOOD2], "Objects/clickable", "wood2.obj", 1);

		m_mapStuffName[STUFF_WOOD3] = "wood3";
		m_mapStuffRadius[STUFF_WOOD3] = 0.5f;
		m_mapStuffScaling[STUFF_WOOD3] = 0.5f;
		m_mapStuffMesh[STUFF_WOOD3] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_WOOD3], "Objects/clickable", "wood3.obj", 1);

		m_mapStuffName[STUFF_WOODBOARD1] = "woodboard1";
		m_mapStuffRadius[STUFF_WOODBOARD1] = 0.5f;
		m_mapStuffScaling[STUFF_WOODBOARD1] = 0.5f;
		m_mapStuffMesh[STUFF_WOODBOARD1] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_WOODBOARD1], "Objects/clickable", "woodboard1.obj", 1);

		m_mapStuffName[STUFF_WOODBOARD2] = "woodboard2";
		m_mapStuffRadius[STUFF_WOODBOARD2] = 0.5f;
		m_mapStuffScaling[STUFF_WOODBOARD2] = 0.5f;
		m_mapStuffMesh[STUFF_WOODBOARD2] = loader.LoadMesh(m_mapStuffVecMtlTex[STUFF_WOODBOARD2], "Objects/clickable", "woodboard2.obj", 1);
	}
}

void cDataManager::Destroy()
{
	//Using by Interaction - Á¤ÈÆ
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