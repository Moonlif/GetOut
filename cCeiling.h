#pragma once
#include "cRectMake.h"
class cCeiling
{
private:
	/**********************
		ÁöÇÏ
	**********************/
	cRectMake* m_pB1FStartRoom;
	cRectMake* m_pB1FRoom;
	/***********************
		1Ãþ
	************************/
	cRectMake* m_pFFRoom;
	cRectMake* m_pFFBathRoom;
	cRectMake* m_pFFLivingRoom;
	cRectMake* m_pFFLivingRoom2;
	cRectMake* m_pFFPassage;
	cRectMake* m_pFFPassage2;

	/***********************
		2Ãþ
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

