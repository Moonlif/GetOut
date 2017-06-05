#pragma once
#include "cFloor.h"
#include "cWall.h"
#include "cCeiling.h"
#include "cSurface.h"
#include "cObjLoader.h"


class cMap
{
private:
	cFloor*		m_pFloor;
	cSurface*	m_pSurface;
	cWall*		m_pWall;
	cCeiling*	m_pCeiling;
	
public:
	cMap();
	~cMap();
	void Setup();
	void Render();
};

