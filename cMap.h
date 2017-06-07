#pragma once
#include "cFloor.h"
#include "cWall.h"
#include "cCeiling.h"
#include "cSurface.h"
#include "cObjLoader.h"
#include "cMapObject.h"

class cMap
{
private:
	cFloor*		m_pFloor;
	cSurface*	m_pSurface;
	cWall*		m_pWall;
	cCeiling*	m_pCeiling;
	

	cMapObject* m_pObjShackles;
	cMapObject* m_pObjPrisonbar;
	cMapObject* m_pObjPrisonbarRow;
	cMapObject* m_pObjShelf;
	cMapObject* m_pObjBox;
	cMapObject* m_pObjWinebarrel;
	cMapObject* m_pObjShelfHigh;
	cMapObject* m_pObjPiano;
	cMapObject* m_pObjBed;

	cMapObject* m_pObjDesk;
	cMapObject* m_pObjTable;
	
public:
	cMap();
	~cMap();
	void Setup();
	void SetupObject();
	void Render();
	void RenderObject();
	cSurface* getSurface() { return m_pSurface; };
};

