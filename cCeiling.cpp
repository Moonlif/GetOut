#include "stdafx.h"
#include "cCeiling.h"


cCeiling::cCeiling()
	: m_pB1FStartRoom(NULL)
	, m_pB1FRoom(NULL)

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


cCeiling::~cCeiling()
{
	SAFE_DELETE(m_pB1FStartRoom);
	SAFE_DELETE(m_pB1FRoom);

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

	//첫방 천장
	m_pB1FRoom = new cRectMake;
	m_pB1FRoom->Setup(D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 12, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 12, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 4)
		, "Texture/maps/cs_office_texture_7.jpg");

	/***********************
	1층
	************************/
	//방
	m_pFFRoom = new cRectMake;
	m_pFFRoom->Setup(D3DXVECTOR3(CENTERX + 3, SF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 6, SF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 3, SF, CENTERZ + 4)
		, "Texture/maps/cs_office_texture_7.jpg");

	//화장실
	m_pFFBathRoom = new cRectMake;
	m_pFFBathRoom->Setup(D3DXVECTOR3(CENTERX + 3, SF, CENTERZ - 4)
		, D3DXVECTOR3(CENTERX + 5.9, SF, CENTERZ - 4)
		, D3DXVECTOR3(CENTERX + 5.9, SF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 3, SF, CENTERZ - 0.5)
		, "Texture/maps/cs_office_texture_7.jpg");
	//거실
	m_pFFLivingRoom = new cRectMake;
	m_pFFLivingRoom->Setup(D3DXVECTOR3(CENTERX + 9, SF, CENTERZ - 3)
		, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ - 3)
		, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 9, SF, CENTERZ + 4)
		, "Texture/maps/cs_office_texture_7.jpg");

	m_pFFLivingRoom2 = new cRectMake;
	m_pFFLivingRoom2->Setup(D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 10.1, SF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 10.1, SF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 6, SF, CENTERZ + 4)
		, "Texture/maps/cs_office_texture_7.jpg");
	//통로
	m_pFFPassage = new cRectMake;
	m_pFFPassage->Setup(D3DXVECTOR3(CENTERX + 5.9, SF, CENTERZ - 4)
		, D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ - 4)
		, D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 5.9, SF, CENTERZ - 0.5)
		, "Texture/maps/cs_office_texture_7.jpg");

	m_pFFPassage2 = new cRectMake;
	m_pFFPassage2->Setup(D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ - 4)
		, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ - 4)
		, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ - 3)
		, D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ - 3)
		, "Texture/maps/cs_office_texture_7.jpg");

	/***********************
	2층
	************************/
	m_pSFLeftRoom = new cRectMake;
	m_pSFLeftRoom->Setup(D3DXVECTOR3(CENTERX + 6, TOP, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 7.8, TOP, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 7.8, TOP, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 6, TOP, CENTERZ + 3)
		, "Texture/maps/cs_office_texture_7.jpg");
	m_pSFRightRoom = new cRectMake;
	m_pSFRightRoom->Setup(D3DXVECTOR3(CENTERX + 9, TOP, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 10.7, TOP, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 10.7, TOP, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 9, TOP, CENTERZ + 3)
		, "Texture/maps/cs_office_texture_7.jpg");
	m_pSFPassage = new cRectMake;
	m_pSFPassage->Setup(D3DXVECTOR3(CENTERX + 7.8, TOP, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 9, TOP, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 9, TOP, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 7.8, TOP, CENTERZ + 3)
		, "Texture/maps/cs_office_texture_7.jpg");
}

void cCeiling::Render()
{
	m_pB1FStartRoom->Render();
	m_pB1FRoom->Render();

	m_pFFRoom->Render();
	m_pFFBathRoom->Render();
	m_pFFLivingRoom->Render();
	m_pFFLivingRoom2->Render();
	m_pFFPassage->Render();
	m_pFFPassage2->Render();

	m_pSFLeftRoom->Render();
	m_pSFRightRoom->Render();
	m_pSFPassage->Render();
}
