#include "stdafx.h"
#include "cMap.h"


cMap::cMap()
	: m_pFloor(NULL)
	, m_pWall(NULL)
	, m_pSurface(NULL)
	, m_pCeiling(NULL)
	, m_pObjShackles(NULL)
	, m_pObjPiano(NULL)
	, m_pObjShelf(NULL)
	, m_pObjBed(NULL)
	, m_pObjWinebarrel(NULL)
	, m_pObjPrisonbar(NULL)
	, m_pObjPrisonbarRow(NULL)
	, m_pObjBox(NULL)
	, m_pObjShelfHigh(NULL)
	, m_pObjTable(NULL)
	, m_pObjDesk(NULL)
{
	
}


cMap::~cMap()
{
	SAFE_DELETE(m_pFloor);
	SAFE_DELETE(m_pWall);
	SAFE_DELETE(m_pSurface);
	SAFE_DELETE(m_pCeiling);
	SAFE_DELETE(m_pObjShackles);
	SAFE_DELETE(m_pObjShelf);
	SAFE_DELETE(m_pObjPiano);
	SAFE_DELETE(m_pObjBed);
	SAFE_DELETE(m_pObjWinebarrel);
	SAFE_DELETE(m_pObjBox);
	SAFE_DELETE(m_pObjPrisonbar);
	SAFE_DELETE(m_pObjPrisonbarRow);
	SAFE_DELETE(m_pObjShelfHigh);
	SAFE_DELETE(m_pObjTable);
	SAFE_DELETE(m_pObjDesk);
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

	
	m_pObjPrisonbar = new cMapObject;
	m_pObjPrisonbar->Setup("Objects/map", "wriggle_prison_bar2.obj");
	
	m_pObjPrisonbarRow = new cMapObject;
	m_pObjPrisonbarRow->Setup("Objects/map", "wriggle_prison_bar2.obj");
	
	m_pObjShelf = new cMapObject;
	m_pObjShelf->Setup("Objects/map", "shelf_no_back.obj");

	m_pObjBox = new cMapObject;
	m_pObjBox->Setup("Objects", "box.obj");
		
	m_pObjPiano = new cMapObject;
	m_pObjPiano->Setup("Objects/map", "piano.obj");

	m_pObjBed = new cMapObject;
	m_pObjBed->Setup("Objects/map", "bed_nice.obj");

	m_pObjWinebarrel = new cMapObject;
	m_pObjWinebarrel->Setup("Objects/map", "big_wine_barrel.obj");

	m_pObjShelfHigh = new cMapObject;
	m_pObjShelfHigh->Setup("Objects/map", "shelf_high01.obj");
	
	m_pObjTable = new cMapObject;
	m_pObjTable->Setup("Objects/map", "table_wood01.obj");

	m_pObjDesk = new cMapObject;
	m_pObjDesk->Setup("Objects/map", "work_desk.obj");
}

void cMap::Render()
{
	m_pSurface->Render();
	m_pFloor->Render();
	m_pWall->Render();
	m_pCeiling->Render();	

	RenderObject();
}

void cMap::RenderObject()
{
	m_pObjShackles->Render(0.08, 33, 7, -24, 1);

	for (int i = 0; i < 12; i++)
	{
		m_pObjPrisonbar->Render(0.33, -31 - i, 0, 12.8, 0);
	}
	
	for (int i = 0; i < 12; i++)
	{
		m_pObjPrisonbarRow->Render(0.33, -22, 0, 12.8 + i, 0);
	}
	
	m_pObjShelf->Render(0.08, 5, 0, 13.5, 1.5);

	m_pObjBox->Render(1, 0, 1, 23, 0);
	m_pObjBox->Render(1, 2.2, 1, 23, 0);
	m_pObjBox->Render(1, 4.5, 1, 23, 0);
	m_pObjBox->Render(1, -2, 1, 23, 0);
	m_pObjBox->Render(1, -1, 3, 23, 0);
	m_pObjBox->Render(1, 3, 3, 23, 0);

	m_pObjPiano->Render(0.13, -18, 12, 0, 0);
	m_pObjBed->Render(0.095, -4, 12, -37, 0.5);
	m_pObjWinebarrel->Render(0.05, 5, 0, -7.5, -0.5);

	m_pObjShelfHigh->Render(0.07, -10, 24, -22.5, 0.5);
	m_pObjShelfHigh->Render(0.07, -4, 24, -22.5, 0.5);
	m_pObjShelfHigh->Render(0.07, 2, 24, -22.5, 0.5);
	m_pObjShelfHigh->Render(0.07, 8, 24, -22.5, 0.5);

	//m_pObjTable->Render(0.1, 0, 0, 0, 0);
	m_pObjDesk->Render(10, 0, 0, 0, 0);
}
