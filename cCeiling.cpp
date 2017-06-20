#include "stdafx.h"
#include "cCeiling.h"


cCeiling::cCeiling()
{
}


cCeiling::~cCeiling()
{
	for each (auto it in m_vecRect)
	{
		SAFE_DELETE(it);
	}
	m_vecRect.clear();
	SAFE_DELETE(m_pB1FStartRoom);

	SAFE_DELETE(m_pB1FCollision);
	SAFE_DELETE(m_pB1FCollision2);
	SAFE_DELETE(m_pB1FCollision3);
	SAFE_DELETE(m_pB1FCollision4);

}


void cCeiling::Setup()
{
	/**********************
	지하
	**********************/
	//스타팅 천장
	m_pB1FStartRoom = new cRectMake;
	m_pB1FStartRoom->Setup(D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 12, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 12, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 4)
		, "Texture/maps/castlebase_ceiling03.dds");


	//무너진 천장
	m_pB1FCollision = new cRectMake;
	m_pB1FCollision->Setup(D3DXVECTOR3(CENTERX + 4.5, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 12, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 12, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 4.5, FF, CENTERZ + 4)
		, "Texture/maps/castlebase_ceiling03.dds");
	
	m_pB1FCollision2 = new cRectMake;
	m_pB1FCollision2->Setup(D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 3.67, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 3.67, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 4)
		, "Texture/maps/castlebase_ceiling03.dds");

	m_pB1FCollision3 = new cRectMake;
	m_pB1FCollision3->Setup(D3DXVECTOR3(CENTERX + 3.67, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 4.5, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 4.5, FF, CENTERZ + 2.3)
		, D3DXVECTOR3(CENTERX + 3.67, FF, CENTERZ + 2.3)
		, "Texture/maps/castlebase_ceiling03.dds");
	m_pB1FCollision4 = new cRectMake;

	m_pB1FCollision4->Setup(D3DXVECTOR3(CENTERX + 3.67, FF, CENTERZ + 3.9)
		, D3DXVECTOR3(CENTERX + 4.5, FF, CENTERZ + 3.9)
		, D3DXVECTOR3(CENTERX + 4.5, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 3.67, FF, CENTERZ + 4)
		, "Texture/maps/castlebase_ceiling03.dds");


	//첫방 천장
	m_pB1FRoom = new cRectMake;
	m_pB1FRoom->Setup(D3DXVECTOR3(CENTERX + 8, FF, CENTERZ - 1)
		, D3DXVECTOR3(CENTERX + 12, FF, CENTERZ - 1)
		, D3DXVECTOR3(CENTERX + 12, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 4)
		, "Texture/maps/castlebase_ceiling03.dds");
	m_vecRect.push_back(m_pB1FRoom);
	/***********************
	1층
	************************/
	//방
	m_pFFRoom = new cRectMake;
	m_pFFRoom->Setup(D3DXVECTOR3(CENTERX + 3, SF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 6, SF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 3, SF, CENTERZ + 4)
		, "Texture/maps/cell.jpg");
	m_vecRect.push_back(m_pFFRoom);

	//화장실
	m_pFFBathRoom = new cRectMake;
	m_pFFBathRoom->Setup(D3DXVECTOR3(CENTERX + 3, SF, CENTERZ - 4)
		, D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 4)
		, D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 3, SF, CENTERZ - 0.5)
		, "Texture/maps/bathRoom.jpg");
	m_vecRect.push_back(m_pFFBathRoom);

	m_pFFBathRoomPrint = new cRectMake;
	m_pFFBathRoomPrint->Setup(D3DXVECTOR3(CENTERX + 3.5, SF, CENTERZ - 3.5)
		, D3DXVECTOR3(CENTERX + 5.5, SF, CENTERZ - 3.5)
		, D3DXVECTOR3(CENTERX + 5.5, SF, CENTERZ - 1)
		, D3DXVECTOR3(CENTERX + 3.5, SF, CENTERZ - 1)
		, "Texture/maps/maze_writing04.dds");
	m_vecRect.push_back(m_pFFBathRoomPrint);


	//거실
	m_pFFLivingRoom = new cRectMake;
	m_pFFLivingRoom->Setup(D3DXVECTOR3(CENTERX + 9, SF, CENTERZ - 3)
		, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ - 3)
		, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 9, SF, CENTERZ + 4)
		, "Texture/maps/cell.jpg");
	m_vecRect.push_back(m_pFFLivingRoom);

	m_pFFLivingRoom2 = new cRectMake;
	m_pFFLivingRoom2->Setup(D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 10.1, SF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 10.1, SF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 6, SF, CENTERZ + 4)
		, "Texture/maps/cell.jpg");
	m_vecRect.push_back(m_pFFLivingRoom2);

	//통로
	m_pFFPassage = new cRectMake;
	m_pFFPassage->Setup(D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 4)
		, D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ - 4)
		, D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 0.5)
		, "Texture/maps/cell.jpg");
	m_vecRect.push_back(m_pFFPassage);


	m_pFFPassage2 = new cRectMake;
	m_pFFPassage2->Setup(D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ - 4)
		, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ - 4)
		, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ - 3)
		, D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ - 3)
		, "Texture/maps/cell.jpg");
	m_vecRect.push_back(m_pFFPassage2);


	/***********************
	2층
	************************/
	m_pSFLeftRoom = new cRectMake;
	m_pSFLeftRoom->Setup(D3DXVECTOR3(CENTERX + 6, TOP, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 7.8, TOP, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 7.8, TOP, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 6, TOP, CENTERZ + 3)
		, "Texture/maps/cell.jpg");
	m_vecRect.push_back(m_pSFLeftRoom);

	m_pSFRightRoom = new cRectMake;
	m_pSFRightRoom->Setup(D3DXVECTOR3(CENTERX + 9, TOP, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 10.7, TOP, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 10.7, TOP, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 9, TOP, CENTERZ + 3)
		, "Texture/maps/cell.jpg");
	m_vecRect.push_back(m_pSFRightRoom);

	m_pSFPassage = new cRectMake;
	m_pSFPassage->Setup(D3DXVECTOR3(CENTERX + 7.8, TOP, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 9, TOP, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 9, TOP, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 7.8, TOP, CENTERZ + 3)
		, "Texture/maps/cell.jpg");
	m_vecRect.push_back(m_pSFPassage);
}

void cCeiling::Render()
{
	for each (auto it in m_vecRect)
	{
		it->Render();
	}
	//무너지기 전
	if (!g_pData->m_bStuffSwitch[SWITCH_FIRSTFLOOR_TRAP])
		m_pB1FStartRoom->Render();
	//무너진후 천장
	else{
		m_pB1FCollision->Render();
		m_pB1FCollision2->Render();
		m_pB1FCollision3->Render();
		m_pB1FCollision4->Render();
	}
}
