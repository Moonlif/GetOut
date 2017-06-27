#pragma once
#include "stdafx.h"
#define g_pData cDataManager::GetInstance()


class cMtlTex;

class cDataManager
{
private:
	SINGLETONE(cDataManager);

	list<string> m_listChat_SEND;

	//���� - UI
	SYNTHESIZE(bool,		m_IsOnChat, IsOnChat)					//ä�ý� �Ұ�
	SYNTHESIZE(bool,		m_IsStartedGame, IsStartedGame)			//������ ���۵Ǿ��°�?
	SYNTHESIZE(bool,		m_IsInvenOpen, IsInvenOpen)				//�κ��丮 �Ұ�
	SYNTHESIZE(StuffCode,	m_UseItem, UseItem)						//���������� ���� � ���ΰ�?
	SYNTHESIZE(StuffCode,	m_PickUpItemCode, PickUpItemCode)		//������ ����� ����Ǵ� ����, NONE�� �ƴҽÿ��� �۵��ϰ� ����

	//���� - ������ ���� ����
	StuffCode				m_arrSaveInvenItem[TOTALINVENSIZE];		//�κ�ũ�⸸ŭ �������ڵ带 ������� �����Ѵ�.
	StuffCode				m_arrLoadInvenItem[TOTALINVENSIZE];		//����� ������ ������ �ڵ� ������ ������� �ε��Ѵ�.
	SYNTHESIZE(bool, m_IsLoadItem, IsLoadItem)						//�ε�� �Ұ�

	//���� - ����� ����
	SYNTHESIZE(bool, m_isWarning, isWarning)						//��� ��� �� �Ұ�
	SYNTHESIZE(string, m_strWarningWord, WarningWord)				//���

	//���� - �÷��̾� ���ϱ�
	SYNTHESIZE(int, m_nPlayer, PlayerNum)							//���� ��� �÷��̾��ΰ�

	//���� - ����
	SYNTHESIZE(bool,		m_IsEnding, IsEnding)					//���� �Ұ�

	//�տ�
	SYNTHESIZE(bool, m_IsCollisionWall, IsCollisionWall)
	D3DXVECTOR3 m_vPosition1P;
	float m_vRotation1P;
	animationState m_eAnimState1P;

	//���� - ��� ���� �� ���� ����
	bool m_bValve1;									//2�� Valve1�� Ŭ���ߴ���
	bool m_bValve2;									//2�� Valve2�� Ŭ���ߴ���
	int m_n2FValve1Count;							//2�� Valve1�� �����̼� �� (����: -4 ~ 4)
	int m_n2FValve2Count;							//2�� Valve2�� �����̼� �� (����: -4 ~ 4)
	int m_nBrickCount;								//1�� ���������⿡�� ������ � ����������

public:
	//���� - ������Ʈ��
	bool m_isHandOn;
	std::map<StuffCode, LPD3DXMESH> m_mapStuffMesh;
	std::map<StuffCode, std::vector<cMtlTex*>> m_mapStuffVecMtlTex;

	//���� - �� ����
	bool m_bStuffSwitch[SWITCH_LASTNUM];			//�������� ��� �ʿ� �ִ°� true
	D3DXVECTOR3 m_vStuffPosition[SWITCH_LASTNUM];
	D3DXVECTOR3 m_vStuffRotation[SWITCH_LASTNUM];

	//���� - ä��
	list<string> m_listChat_RECV;

	//�տ�
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

	//��� ���� ���� ���� �Լ�
	void TextOutWarningWord(string str);
	//�κ��丮 �����Լ�
	void SaveInvenInfo(int Index, StuffCode code) { m_arrSaveInvenItem[Index] = code; }
	//�κ��丮 �ε� �Լ�
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

