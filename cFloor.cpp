#include "stdafx.h"
#include "cFloor.h"


cFloor::cFloor()
{
}


cFloor::~cFloor()
{
	for each (auto it in m_vecFloorRect)
	{
		SAFE_DELETE(it);
	}
	m_vecFloorRect.clear();
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
	m_vecFloorRect.push_back(m_pB1FStartRoom);

	m_pB1FBlood = new cRectMake;
	m_pB1FBlood->Setup(D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 0)
		, "Texture/maps/blood_stain_small.dds");
	m_vecFloorRect.push_back(m_pB1FBlood);
	
	//첫방 바닥
	m_pB1FRoom = new cRectMake;
	m_pB1FRoom->Setup(D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 0)
		, "Texture/maps/castlebase_floor_emblem.dds");
	m_vecFloorRect.push_back(m_pB1FRoom);

	D3DXVECTOR3 v0, v1, v2, v3;
	for (size_t i = 0; i < 10; i++) {
		m_pB1Stair[i] = new cRectMake;
		v0 = D3DXVECTOR3(CENTERX + 9, (FF - B1F) * 0.1 * i, CENTERZ - 0.5 + (-0.3 * i));
		v1 = D3DXVECTOR3(CENTERX + 9, (FF - B1F) * 0.1 * i, CENTERZ + (-0.3 * i));
		v2 = D3DXVECTOR3(CENTERX + 10, (FF - B1F) * 0.1 * i, CENTERZ + (-0.3 * i));
		v3 = D3DXVECTOR3(CENTERX + 10, (FF - B1F) * 0.1 * i, CENTERZ - 0.5 + (-0.3 * i));
		m_pB1Stair[i]->Setup(v0, v1, v2, v3, "Texture/maps/cs_office_texture_34.jpg");
		m_vecFloorRect.push_back(m_pB1Stair[i]);

		m_pB1StairWall[i] = new cRectMake;
		v0 = D3DXVECTOR3(CENTERX + 10, (FF - B1F) * 0.1 * i, CENTERZ - (0.3 * i) - 0.3);
		v1 = D3DXVECTOR3(CENTERX + 10, (FF - B1F) * 0.1 * (i + 1), CENTERZ - (0.3 * i) - 0.3);
		v2 = D3DXVECTOR3(CENTERX + 9, (FF - B1F) * 0.1 * (i + 1), CENTERZ - (0.3 * i) - 0.3);
		v3 = D3DXVECTOR3(CENTERX + 9, (FF - B1F) * 0.1 * i, CENTERZ - (0.3 * i) - 0.3);
		m_pB1StairWall[i]->Setup(v0, v1, v2, v3, "Texture/maps/cs_office_texture_34.jpg");
		m_vecFloorRect.push_back(m_pB1StairWall[i]);
	}


	/***********************
	1층
	************************/
	//방
	/*
	m_pFFRoom = new cRectMake;
	m_pFFRoom->Setup(D3DXVECTOR3(CENTERX + 3, FF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 6, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 0.5)
		, "Texture/maps/dobaemall_1814.jpg");
	m_vecFloorRect.push_back();
	*/

	m_pFFRoom2 = new cRectMake;
	m_pFFRoom2->Setup(D3DXVECTOR3(CENTERX + 3, FF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 2.25)
		, D3DXVECTOR3(CENTERX + 4.5, FF, CENTERZ + 2.25)
		, D3DXVECTOR3(CENTERX + 4.5, FF, CENTERZ - 0.5)
		, "Texture/maps/dobaemall_1814.jpg");
	m_vecFloorRect.push_back(m_pFFRoom2);

	m_pFFRoom3 = new cRectMake;
	m_pFFRoom3->Setup(D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 2.25)
		, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 3.67, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 3.67, FF, CENTERZ + 2.25)
		, "Texture/maps/dobaemall_1814.jpg");
	m_vecFloorRect.push_back(m_pFFRoom3);

	m_pFFRoom4 = new cRectMake;
	m_pFFRoom4->Setup(D3DXVECTOR3(CENTERX + 3.67, FF, CENTERZ + 3.9)
		, D3DXVECTOR3(CENTERX + 3.67, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 4.5, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 4.5, FF, CENTERZ + 3.9)
		, "Texture/maps/dobaemall_1814.jpg");
	m_vecFloorRect.push_back(m_pFFRoom4);
	
	//방 무너진 바닥
	m_pFFRoomCollision = new cRectMake;
	m_pFFRoomCollision->Setup(D3DXVECTOR3(CENTERX + 4.5, FF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 4.5, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 6, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 0.5)
		, "Texture/maps/dobaemall_1814.jpg");
	m_vecFloorRect.push_back(m_pFFRoomCollision);

	//화장실
	m_pFFBathRoom = new cRectMake;
	m_pFFBathRoom->Setup(D3DXVECTOR3(CENTERX + 3, FF, CENTERZ - 4)
		, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 4)
		, "Texture/maps/bathRoom.jpg");
	m_vecFloorRect.push_back(m_pFFBathRoom);

	//화장실 핏자국
	m_pBloodPrint = new cRectMake;
	m_pBloodPrint->Setup(D3DXVECTOR3(CENTERX + 3, FF, CENTERZ - 4)
		, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 4)
		, "Texture/maps/blood_stain_small.dds");
	m_vecFloorRect.push_back(m_pBloodPrint);

	//거실1
	m_pFFLivingRoom = new cRectMake;
	m_pFFLivingRoom->Setup(D3DXVECTOR3(CENTERX + 10, FF, CENTERZ - 3)
		, D3DXVECTOR3(CENTERX + 10, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 13, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 13, FF, CENTERZ - 3)
		, "Texture/maps/granit_texture1866.jpg");
	m_vecFloorRect.push_back(m_pFFLivingRoom);

	//거실2
	m_pFFLivingRoom2 = new cRectMake;
	m_pFFLivingRoom2->Setup(D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 6, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 10, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 10, FF, CENTERZ - 0.5)
		, "Texture/maps/granit_texture1866.jpg");
	m_vecFloorRect.push_back(m_pFFLivingRoom2);

	//통로1
	m_pFFPassage = new cRectMake;
	m_pFFPassage->Setup(D3DXVECTOR3(CENTERX + 5.9, FF, CENTERZ - 4)
		, D3DXVECTOR3(CENTERX + 5.9, FF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 9, FF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 9, FF, CENTERZ - 4)
		, "Texture/maps/granit_texture1866.jpg");
	m_vecFloorRect.push_back(m_pFFPassage);

	//통로2
	m_pFFPassage2 = new cRectMake;
	m_pFFPassage2->Setup(D3DXVECTOR3(CENTERX + 7.8, FF, CENTERZ - 4)
		, D3DXVECTOR3(CENTERX + 7.8, FF, CENTERZ - 3)
		, D3DXVECTOR3(CENTERX + 13, FF, CENTERZ - 3)
		, D3DXVECTOR3(CENTERX + 13, FF, CENTERZ - 4)
		, "Texture/maps/granit_texture1866.jpg");
	m_vecFloorRect.push_back(m_pFFPassage2);


	for (size_t i = 0; i < 11; i++) {
		m_pB1Stair2[i] = new cRectMake;
		v0 = D3DXVECTOR3(CENTERX + 7.8, ((SF - FF) * 0.1 * i) + FF, CENTERZ - 3 + (0.2 * i)); 
		v1 = D3DXVECTOR3(CENTERX + 7.8, ((SF - FF) * 0.1 * i) + FF, CENTERZ - 2.5 + (0.2 * i));
		v2 = D3DXVECTOR3(CENTERX + 9, ((SF - FF) * 0.1 * i) + FF, CENTERZ - 2.5 + (0.2 * i));
		v3 = D3DXVECTOR3(CENTERX + 9, ((SF - FF) * 0.1 * i) + FF, CENTERZ - 3 + (0.2 * i));
		m_pB1Stair2[i]->Setup(v0, v1, v2, v3, "Texture/maps/cs_office_texture_34.jpg");
		m_vecFloorRect.push_back(m_pB1Stair2[i]);
	}
	for (size_t i = 0; i < 10; i++) {
	
		m_pB1Stair2Wall[i] = new cRectMake;
		v0 = D3DXVECTOR3(CENTERX + 7.8, FF + (SF - FF) * 0.1 * i, CENTERZ + (0.2 * i) - 2.75);
		v1 = D3DXVECTOR3(CENTERX + 7.8, FF + (SF - FF) * 0.1 * (i + 1), CENTERZ + (0.2 * i) - 2.75);
		v2 = D3DXVECTOR3(CENTERX + 9, FF + (SF - FF) * 0.1 * (i + 1), CENTERZ + (0.2 * i) - 2.75);
		v3 = D3DXVECTOR3(CENTERX + 9, FF + (SF - FF) * 0.1 * i, CENTERZ + (0.2 * i) - 2.75);
		m_pB1Stair2Wall[i]->Setup(v0, v1, v2, v3, "Texture/maps/cs_office_texture_34.jpg");
		m_vecFloorRect.push_back(m_pB1Stair2Wall[i]);
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
		, "Texture/maps/granit_texture1866.jpg");
	m_vecFloorRect.push_back(m_pSFLeftRoom);

	//오른쪽 방
	m_pSFRightRoom = new cRectMake;
	m_pSFRightRoom->Setup(D3DXVECTOR3(CENTERX + 9, SF, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 9, SF, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 10.7, SF, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 10.7, SF, CENTERZ - 2.2)
		, "Texture/maps/granit_texture1866.jpg");
	m_vecFloorRect.push_back(m_pSFRightRoom);

	//통로
	m_pSFPassage = new cRectMake;
	m_pSFPassage->Setup(D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ - 0.5)
		, D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 9, SF, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 9, SF, CENTERZ - 0.5)
		, "Texture/maps/granit_texture1866.jpg");
	m_vecFloorRect.push_back(m_pSFPassage);

}

void cFloor::Render()
{
	for each (auto it in m_vecFloorRect)
	{
		it->Render();
	}
}

