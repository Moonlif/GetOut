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
	SYNTHESIZE(bool, m_IsOnChat, IsOnChat)
	SYNTHESIZE(bool, m_IsStartedGame, IsStartedGame)
	SYNTHESIZE(bool, m_IsInvenOpen, IsInvenOpen)
	SYNTHESIZE(StuffCode, m_UseItem, UseItem)
	SYNTHESIZE(bool, m_IsMiniGamePrisonBreak, IsMiniGamePrisonBreak)

	SYNTHESIZE(bool, m_IsPossibleMove, IsPossibleMove)
	SYNTHESIZE(StuffCode, m_SetItem, SetItem)

	//����� ����
	SYNTHESIZE(bool,					m_isWarning, isWarning);
	SYNTHESIZE(string,					m_strWarningWord, WarningWord);
	
public:
	//���� - ������Ʈ��
	std::map<StuffCode, LPD3DXMESH> m_mapStuffMesh;
	std::map<StuffCode, std::vector<cMtlTex*>> m_mapStuffVecMtlTex;

	//���� - �� ����
	bool m_bStuffSwitch[SWITCH_LASTNUM];
	D3DXVECTOR3 m_vStuffPosition[SWITCH_LASTNUM];
	D3DXVECTOR3 m_vStuffRotation[SWITCH_LASTNUM];

	//���� - ä��
	list<string> m_listChat_RECV;

	//�տ�
	int m_nPlayerNum1P;
	int m_nPlayerNum2P;
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

	void DropItem(StuffCode itemCode);
	void GetItem(StuffCode itemCode);

	void TextOutWarningWord(string str);
};

