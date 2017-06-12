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
	bool m_bStuffSwitch[SWITCH_LASTNUM];
	D3DXVECTOR3 m_vStuffPosition[SWITCH_LASTNUM];
	D3DXVECTOR3 m_vStuffRotation[SWITCH_LASTNUM];

	//Áö»ó - Ã¤ÆÃ
	list<string> m_listChat_RECV;
	SYNTHESIZE(DWORD, m_dwUpdateTick, UpdateTick);

	//±Õ¿µ
	int m_nPlayerNum;
	D3DXVECTOR3 m_vPosition1P;
	D3DXVECTOR3 m_vPosition2P;
	float m_vRotation1P;
	float m_vRotation2P;
	animationState m_eAnimState1P;
	animationState m_eAnimState2P;

public:
	void Setup();
	void Destroy();
	
	void Chat(string Text);
	string GetText();

	void DropItem(StuffCode itemCode, D3DXVECTOR3 position, D3DXVECTOR3 rotation = D3DXVECTOR3(0, 0, 0));
	void GetItem(StuffCode itemCode);
};

