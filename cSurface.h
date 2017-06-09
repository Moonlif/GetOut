#pragma once
#include "cRectMake.h"

struct PassSurface
{
	D3DXVECTOR3 p;
	int nindex;
	bool isOpen;
};

class cSurface
{
private:
	SYNTHESIZE(std::vector<D3DXVECTOR3>, vecVertex, VecVertex);
	SYNTHESIZE(std::vector<PassSurface>, passVertex, PassVertex);
private:
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
	cRectMake* m_pFFLivingRoom2;
	cRectMake* m_pFFRoom;
	cRectMake* m_pFBathRoom;
	cRectMake* m_pB1Stair2[10];
	//2Ãþ
	cRectMake* m_pSFPassage;
	cRectMake* m_pSFRoom;
	cRectMake* m_pSFRoom2;
	


	//Åë·Î
	cRectMake* m_pB1PrisonDoor;
	cRectMake* m_pB1Door;
	cRectMake* m_pBathRoomWall;
	cRectMake* m_pBathRoomDoor;
	cRectMake* m_pFFRoomDoor;
	cRectMake* m_pSFRoomDoor1;
	cRectMake* m_pSFRoomDoor2;



	LPDIRECT3DTEXTURE9		   m_pTexture;
	D3DMATERIAL9			   m_stMtl;
public:
	cSurface();
	~cSurface();
	void Setup();
	void Render();
	void PassSetup();
};

