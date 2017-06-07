#pragma once
#include "stdafx.h"
#define g_pData cDataManager::GetInstance()

class cMtlTex;

class cDataManager
{
private:
	SINGLETONE(cDataManager);

	list<string> m_listChat_SEND;

	//¿µÇö
	SYNTHESIZE(bool, m_IsStartedGame, IsStartedGame)
	SYNTHESIZE(bool, m_IsInvenOpen, IsInvenOpen)

public:
	//Á¤ÈÆ - ¿ÀºêÁ§Æ®¿ë
	std::map<StuffCode, LPD3DXMESH> m_mapStuffMesh;
	std::map<StuffCode, std::vector<cMtlTex*>> m_mapStuffVecMtlTex;

	//Á¤ÈÆ - ¸Ê Á¤º¸
	bool m_BasementSwitch1;

	//Áö»ó - Ã¤ÆÃ
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

