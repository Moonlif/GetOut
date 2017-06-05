#pragma once
#include "cRectMake.h"

class cFloor
{
private:
	/**********************
	ÁöÇÏ
	**********************/
	cRectMake* m_pB1FStartRoom;
	cRectMake* m_pB1FRoom;
	cRectMake* m_pB1Stair[10];
	cRectMake* m_pB1Water;
	cRectMake* m_pB1FBlood;
	/***********************
	1Ãþ
	************************/
	cRectMake* m_pFFRoom;
	cRectMake* m_pFFBathRoom;
	cRectMake* m_pFFLivingRoom;
	cRectMake* m_pFFLivingRoom2;
	cRectMake* m_pFFPassage;
	cRectMake* m_pFFPassage2;
	cRectMake* m_pB1Stair2[10];
	/***********************
	2Ãþ
	************************/
	cRectMake* m_pSFLeftRoom;
	cRectMake* m_pSFRightRoom;
	cRectMake* m_pSFPassage;
public:
	cFloor();
	~cFloor();
	void Setup();
	void Render();
};

