#include "stdafx.h"
#include "cMap.h"


cMap::cMap()
	: m_pFloor(NULL)
	, m_pWall(NULL)
	, m_pSurface(NULL)
	, m_pCeiling(NULL)
	, m_pObjShackles(NULL)
{
	for (int i = 0; i < 12; i++)
	{
		m_pObjPrisonbar[i] = NULL;
	}
	for (int i = 0; i < 12; i++)
	{
		m_pObjPrisonbarRow[i] = NULL;
	}
}


cMap::~cMap()
{
	SAFE_DELETE(m_pFloor);
	SAFE_DELETE(m_pWall);
	SAFE_DELETE(m_pSurface);
	SAFE_DELETE(m_pCeiling);

	SAFE_DELETE(m_pObjShackles);
	for (int i = 0; i < 15; i++)
	{
		SAFE_DELETE(m_pObjPrisonbar[i]);
	}
	for (int i = 0; i < 12; i++)
	{
		SAFE_DELETE(m_pObjPrisonbarRow[i]);
	}

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

	SetupObject();
}

void cMap::SetupObject()
{
	m_pObjShackles = new cMapObject;
	m_pObjShackles->Setup("Objects/map", "shackles.obj");

	for (int i = 0; i < 12; i++)
	{
		m_pObjPrisonbar[i] = new cMapObject;
		m_pObjPrisonbar[i]->Setup("Objects/map", "wriggle_prison_bar2.obj");
	}
	for (int i = 0; i < 12; i++)
	{
		m_pObjPrisonbarRow[i] = new cMapObject;
		m_pObjPrisonbarRow[i]->Setup("Objects/map", "wriggle_prison_bar2.obj");
	}
}

void cMap::Render()
{
	//m_pSurface->Render();
	m_pFloor->Render();
	m_pWall->Render();
	m_pCeiling->Render();	

	RenderObject();
}

void cMap::RenderObject()
{
	m_pObjShackles->Render(0.08, 33, 7, -24);

	for (int i = 0; i < 12; i++)
	{
		m_pObjPrisonbar[i]->Render(0.33, 42 - i, 0, -12.8);
	}

	for (int i = 0; i < 12; i++)
	{
		m_pObjPrisonbarRow[i]->Render(0.33, 21.5, 0, -12.8 - i);
	}
}
