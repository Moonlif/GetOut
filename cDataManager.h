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
	//Á¤ÈÆ - ¿ÀºêÁ§Æ®¿ë
	std::map<StuffCode, string> m_mapStuffName;
	std::map<StuffCode, float> m_mapStuffRadius;
	std::map<StuffCode, float> m_mapStuffScaling;
	std::map<StuffCode, LPD3DXMESH> m_mapStuffMesh;
	std::map<StuffCode, std::vector<cMtlTex*>> m_mapStuffVecMtlTex;

	list<string> m_listChat_RECV;

	//±Õ¿µ
	int m_nPlayerNum;
	D3DXVECTOR3 m_vPosition1P;
	D3DXVECTOR3 m_vPosition2P;
	float m_vRotation1P;
	float m_vRotation2P;
	animationState m_eOtherPlayerAnimState;



public:
	void Setup();
	void Destroy();
	
	void Chat(string Text);
	string GetText();
};

