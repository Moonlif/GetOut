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
	cMapObject* m_pObjPrisonbar[12];
	cMapObject* m_pObjPrisonbarRow[12];
	
public:
	cMap();
	~cMap();
	void Setup();
	void SetupObject();
	void Render();
	void RenderObject();
	cSurface* getSurface() { return m_pSurface; };
};

