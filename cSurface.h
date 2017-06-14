#pragma once
#include "cRectMake.h"

struct PassSurface
{
	D3DXVECTOR3 p;
	int nindex;

};
struct Surface
{
	D3DXVECTOR3 p;
	int floor;
};

/*
struct Check
{
	int nIndex;
	bool isOpen;
};
*/
class cSurface
{
private:
	SYNTHESIZE(std::vector<Surface>, vecVertex, VecVertex);
	SYNTHESIZE(std::vector<PassSurface>, passVertex, PassVertex);
	
	
private:
	//ÁöÇÏ
	cRectMake* m_pB1StartRoom;
	cRectMake* m_pB1Prison;
	cRectMake* m_pB1StartSpace;
	cRectMake* m_pB1NextRoom;
	cRectMake* m_pB1StairSurface;
	cRectMake* m_pB1StairPass;
	
	//1Ãþ
	cRectMake* m_pFFPassage;
	cRectMake* m_pFFPassage2;
	cRectMake* m_pFFLivingRoom;
	cRectMake* m_pFFLivingRoom2;
	cRectMake* m_pFFRoom;
	cRectMake* m_pFFRoom1;
	cRectMake* m_pFFBathRoom;
	cRectMake* m_pFFStairSurface;
	//2Ãþ
	cRectMake* m_pSFPassage;
	cRectMake* m_pSFRoom;
	cRectMake* m_pSFRoom2;
	


	//¹® Åë·Î
	cRectMake* m_pB1PrisonDoor;
	cRectMake* m_pB1Door;
	cRectMake* m_pBathRoomWall;
	cRectMake* m_pBathRoomDoor;
	cRectMake* m_pFFRoomDoor;
	cRectMake* m_pSFRoomDoor1;
	cRectMake* m_pSFRoomDoor2;
	cRectMake* m_pFFCollision;
	cRectMake* m_pWoodWay;
	
	
	//Check m_pCheked[8];

	LPDIRECT3DTEXTURE9		   m_pTexture;
	D3DMATERIAL9			   m_stMtl;
public:
	cSurface();
	~cSurface();
	void Setup();
	void Render();
	void PassSetup();
	void PassInput(PassSurface v0, PassSurface v1, PassSurface v2, PassSurface v3, int index);
//	bool getCheckOpen(int index) { return m_pCheked[index].isOpen; }
//	void setCheckOpen(int index, bool isOpen) { m_pCheked[index].isOpen = isOpen; }
};

