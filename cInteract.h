#pragma once

#include "cStuff.h"

class cInteract
{
public:
	cInteract();
	~cInteract();

private:
	std::vector<cStuff*> m_vecStuff;		//모든 물체들을 저장하는 벡터

	int m_n1FBlockCount;					//1층 BoardBlock을 몇번 클릭했는지 나타내는 값
	bool m_bValve1;							//2층 Valve1을 클릭했는지
	bool m_bValve2;							//2층 Valve2을 클릭했는지
	int m_n2FValve1Count;					//2층 Valve1의 로테이션 값 (범위: -4 ~ 4)
	int m_n2FValve2Count;					//2층 Valve2의 로테이션 값 (범위: -4 ~ 4)
	int m_n2FButton1Count;					//2층 Button1이 눌려있는지
	int m_n2FButton2Count;					//2층 Button2이 눌려있는지

public:
	void Setup();
	void Update();
	void Render();
	void PickStuff(int keyState, D3DXVECTOR3 playerPos);
};

