#include "stdafx.h"
#include "cMap.h"


cMap::cMap()
	: m_pFloor(NULL)
	, m_pWall(NULL)
	, m_pSurface(NULL)
	, m_pCeiling(NULL)
{

}


cMap::~cMap()
{
	SAFE_DELETE(m_pFloor);
	SAFE_DELETE(m_pWall);
	SAFE_DELETE(m_pSurface);
	SAFE_DELETE(m_pCeiling);
}

void cMap::Setup()
{
	m_pFloor = new cFloor;
	m_pFloor->Setup();
	m_pWall = new cWall;
	m_pWall->Setup();
	m_pSurface = new cSurface;
	m_pSurface->Setup();
	m_pCeiling = new cCeiling;
	m_pCeiling->Setup();

}

void cMap::Render()
{
	//m_pSurface->Render();
	m_pFloor->Render();
	m_pWall->Render();
	m_pCeiling->Render();
	
}
