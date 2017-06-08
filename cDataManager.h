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
	bool m_BasementSwitch1;

	//���� - ä��
	list<string> m_listChat_RECV;

	//�տ�
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
};

