#pragma once
#include "cRectMake.h"
class cCeiling
{
private:
	std::vector<cRectMake*> m_vecRect;

	/**********************
		����
	**********************/
	cRectMake* m_pB1FStartRoom;
	//������ õ�� ����
	cRectMake* m_pB1FCollision;
	cRectMake* m_pB1FCollision2;
	cRectMake* m_pB1FCollision3;
	cRectMake* m_pB1FCollision4;

	cRectMake* m_pB1FRoom;
	/***********************
		1��
	************************/
	cRectMake* m_pFFRoom;
	cRectMake* m_pFFBathRoom;
	cRectMake* m_pFFBathRoomPrint;
	cRectMake* m_pFFLivingRoom;
	cRectMake* m_pFFLivingRoom2;
	cRectMake* m_pFFPassage;
	cRectMake* m_pFFPassage2;

	/***********************
		2��
	************************/
	cRectMake* m_pSFLeftRoom;
	cRectMake* m_pSFRightRoom;
	cRectMake* m_pSFPassage;
public:
	cCeiling();
	~cCeiling();
	void Setup();
	void Render();
};

