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
	//Using by Interaction - Á¤ÈÆ
	{
		cObjLoader loader; 

		m_mapItemName[ITEM_BASEMENT_JAILKEY] = "KEY1";
		m_mapItemRadius[ITEM_BASEMENT_JAILKEY] = 0.5f;
		m_mapItemScaling[ITEM_BASEMENT_JAILKEY] = 0.5f;
		m_mapItemMesh[ITEM_BASEMENT_JAILKEY] = loader.LoadMesh(m_mapItemVecMtlTex[ITEM_BASEMENT_JAILKEY], "interactObj", "box.obj");

	}
}

void cDataManager::Destroy()
{
	//Using by Interaction - Á¤ÈÆ
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