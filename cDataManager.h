#pragma once
#include "stdafx.h"
#define g_pData cDataManager::GetInstance()


class cMtlTex;

class cDataManager
{
private:
	SINGLETONE(cDataManager);

	list<string> m_listChat_SEND;

	//영현 - UI
	SYNTHESIZE(bool,		m_IsOnChat, IsOnChat)
	SYNTHESIZE(bool,		m_IsStartedGame, IsStartedGame)
	SYNTHESIZE(bool,		m_IsInvenOpen, IsInvenOpen)
	SYNTHESIZE(StuffCode,	m_UseItem, UseItem)
	SYNTHESIZE(StuffCode,	m_PickUpItemCode, PickUpItemCode)

	//영현 - 아이템 정보 저장
	StuffCode				m_arrSaveInvenItem[TOTALINVENSIZE];
	StuffCode				m_arrLoadInvenItem[TOTALINVENSIZE];
	SYNTHESIZE(bool,		m_IsLoadItem, IsLoadItem)

	//영현 - 경고문구 띄우기
	SYNTHESIZE(bool,		m_isWarning, isWarning)
	SYNTHESIZE(string,		m_strWarningWord, WarningWord)
	
public:
	//정훈 - 오브젝트용
	bool m_isHandOn;
	std::map<StuffCode, LPD3DXMESH> m_mapStuffMesh;
	std::map<StuffCode, std::vector<cMtlTex*>> m_mapStuffVecMtlTex;

	//정훈 - 맵 정보
	bool m_bStuffSwitch[SWITCH_LASTNUM];			//아이템일 경우 맵에 있는게 true
	D3DXVECTOR3 m_vStuffPosition[SWITCH_LASTNUM];
	D3DXVECTOR3 m_vStuffRotation[SWITCH_LASTNUM];
	bool m_bValve1;									//2층 Valve1을 클릭했는지
	bool m_bValve2;									//2층 Valve2을 클릭했는지
	int m_n2FValve1Count;							//2층 Valve1의 로테이션 값 (범위: -4 ~ 4)
	int m_n2FValve2Count;							//2층 Valve2의 로테이션 값 (범위: -4 ~ 4)
	int m_nBrickCount;								//1층 벽돌무더기에서 벽돌을 몇개 가져갔는지

	//지상 - 채팅
	list<string> m_listChat_RECV;

	//균영
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
	void SaveInvenInfo(int Index, StuffCode code) { m_arrSaveInvenItem[Index] = code; }
	StuffCode LoadInvenInfo(int Index) { return m_arrLoadInvenItem[Index]; }


	void AddSound();
};

