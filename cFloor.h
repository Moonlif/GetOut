#pragma once
#include "cRectMake.h"
#define B1F 0
#define FF 3
#define SF 6
//½ºÅ¸µù ÁÂÇ¥
#define CENTERX -10
#define CENTERZ 0


class cFloor
{
private:
	SYNTHESIZE(std::vector<D3DXVECTOR3>, vecVertex, VecVertex);
	//ÁöÇÏ
	cRectMake* m_pB1StartRoom;
	cRectMake* m_pB1Prison;
	cRectMake* m_pB1StartSpace;
	cRectMake* m_pB1NextRoom;
	cRectMake* m_pB1Stair[10];
	//1Ãþ
	cRectMake* m_pFFPassage;
	cRectMake* m_pFFPassage2;
	cRectMake* m_pFFLivingRoom;
	cRectMake* m_pFFRoom;
	cRectMake* m_pFBathRoom;
	cRectMake* m_pB1Stair2[10];
	//2Ãþ
	cRectMake* m_pSFPassage;
	cRectMake* m_pSFRoom;
	cRectMake* m_pSFRoom2;

	std::vector<ST_PNT_VERTEX> m_vecBottomVertex;
	LPDIRECT3DTEXTURE9		   m_pTexture;
	D3DMATERIAL9			   m_stMtl;
public:
	cFloor();
	~cFloor();
	void Setup();
	void Render();
};

