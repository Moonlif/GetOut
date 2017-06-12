#include "stdafx.h"
#include "cMap.h"


cMap::cMap()
	: m_pFloor(NULL)
	, m_pWall(NULL)
	, m_pSurface(NULL)
	, m_pCeiling(NULL)
	, m_pOjbSurface(NULL)
	, m_pObjShackles(NULL)
	, m_pObjPiano(NULL)
	, m_pObjShelf(NULL)
	, m_pObjBed(NULL)
	, m_pObjWinebarrel(NULL)
	, m_pObjPrisonbar(NULL)
	, m_pObjPrisonbarRow(NULL)
	, m_pObjBox(NULL)
	, m_pObjShelfHigh(NULL)
	//, m_pObjTable(NULL)
	, m_pObjDesk(NULL)
//	, m_pObjSofa(NULL)
//	, m_pObjChair(NULL)
//	, m_pObjBarrel(NULL)
	, m_pDrawers(NULL)
	, m_pIronmaiden(NULL)
	, m_pTorture(NULL)
	, m_pStonetable(NULL)
	, m_pBookPile1(NULL)
	, m_pBookRow(NULL)
{
	
}


cMap::~cMap()
{
	SAFE_DELETE(m_pFloor);
	SAFE_DELETE(m_pWall);
	SAFE_DELETE(m_pSurface);
	SAFE_DELETE(m_pCeiling);
	SAFE_DELETE(m_pOjbSurface);



	SAFE_DELETE(m_pObjShackles);
	SAFE_DELETE(m_pObjShelf);
	SAFE_DELETE(m_pObjPiano);
	SAFE_DELETE(m_pObjBed);
	SAFE_DELETE(m_pObjWinebarrel);
	SAFE_DELETE(m_pObjBox);
	SAFE_DELETE(m_pObjPrisonbar);
	SAFE_DELETE(m_pObjPrisonbarRow);
	SAFE_DELETE(m_pObjShelfHigh);
	//SAFE_DELETE(m_pObjTable);
	SAFE_DELETE(m_pObjDesk);
	//SAFE_DELETE(m_pObjSofa);
	//SAFE_DELETE(m_pObjChair);
	//SAFE_DELETE(m_pObjBarrel);
	SAFE_DELETE(m_pDrawers);
	SAFE_DELETE(m_pIronmaiden);
	SAFE_DELETE(m_pTorture);
	SAFE_DELETE(m_pStonetable);
	SAFE_DELETE(m_pBookPile1);
	SAFE_DELETE(m_pBookRow);
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
	m_pOjbSurface = new cObjectSurface;
	SetupObject();
}

void cMap::SetupObject()
{
	//족쇄
	m_pObjShackles = new cMapObject;
	m_pObjShackles->Setup("Objects/map", "shackles.obj");
	
	//쇠창살
	m_pObjPrisonbar = new cMapObject;
	m_pObjPrisonbar->Setup("Objects/map", "wriggle_prison_bar2.obj");
	m_pObjPrisonbarRow = new cMapObject;
	m_pObjPrisonbarRow->Setup("Objects/map", "wriggle_prison_bar2.obj");
	
	//지하실 선반
	m_pObjShelf = new cMapObject;
	m_pObjShelf->Setup("Objects/map", "shelf_no_back.obj");
	m_pOjbSurface->AddSurface(D3DXVECTOR3(CENTERX + 7.5, B1F, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 7.5, B1F, CENTERZ + 1.5)
		, D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 1.5)
		, D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 0));

	//지하실 와인 베럴
	m_pObjWinebarrel = new cMapObject;
	m_pObjWinebarrel->Setup("Objects/map", "big_wine_barrel.obj");
	m_pOjbSurface->AddSurface(D3DXVECTOR3(CENTERX + 10.7, B1F, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 10.7, B1F, CENTERZ + 1.5)
		, D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 1.5)
		, D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 0));

	//박스
	m_pObjBox = new cMapObject;
	m_pObjBox->Setup("Objects", "box.obj");
	m_pOjbSurface->AddSurface(D3DXVECTOR3(CENTERX + 9.4, B1F, CENTERZ + 3.5)
		, D3DXVECTOR3(CENTERX + 9.4, B1F, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 11, B1F, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 11, B1F, CENTERZ + 3.5));

	//피아노
	m_pObjPiano = new cMapObject;
	m_pObjPiano->Setup("Objects/map", "piano.obj");
	m_pOjbSurface->AddSurface(D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 6, FF, CENTERZ + 0.3)
		, D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 0.3)
		, D3DXVECTOR3(CENTERX + 8, FF, CENTERZ - 0.5));

	//서랍
	m_pDrawers = new cMapObject;
	m_pDrawers->Setup("Objects/map", "chest_of_drawers_nice.obj");
	m_pOjbSurface->AddSurface(D3DXVECTOR3(CENTERX + 8, FF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 0.3)
		, D3DXVECTOR3(CENTERX + 8.8, FF, CENTERZ + 0.3)
		, D3DXVECTOR3(CENTERX + 8.8, FF, CENTERZ - 0.5));

	//침대
	m_pObjBed = new cMapObject;
	m_pObjBed->Setup("Objects/map", "bed_nice.obj");
	m_pOjbSurface->AddSurface(D3DXVECTOR3(CENTERX + 3, FF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 1.7)
		, D3DXVECTOR3(CENTERX + 4.6, FF, CENTERZ + 1.7)
		, D3DXVECTOR3(CENTERX + 4.6, FF, CENTERZ - 0.5));

	//선반
	m_pObjShelfHigh = new cMapObject;
	m_pObjShelfHigh->Setup("Objects/map", "shelf_high01.obj");
	m_pOjbSurface->AddSurface(D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 6, SF, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 6.5, SF, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 6.5, SF, CENTERZ - 0.5));

	/*
	m_pObjTable = new cMapObject;
	m_pObjTable->Setup("Objects/map", "table_wood01.obj");
	*/
	//책상
	m_pObjDesk = new cMapObject;
	m_pObjDesk->Setup("Objects/map", "work_desk.obj");
	m_pOjbSurface->AddSurface(D3DXVECTOR3(CENTERX + 6.3, SF, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 6.3, SF, CENTERZ - 1.5)
		, D3DXVECTOR3(CENTERX + 7.7, SF, CENTERZ - 1.5)
		, D3DXVECTOR3(CENTERX + 7.7, SF, CENTERZ - 2.2));

	//아이언메이든
	m_pIronmaiden = new cMapObject;
	m_pIronmaiden->Setup("Objects/map", "iron_maiden.obj");
	m_pOjbSurface->AddSurface(D3DXVECTOR3(CENTERX + 9.3, SF, CENTERZ + 2)
		, D3DXVECTOR3(CENTERX + 9.3, SF, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 10.5, SF, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 10.5, SF, CENTERZ + 2));

	//고문 기구
	m_pTorture = new cMapObject;
	m_pTorture->Setup("Objects/map", "torture_saw_setup.obj");

	m_pOjbSurface->AddSurface(D3DXVECTOR3(CENTERX + 11.2, FF, CENTERZ - 0.3)
		, D3DXVECTOR3(CENTERX + 11.2, FF, CENTERZ + 0.7)
		, D3DXVECTOR3(CENTERX + 11.9, FF, CENTERZ + 0.7)
		, D3DXVECTOR3(CENTERX + 11.9, FF, CENTERZ - 0.3));

	m_pOjbSurface->AddSurface(D3DXVECTOR3(CENTERX + 9.1, FF, CENTERZ - 0.3)
		, D3DXVECTOR3(CENTERX + 9.1, FF, CENTERZ + 0.7)
		, D3DXVECTOR3(CENTERX + 9.8, FF, CENTERZ + 0.7)
		, D3DXVECTOR3(CENTERX + 9.8, FF, CENTERZ - 0.3));

	//돌 테이블
	m_pStonetable = new cMapObject;
	m_pStonetable->Setup("Objects/map", "stone_table.obj");
	m_pOjbSurface->AddSurface(D3DXVECTOR3(CENTERX + 10, FF, CENTERZ - 2.8)
		, D3DXVECTOR3(CENTERX + 10, FF, CENTERZ - 1.3)
		, D3DXVECTOR3(CENTERX + 10.9, FF, CENTERZ - 1.3)
		, D3DXVECTOR3(CENTERX + 10.9, FF, CENTERZ - 2.8));

	m_pBookPile1 = new cMapObject;
	m_pBookPile1->Setup("Objects/map", "book_pile01.obj");

	m_pBookRow = new cMapObject;
	m_pBookRow->Setup("Objects/map", "book_row01.obj");

	/*
	m_pOjbSurface->AddSurface(D3DXVECTOR3(CENTERX + 6.3, SF, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 6.3, SF, CENTERZ - 1.5)
		, D3DXVECTOR3(CENTERX + 7.7, SF, CENTERZ - 1.5)
		, D3DXVECTOR3(CENTERX + 7.7, SF, CENTERZ - 2.2));
		*/

	/*m_pObjSofa = new cMapObject;
	m_pObjSofa->Setup("Objects/map", "sofa.obj");

	m_pObjChair = new cMapObject;
	m_pObjChair->Setup("Objects/map", "armchair.obj");

	m_pObjBarrel = new cMapObject;
	m_pObjBarrel->Setup("Objects/map", "barrel01.obj");*/

	{
		//1지하 상자
		m_pOjbSurface->AddSurface(D3DXVECTOR3(CENTERX + 11.4, B1F, CENTERZ + 2.5)
			, D3DXVECTOR3(CENTERX + 11.4, B1F, CENTERZ + 3.5)
			, D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 3.5)
			, D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 2.5));
		
		//지하 움직이는 상자
		m_pOjbSurface->AddSurface(D3DXVECTOR3(CENTERX + 8.8, B1F, CENTERZ + 2.7)
			, D3DXVECTOR3(CENTERX + 8.8, B1F, CENTERZ + 3.5)
			, D3DXVECTOR3(CENTERX + 10.2, B1F, CENTERZ + 3.5)
			, D3DXVECTOR3(CENTERX + 10.2, B1F, CENTERZ + 2.7));

		//돌무더기
		m_pOjbSurface->AddSurface(D3DXVECTOR3(CENTERX + 11.2, FF, CENTERZ + 3)
			, D3DXVECTOR3(CENTERX + 11.2, FF, CENTERZ + 3.5)
			, D3DXVECTOR3(CENTERX + 12.6, FF, CENTERZ + 3.5)
			, D3DXVECTOR3(CENTERX + 12.6, FF, CENTERZ + 3));

		//돌무더기
		m_pOjbSurface->AddSurface(D3DXVECTOR3(CENTERX + 11.5, FF, CENTERZ + 2.3)
			, D3DXVECTOR3(CENTERX + 11.5, FF, CENTERZ + 3)
			, D3DXVECTOR3(CENTERX + 12.6, FF, CENTERZ + 3)
			, D3DXVECTOR3(CENTERX + 12.6, FF, CENTERZ + 2.3));

		//화장실 상자
		m_pOjbSurface->AddSurface(D3DXVECTOR3(CENTERX + 3.2, FF, CENTERZ - 1.2)
			, D3DXVECTOR3(CENTERX + 3.2, FF, CENTERZ - 0.7)
			, D3DXVECTOR3(CENTERX + 4, FF, CENTERZ - 0.7)
			, D3DXVECTOR3(CENTERX + 4, FF, CENTERZ - 1.2));
	}


}

void cMap::Update(int index, bool isTrue)
{
	/*
	std::vector<PassSurface> v;
	m_pSurface->GetPassVertex().assign = 1;
	m_pSurface->SetPassVertex(v);
	*/
}


void cMap::Render()
{
	
//	m_pSurface->Render();
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

	m_pObjPiano->Render(0.13, -18, 12.1, 0, 0);
	m_pObjBed->Render(0.095, -4, 12, -37, 0.5);
	m_pObjWinebarrel->Render(0.05, 5, 0, -7.5, -0.5);

	m_pObjShelfHigh->Render(0.07, -15, 24.1, -22.5, 0.5);
	m_pObjShelfHigh->Render(0.07, -10, 24.1, -22.5, 0.5);
	m_pObjShelfHigh->Render(0.07, -5, 24.1, -22.5, 0.5);
	m_pObjShelfHigh->Render(0.07, 0, 24.1, -22.5, 0.5);

	//m_pObjTable->Render(0.1, 0, 0, 0, 0);
	//m_pObjSofa->Render(0.1, 0, 12, -22, -1);
	//m_pObjChair->Render(0.1, 9, 14, -22, -1);
	//m_pObjBarrel->Render(15, 2.2, 24, 14, 0);
	//m_pObjBarrel->Render(15, -2.7, 24, 14, 0);
	m_pDrawers->Render(0.09, -10, 14.1, 0, 0);
	m_pObjDesk->Render(8.5, 18, 24.1, 11, 1);
	m_pIronmaiden->Render(0.1, 0, 24.1, -15, -1);
	m_pTorture->Render(0.1, 3, 12, 1, 0);
	m_pStonetable->Render(0.1, 3, 12, -12, 0);
	m_pBookPile1->Render(0.1, -17, 27.5, - 11.5, 0);
	//m_pBookRow->Render(0.1, -12, 26, -22, 0.5);
	//m_pOjbSurface->RenderSurface();
}
