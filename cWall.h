#pragma once
#include "cRectMake.h"

class cWall
{
private:
	//����
	//���� ���� �Ʒ��� ������ ��
	cRectMake* m_pB1Up;
	cRectMake* m_pB1Left;
	cRectMake* m_pB1Down;
	cRectMake* m_pB1Down2;
	cRectMake* m_pB1Right;
	
	//1��
	cRectMake* m_pFFUp;
	cRectMake* m_pFFLeft;
	cRectMake* m_pFFDown;
	cRectMake* m_pFFRight;

	//2��
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

