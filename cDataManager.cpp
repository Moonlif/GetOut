#include "stdafx.h"
#include "cDataManager.h"
#include "cMtlTex.h"

#include "cObjLoader.h"

cDataManager::cDataManager()
{
}


cDataManager::~cDataManager()
{
}

void cDataManager::Setup()
{
	//Using by Interaction 
	{
		cObjLoader loader;

		m_mapItemName[ITEM_KEY1] = "KEY1";
		m_mapItemSize[ITEM_KEY1] = 0.5f;
		m_mapItemMesh[ITEM_KEY1] = loader.LoadMesh(m_mapItemVecMtlTex[ITEM_KEY1], "interactObj", "box.obj");
	}
}

void cDataManager::Destroy()
{
	for each (auto it in m_mapItemMesh)
	{
		SAFE_RELEASE(it.second);
	}

	for each(auto it in m_mapItemVecMtlTex)
	{
		for (int i = 0; i < it.second.size(); i++)
		{
			SAFE_RELEASE(it.second[i]);
		}
	}
}

void cDataManager::Chat(string Text)
{
}

string cDataManager::GetText()
{
	if (m_listChat.empty())
		return NULL;

	string Text = m_listChat.front();
	m_listChat.pop_front();
	return Text;
}