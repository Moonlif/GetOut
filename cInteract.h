#pragma once

#include "cStuff.h"
#include "cParticleSystem.h"

class cInteract
{
public:
	cInteract();
	~cInteract();

private:
	std::vector<cStuff*> m_vecStuff;		//��� ��ü���� �����ϴ� ����

	int m_n1FBlockCount;					//1�� BoardBlock�� ��� Ŭ���ߴ��� ��Ÿ���� ��
	bool m_bValve1;							//2�� Valve1�� Ŭ���ߴ���
	bool m_bValve2;							//2�� Valve2�� Ŭ���ߴ���
	int m_n2FValve1Count;					//2�� Valve1�� �����̼� �� (����: -4 ~ 4)
	int m_n2FValve2Count;					//2�� Valve2�� �����̼� �� (����: -4 ~ 4)
	int m_n2FButton1Count;					//2�� Button1�� �����ִ���
	int m_n2FButton2Count;					//2�� Button2�� �����ִ���
	int m_nBrickCount;						//1�� ���������⿡�� ������ � ����������

	cParticleSystem* m_pParticleFog;
	D3DXVECTOR3 m_vPositionFog;

public:
	void Setup();
	void Update();
	void Render();
	void CheckStuff(D3DXVECTOR3 playerPos);
	bool PickStuff(StuffCode stuffCode, bool lButton);
};