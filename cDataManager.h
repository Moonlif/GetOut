#pragma once
#include "stdafx.h"
#define g_pData cDataManager::GetInstance()

class cMtlTex;

class cDataManager
{
private:
	SINGLETONE(cDataManager);

	list<string> m_listChat_SEND;

public:
	std::map<ItemCode, string> m_mapItemName;
	std::map<ItemCode, float> m_mapItemRadius;
	std::map<ItemCode, float> m_mapItemScaling;
	std::map<ItemCode, LPD3DXMESH> m_mapItemMesh;
	std::map<ItemCode, std::vector<cMtlTex*>> m_mapItemVecMtlTex;

	list<string> m_listChat_RECV;

public:
	void Setup();
	void Destroy();
	
	void Chat(string Text);
	string GetText();
};

