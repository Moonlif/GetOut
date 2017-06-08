#pragma once
#include "stdafx.h"
#define g_pData cDataManager::GetInstance()

class cMtlTex;

class cDataManager
{
private:
	SINGLETONE(cDataManager);

	list<string> m_listChat_SEND;

	//����
	SYNTHESIZE(bool, m_IsStartedGame, IsStartedGame)
	SYNTHESIZE(bool, m_IsInvenOpen, IsInvenOpen)

public:
	//���� - ������Ʈ��
	std::map<StuffCode, LPD3DXMESH> m_mapStuffMesh;
	std::map<StuffCode, std::vector<cMtlTex*>> m_mapStuffVecMtlTex;

	//���� - �� ����
	bool m_bStuffSwitch[10];
	D3DXVECTOR3 m_vStuffPosition[SWITCH_LASTNUM];
	D3DXVECTOR3 m_vStuffRotation[SWITCH_LASTNUM];

	//���� - ä��
	list<string> m_listChat_RECV;
	SYNTHESIZE(DWORD, m_dwUpdateTick, UpdateTick);

	//�տ�
	int m_nPlayerNum;
	D3DXVECTOR3 m_vPosition1P;
	D3DXVECTOR3 m_vPosition2P;
	D3DXVECTOR3 m_vRotation1P;
	D3DXVECTOR3 m_vRotation2P;
	animationState m_eOtherPlayerAnimState;

public:
	void Setup();
	void Destroy();
	
	void Chat(string Text);
	string GetText();
};

