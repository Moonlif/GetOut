#pragma once
#include "stdafx.h"
#define g_pData cDataManager::GetInstance()

class cMtlTex;

class cDataManager
{
private:
	SINGLETONE(cDataManager);

	// >> : À¯Áö»ó
	list<string> m_listChat;
	// << :
public:
	std::map<ItemCode, string> m_mapItemName;
	std::map<ItemCode, float> m_mapItemSize;
	std::map<ItemCode, LPD3DXMESH> m_mapItemMesh;
	std::map<ItemCode, std::vector<cMtlTex*>> m_mapItemVecMtlTex;

	LPD3DXMESH mesh;

public:
	void Setup();
	void Destroy();
	
	void Chat(string Text);
	string GetText();
};

