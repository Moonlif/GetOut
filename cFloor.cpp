#include "stdafx.h"
#include "cFloor.h"


cFloor::cFloor()
	: m_pB1FStartRoom(NULL)
	, m_pB1FRoom(NULL)
	, m_pB1Water(NULL)
	, m_pB1FBlood(NULL)

	, m_pFFRoom(NULL)
	, m_pFFBathRoom(NULL)
	, m_pFFLivingRoom(NULL)
	, m_pFFLivingRoom2(NULL)
	, m_pFFPassage(NULL)
	, m_pFFPassage2(NULL)

	, m_pSFLeftRoom(NULL)
	, m_pSFRightRoom(NULL)
	, m_pSFPassage(NULL)
{
}


cFloor::~cFloor()
{
	SAFE_DELETE(m_pB1FStartRoom);
	SAFE_DELETE(m_pB1FRoom);
	SAFE_DELETE(m_pB1Water);
	SAFE_DELETE(m_pB1FBlood);

	SAFE_DELETE(m_pFFRoom);
	SAFE_DELETE(m_pFFBathRoom);
	SAFE_DELETE(m_pFFLivingRoom);
	SAFE_DELETE(m_pFFLivingRoom2);
	SAFE_DELETE(m_pFFPassage);
	SAFE_DELETE(m_pFFPassage2);

	SAFE_DELETE(m_pSFLeftRoom);
	SAFE_DELETE(m_pSFRightRoom);
	SAFE_DELETE(m_pSFPassage);
}

void cFloor::Setup()
{
	/**********************
		지하
	**********************/
	//스타팅 바닥
	m_pB1FStartRoom = new cRectMake;
	m_pB1FStartRoom->Setup(D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 0)
		, "Texture/maps/castlebase_floor.dds");

	m_pB1FBlood = new cRectMake;
	m_pB1FBlood->Setup(D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 0)
		, "Texture/maps/blood_stain_small.dds");


	m_pB1Water = new cRectMake;
	m_pB1Water->Setup(D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 0)
		, "Texture/maps/water_sewer_streaming.dds");
	
	//첫방 바닥
	m_pB1FRoom = new cRectMake;
	m_pB1FRoom->Setup(D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 0)
		, "Texture/maps/castlebase_floor_emblem.dds");


	D3DXVECTOR3 v0, v1, v2, v3;
	for (size_t i = 0; i < 10; i++) {
		m_pB1Stair[i] = new cRectMake;
		v0 = D3DXVECTOR3(CENTERX + 9, (FF - B1F) * 0.1 * i, CENTERZ - 0.5 + (-0.3 * i));
		v1 = D3DXVECTOR3(CENTERX + 9, (FF - B1F) * 0.1 * i, CENTERZ + (-0.3 * i));
		v2 = D3DXVECTOR3(CENTERX + 10, (FF - B1F) * 0.1 * i, CENTERZ + (-0.3 * i));
		v3 = D3DXVECTOR3(CENTERX + 10, (FF - B1F) * 0.1 * i, CENTERZ - 0.5 + (-0.3 * i));
		m_pB1Stair[i]->Setup(v0, v1, v2, v3, "Texture/maps/cs_office_texture_34.jpg");
	}
	/***********************
	1층
	************************/
	//방
	m_pFFRoom = new cRectMake;
	m_pFFRoom->Setup(D3DXVECTOR3(CENTERX + 3, FF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 6, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 0.5)
		, "Texture/maps/carpet01.dds");

	//화장실
	m_pFFBathRoom = new cRectMake;
	m_pFFBathRoom->Setup(D3DXVECTOR3(CENTERX + 3, FF, CENTERZ - 4)
		, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 5.9, FF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 5.9, FF, CENTERZ - 4)
		, "Texture/maps/bathRoom.jpg");
	//거실1
	m_pFFLivingRoom = new cRectMake;
	m_pFFLivingRoom->Setup(D3DXVECTOR3(CENTERX + 10, FF, CENTERZ - 3)
		, D3DXVECTOR3(CENTERX + 10, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 13, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 13, FF, CENTERZ - 3)
		, "Texture/maps/cs_office_texture_7.jpg");
	//거실2
	m_pFFLivingRoom2 = new cRectMake;
	m_pFFLivingRoom2->Setup(D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 6, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 10, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 10, FF, CENTERZ - 0.5)
		, "Texture/maps/cs_office_texture_7.jpg");
	//통로1
	m_pFFPassage = new cRectMake;
	m_pFFPassage->Setup(D3DXVECTOR3(CENTERX + 5.9, FF, CENTERZ - 4)
		, D3DXVECTOR3(CENTERX + 5.9, FF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 7.8, FF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 7.8, FF, CENTERZ - 4)
		, "Texture/maps/cs_office_texture_7.jpg");
	//통로2
	m_pFFPassage2 = new cRectMake;
	m_pFFPassage2->Setup(D3DXVECTOR3(CENTERX + 7.8, FF, CENTERZ - 4)
		, D3DXVECTOR3(CENTERX + 7.8, FF, CENTERZ - 3)
		, D3DXVECTOR3(CENTERX + 13, FF, CENTERZ - 3)
		, D3DXVECTOR3(CENTERX + 13, FF, CENTERZ - 4)
		, "Texture/maps/cs_office_texture_7.jpg");

	for (size_t i = 0; i < 10; i++) {
		m_pB1Stair2[i] = new cRectMake;
		v0 = D3DXVECTOR3(CENTERX + 7.9, ((SF - FF) * 0.1 * i) + FF, CENTERZ - 3 + (0.3 * i)); 
		v1 = D3DXVECTOR3(CENTERX + 7.9, ((SF - FF) * 0.1 * i) + FF, CENTERZ - 2.5 + (0.3 * i));
		v2 = D3DXVECTOR3(CENTERX + 8.9, ((SF - FF) * 0.1 * i) + FF, CENTERZ - 2.5 + (0.3 * i));
		v3 = D3DXVECTOR3(CENTERX + 8.9, ((SF - FF) * 0.1 * i) + FF, CENTERZ - 3 + (0.3 * i));
		m_pB1Stair2[i]->Setup(v0, v1, v2, v3, "Texture/maps/cs_office_texture_34.jpg");
	}
	/***********************
	2층
	************************/
	//왼쪽 방
	m_pSFLeftRoom = new cRectMake;
	m_pSFLeftRoom->Setup(D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 6, SF, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ - 2.2)
		, "Texture/maps/cs_office_texture_7.jpg");
	//오른쪽 방
	m_pSFRightRoom = new cRectMake;
	m_pSFRightRoom->Setup(D3DXVECTOR3(CENTERX + 9, SF, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 9, SF, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 10.7, SF, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 10.7, SF, CENTERZ - 2.2)
		, "Texture/maps/cs_office_texture_7.jpg");
	//통로
	m_pSFPassage = new cRectMake;
	m_pSFPassage->Setup(D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ + 0.3)
		, D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 9, SF, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 9, SF, CENTERZ + 0.3)
		, "Texture/maps/cs_office_texture_7.jpg");
}

void cFloor::Render()
{
	m_pB1FStartRoom->Render();
	m_pB1FBlood->Render();
	m_pB1FRoom->Render();
//	m_pB1Water->Render();
	for (size_t i = 0; i < 10; i++) {
		m_pB1Stair[i]->Render();
	}

	m_pFFRoom->Render();
	m_pFFBathRoom->Render();
	m_pFFLivingRoom->Render();
	m_pFFLivingRoom2->Render();
	m_pFFPassage->Render();
	m_pFFPassage2->Render();
	for (size_t i = 0; i < 10; i++) {
		m_pB1Stair2[i]->Render();
	}


	m_pSFLeftRoom->Render();
	m_pSFRightRoom->Render();
	m_pSFPassage->Render();
}

