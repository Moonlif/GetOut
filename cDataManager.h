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
	//정훈 - 오브젝트용
	std::map<StuffCode, string> m_mapStuffName;
	std::map<StuffCode, float> m_mapStuffRadius;
	std::map<StuffCode, float> m_mapStuffScaling;
	std::map<StuffCode, LPD3DXMESH> m_mapStuffMesh;
	std::map<StuffCode, std::vector<cMtlTex*>> m_mapStuffVecMtlTex;

	list<string> m_listChat_RECV;

public:
	void Setup();
	void Destroy();
	
	void Chat(string Text);
	string GetText();
};

