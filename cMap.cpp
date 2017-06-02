#include "stdafx.h"
#include "cMap.h"


cMap::cMap()
	: m_pFloor(NULL)
	, m_pWall(NULL)
{

}


cMap::~cMap()
{
	SAFE_DELETE(m_pFloor);
	SAFE_DELETE(m_pWall);
}

void cMap::Setup()
{
	m_pFloor = new cFloor;
	m_pFloor->Setup();
	m_pWall = new cWall;
	m_pWall->Setup();
}

void cMap::Render()
{
	m_pFloor->Render();
	m_pWall->Render();
}
