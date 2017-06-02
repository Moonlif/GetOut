#pragma once
#include "cFloor.h"
#include "cWall.h"

class cMap
{
private:
	cFloor* m_pFloor;
	cWall* m_pWall;
public:
	cMap();
	~cMap();
	void Setup();
	void Render();
};

