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
	SYNTHESIZE(bool,		m_IsOnChat, IsOnChat)					//채팅시 불값
	SYNTHESIZE(bool,		m_IsStartedGame, IsStartedGame)			//게임이 시작되었는가?
	SYNTHESIZE(bool,		m_IsInvenOpen, IsInvenOpen)				//인벤토리 불값
	SYNTHESIZE(StuffCode,	m_UseItem, UseItem)						//사용아이템이 현재 어떤 것인가?
	SYNTHESIZE(StuffCode,	m_PickUpItemCode, PickUpItemCode)		//아이템 습득시 변경되는 변수, NONE이 아닐시에만 작동하게 만듬

	//영현 - 아이템 정보 저장
	StuffCode				m_arrSaveInvenItem[TOTALINVENSIZE];		//인벤크기만큼 아이템코드를 순서대로 저장한다.
	StuffCode				m_arrLoadInvenItem[TOTALINVENSIZE];		//저장된 서버의 아이템 코드 순서를 순서대로 로드한다.
	SYNTHESIZE(bool, m_IsLoadItem, IsLoadItem)						//로드시 불값

	//영현 - 경고문구 띄우기
	SYNTHESIZE(bool, m_isWarning, isWarning)						//경고문 띄울 때 불값
	SYNTHESIZE(string, m_strWarningWord, WarningWord)				//경고문

	//영현 - 플레이어 정하기
	SYNTHESIZE(int, m_nPlayer, PlayerNum)							//내가 몇번 플레이어인가

	//영현 - 엔딩
	SYNTHESIZE(bool,		m_IsEnding, IsEnding)					//엔딩 불값

	//균영
	SYNTHESIZE(bool, m_IsCollisionWall, IsCollisionWall)
	D3DXVECTOR3 m_vPosition1P;
	float m_vRotation1P;
	animationState m_eAnimState1P;

	//정훈 - 밸브 상태 및 벽돌 개수
	bool m_bValve1;									//2층 Valve1을 클릭했는지
	bool m_bValve2;									//2층 Valve2을 클릭했는지
	int m_n2FValve1Count;							//2층 Valve1의 로테이션 값 (범위: -4 ~ 4)
	int m_n2FValve2Count;							//2층 Valve2의 로테이션 값 (범위: -4 ~ 4)
	int m_nBrickCount;								//1층 벽돌무더기에서 벽돌을 몇개 가져갔는지

public:
	//정훈 - 오브젝트용
	bool m_isHandOn;
	std::map<StuffCode, LPD3DXMESH> m_mapStuffMesh;
	std::map<StuffCode, std::vector<cMtlTex*>> m_mapStuffVecMtlTex;

	//정훈 - 맵 정보
	bool m_bStuffSwitch[SWITCH_LASTNUM];			//아이템일 경우 맵에 있는게 true
	D3DXVECTOR3 m_vStuffPosition[SWITCH_LASTNUM];
	D3DXVECTOR3 m_vStuffRotation[SWITCH_LASTNUM];

	//지상 - 채팅
	list<string> m_listChat_RECV;

	//균영
	int m_nPlayerNum1P;
	int m_nPlayerNum2P;
	D3DXVECTOR3 m_vPosition2P;
	float m_vRotation2P;
	animationState m_eAnimState2P;

public:
	void Setup();
	void Destroy();
	
	void Chat(string Text);
	string GetText();

	void DropItem(StuffCode itemCode);
	void GetItem(StuffCode itemCode);

	//경고 문구 띄우기 위한 함수
	void TextOutWarningWord(string str);
	//인벤토리 저장함수
	void SaveInvenInfo(int Index, StuffCode code) { m_arrSaveInvenItem[Index] = code; }
	//인벤토리 로드 함수
	StuffCode LoadInvenInfo(int Index) { return m_arrLoadInvenItem[Index]; }

	D3DXVECTOR3 Get1PPosition();
	void Set1PPosition(D3DXVECTOR3 stValue);
	float Get1PRotation();
	void Set1PRotation(float fValue);
	animationState Get1PAnimation();
	void Set1PAnimation(animationState stValue);

	void AddSound();

	bool GetValve1();
	bool GetValve2();
	int GetValve1Count();
	int GetValve2Count();
	int GetBrickCount();

	void SetValve1(bool bValue);
	void SetValve2(bool bValue);
	void SetValve1Count(int nValue);
	void SetValve2Count(int nValue);
	void SetBrickCount(int nValue);
};

