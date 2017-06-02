#pragma once
#include "cRectMake.h"

class cWall
{
private:
	//지하
	//위쪽 왼쪽 아래쪽 오른쪽 벽
	cRectMake* m_pB1Up;
	cRectMake* m_pB1Left;
	cRectMake* m_pB1Down;
	cRectMake* m_pB1Down2;
	cRectMake* m_pB1Right;
	
	//1층
	cRectMake* m_pFFUp;
	cRectMake* m_pFFLeft;
	cRectMake* m_pFFDown;
	cRectMake* m_pFFRight;

	//2층
	cRectMake* m_pSFUp;
	cRectMake* m_pSFLeft;
	cRectMake* m_pSFDown;
	cRectMake* m_pSFRight;
public:
	cWall();
	~cWall();
	void Setup();
	void Render();
};

