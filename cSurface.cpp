#include "stdafx.h"
#include "cSurface.h"


cSurface::cSurface()
	: m_pTexture(NULL)
	, m_pB1StartRoom(NULL)
	, m_pB1Prison(NULL)
	, m_pB1StartSpace(NULL)
	, m_pB1NextRoom(NULL)
	, m_pFFPassage(NULL)
	, m_pFFPassage2(NULL)
	, m_pFFLivingRoom(NULL)
	, m_pFFLivingRoom2(NULL)
	, m_pFFRoom(NULL)
	, m_pFBathRoom(NULL)
	, m_pSFPassage(NULL)
	, m_pSFRoom(NULL)
	, m_pSFRoom2(NULL)

	, m_pB1PrisonDoor(NULL)
	, m_pB1Door(NULL)
	, m_pBathRoomWall(NULL)
	, m_pBathRoomDoor(NULL)
	, m_pFFRoomDoor(NULL)
	, m_pSFRoomDoor1(NULL)
	, m_pSFRoomDoor2(NULL)

{
	for (size_t i = 0; i < 10; i++) {
		m_pB1Stair[i] = NULL;
	}
	for (size_t i = 0; i < 10; i++) {
		m_pB1Stair2[i] = NULL;
	}
}


cSurface::~cSurface()
{
	//ÁöÇÏ
	SAFE_DELETE(m_pB1StartRoom);
	SAFE_DELETE(m_pB1Prison);
	SAFE_DELETE(m_pB1StartSpace);
	SAFE_DELETE(m_pB1NextRoom);

	for (size_t i = 0; i < 10; i++) {
		SAFE_DELETE(m_pB1Stair[i]);
	}

	//1Ãþ
	SAFE_DELETE(m_pFFPassage);
	SAFE_DELETE(m_pFFPassage2);
	SAFE_DELETE(m_pFFLivingRoom);
	SAFE_DELETE(m_pFFLivingRoom2);
	SAFE_DELETE(m_pFFRoom);
	SAFE_DELETE(m_pFBathRoom);
	for (size_t i = 0; i < 10; i++) {
		SAFE_DELETE(m_pB1Stair2[i]);
	}
	//2Ãþ
	SAFE_DELETE(m_pSFPassage);
	SAFE_DELETE(m_pSFRoom);
	SAFE_DELETE(m_pSFRoom2);

	SAFE_DELETE(m_pB1PrisonDoor);
	SAFE_DELETE(m_pB1Door);
	SAFE_DELETE(m_pFFRoomDoor);
	SAFE_DELETE(m_pBathRoomDoor);
	SAFE_DELETE(m_pBathRoomWall);
	SAFE_DELETE(m_pSFRoomDoor1);
	SAFE_DELETE(m_pSFRoomDoor2);

	SAFE_RELEASE(m_pTexture);
}

void cSurface::Setup()
{
	/*
	ÁÂÇ¥ »ç°¢Çü ÀÔ·Â
	1 2
	0 3
	//012 023
	*/
	//>> ÁöÇÏ 
	//½ºÅ¸Æ® ·ë
	m_pB1StartRoom = new cRectMake;
	D3DXVECTOR3 v0, v1, v2, v3;
	v0 = D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ); 
	v1 = D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ + 2); 
	v2 = D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 2);
	v3 = D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ);
	m_pB1StartRoom->Setup(v0, v1, v2, v3, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);

	//°¨¿Á
	m_pB1Prison = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ + 2.1); 
	v1 = D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ + 4); 
	v2 = D3DXVECTOR3(CENTERX + 6.4, B1F, CENTERZ + 4);
	v3 = D3DXVECTOR3(CENTERX + 6.4, B1F, CENTERZ + 2.1);
	m_pB1Prison->Setup(v0, v1, v2, v3, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);

	//½ºÅ¸Æ®·ë °ø°£
	m_pB1StartSpace = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 6.5, B1F, CENTERZ + 2); 
	v1 = D3DXVECTOR3(CENTERX + 6.5, B1F, CENTERZ + 4); 
	v2 = D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 4); 
	v3 = D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 2); 
	m_pB1StartSpace->Setup(v0, v1, v2, v3, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);

	//ÁöÇÏ ¹æ
	m_pB1NextRoom = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 8.1, B1F, CENTERZ); 
	v1 = D3DXVECTOR3(CENTERX + 8.1, B1F, CENTERZ + 4);
	v2 = D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 4); 
	v3 = D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ); 
	m_pB1NextRoom->Setup(v0, v1, v2, v3, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);

	//ÁöÇÏ -> 1Ãþ °è´Ü
	for (size_t i = 0; i < 10; i++) {
		m_pB1Stair[i] = new cRectMake;
		v0 = D3DXVECTOR3(CENTERX + 9, (FF - B1F) * 0.1 * i, CENTERZ - 0.5 + (-0.3 * i));
		v1 = D3DXVECTOR3(CENTERX + 9, (FF - B1F) * 0.1 * i, CENTERZ + (-0.3 * i));
		v2 = D3DXVECTOR3(CENTERX + 10, (FF - B1F) * 0.1 * i, CENTERZ + (-0.3 * i)); 
		v3 = D3DXVECTOR3(CENTERX + 10, (FF - B1F) * 0.1 * i, CENTERZ - 0.5 + (-0.3 * i));
		m_pB1Stair[i]->Setup(v0, v1, v2, v3, NULL);
		vecVertex.push_back(v0);
		vecVertex.push_back(v1);
		vecVertex.push_back(v2);

		vecVertex.push_back(v0);
		vecVertex.push_back(v2);
		vecVertex.push_back(v3);
	}

	//>>1Ãþ

	//1Ãþ Åë·Î1
	m_pFFPassage = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 4); 
	v1 = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 3); 
	v2 = D3DXVECTOR3(CENTERX + 13, FF, CENTERZ - 3);
	v3 = D3DXVECTOR3(CENTERX + 13, FF, CENTERZ - 4);
	m_pFFPassage->Setup(v0, v1, v2, v3, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);

	//1Ãþ Åë·Î2
	m_pFFPassage2 = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 3); 
	v1 = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 0.5); 
	v2 = D3DXVECTOR3(CENTERX + 7.8, FF, CENTERZ - 0.5);
	v3 = D3DXVECTOR3(CENTERX + 7.8, FF, CENTERZ - 3); 
	m_pFFPassage2->Setup(v0, v1, v2, v3, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);
	//°Å½Ç
	m_pFFLivingRoom = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 10.1, FF, CENTERZ - 3);
	v1 = D3DXVECTOR3(CENTERX + 10.1, FF, CENTERZ + 4);
	v2 = D3DXVECTOR3(CENTERX + 13, FF, CENTERZ + 4); 
	v3 = D3DXVECTOR3(CENTERX + 13, FF, CENTERZ - 3); 
	m_pFFLivingRoom->Setup(v0, v1, v2, v3, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);

	//°Å½Ç 2
	m_pFFLivingRoom2 = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 6.1, FF, CENTERZ - 0.4); 
	v1 = D3DXVECTOR3(CENTERX + 6.1, FF, CENTERZ + 4); 
	v2 = D3DXVECTOR3(CENTERX + 10.1, FF, CENTERZ + 4);
	v3 = D3DXVECTOR3(CENTERX + 10.1, FF, CENTERZ - 0.4); 
	m_pFFLivingRoom2->Setup(v0, v1, v2, v3, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);

	//¹æ
	m_pFFRoom = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 3, FF, CENTERZ - 0.4);
	v1 = D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 4); 
	v2 = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ + 4); 
	v3 = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 0.4); 
	m_pFFRoom->Setup(v0, v1, v2, v3, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);

	//È­Àå½Ç

	m_pFBathRoom = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 3, FF, CENTERZ - 4);
	v1 = D3DXVECTOR3(CENTERX + 3, FF, CENTERZ - 0.5); 
	v2 = D3DXVECTOR3(CENTERX + 5.9, FF, CENTERZ - 0.5);
	v3 = D3DXVECTOR3(CENTERX + 5.9, FF, CENTERZ - 4); 
	m_pFBathRoom->Setup(v0, v1, v2, v3, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);

	//1Ãþ -> 2Ãþ °è´Ü
	for (size_t i = 0; i < 10; i++) {
		m_pB1Stair2[i] = new cRectMake;
		v0 = D3DXVECTOR3(CENTERX + 7.9, ((SF - FF) * 0.1 * i) + FF, CENTERZ - 3 + (0.3 * i)); 
		v1 = D3DXVECTOR3(CENTERX + 7.9, ((SF - FF) * 0.1 * i) + FF, CENTERZ - 2.5 + (0.3 * i)); 
		v2 = D3DXVECTOR3(CENTERX + 8.9, ((SF - FF) * 0.1 * i) + FF, CENTERZ - 2.5 + (0.3 * i)); 
		v3 = D3DXVECTOR3(CENTERX + 8.9, ((SF - FF) * 0.1 * i) + FF, CENTERZ - 3 + (0.3 * i)); 
		m_pB1Stair2[i]->Setup(v0, v1, v2, v3, NULL);
		vecVertex.push_back(v0);
		vecVertex.push_back(v1);
		vecVertex.push_back(v2);

		vecVertex.push_back(v0);
		vecVertex.push_back(v2);
		vecVertex.push_back(v3);
	}

	//2Ãþ
	//2Ãþ Åë·Î
	m_pSFPassage = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ + 0.3);
	v1 = D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ + 3);
	v2 = D3DXVECTOR3(CENTERX + 9, SF, CENTERZ + 3);
	v3 = D3DXVECTOR3(CENTERX + 9, SF, CENTERZ + 0.3);
	m_pSFPassage->Setup(v0, v1, v2, v3, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);


	//2Ãþ ·ë1
	m_pSFRoom = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 9.1, SF, CENTERZ - 2.2); 
	v1 = D3DXVECTOR3(CENTERX + 9.1, SF, CENTERZ + 3); 
	v2 = D3DXVECTOR3(CENTERX + 10.7, SF, CENTERZ + 3); 
	v3 = D3DXVECTOR3(CENTERX + 10.7, SF, CENTERZ - 2.2);
	m_pSFRoom->Setup(v0, v1, v2, v3, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);


	//2Ãþ ·ë2
	m_pSFRoom2 = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 2.2);
	v1 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ + 3); 
	v2 = D3DXVECTOR3(CENTERX + 7.7, SF, CENTERZ + 3);
	v3 = D3DXVECTOR3(CENTERX + 7.7, SF, CENTERZ - 2.2);
	m_pSFRoom2->Setup(v0, v1, v2, v3, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);

	PassSetup();

}

void cSurface::Render()
{
	//ÁöÇÏ 

	m_pB1StartRoom->Render();
	m_pB1Prison->Render();
	m_pB1StartSpace->Render();
	m_pB1NextRoom->Render();
	for (size_t i = 0; i < 10; i++) {
		m_pB1Stair[i]->Render();
	}

	//1Ãþ 
	m_pFFPassage->Render();
	m_pFFPassage2->Render();
	m_pFFLivingRoom->Render();
	m_pFFLivingRoom2->Render();
	m_pFFRoom->Render();
	m_pFBathRoom->Render();
	for (size_t i = 0; i < 10; i++) {
		m_pB1Stair2[i]->Render();
	}

	//2Ãþ
	m_pSFPassage->Render();
	m_pSFRoom->Render();
	m_pSFRoom2->Render();


	m_pB1Door->Render();
	m_pB1PrisonDoor->Render();
	m_pBathRoomWall->Render();
	m_pBathRoomDoor->Render();
	m_pFFRoomDoor->Render();
	m_pSFRoomDoor1->Render();
	m_pSFRoomDoor2->Render();
}

void cSurface::PassSetup()
{
	//0 °¨¿Á 1 ÁöÇÏ Åë·Î 2 È­Àå½Ç º® 3 È­Àå½Ç ¹®

	PassSurface v, v1, v2, v3;

	m_pB1PrisonDoor = new cRectMake;
	v.nindex = 0;
	v.isOpen = false;
	v.p = D3DXVECTOR3(CENTERX + 5, B1F, CENTERZ + 2);
	v1.p = D3DXVECTOR3(CENTERX + 5, B1F, CENTERZ + 2.1);
	v2.p = D3DXVECTOR3(CENTERX + 6.5, B1F, CENTERZ + 2.1);
	v3.p = D3DXVECTOR3(CENTERX + 6.5, B1F, CENTERZ + 2);
	m_pB1PrisonDoor->Setup(v.p, v1.p, v2.p, v3.p, NULL);

	m_pB1Door = new cRectMake;
	v.nindex = 1;
	v.isOpen = false;
	v.p = D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 3);
	v1.p = D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 3.5);
	v2.p = D3DXVECTOR3(CENTERX + 8.1, B1F, CENTERZ + 3.5);
	v3.p = D3DXVECTOR3(CENTERX + 8.1, B1F, CENTERZ + 3);
	m_pB1Door->Setup(v.p, v1.p, v2.p, v3.p, NULL);
	passVertex.push_back(v);


	m_pBathRoomWall = new cRectMake;
	v.nindex = 2;
	v.isOpen = false;
	v.p = D3DXVECTOR3(CENTERX + 5.2, FF, CENTERZ - 0.5);
	v1.p = D3DXVECTOR3(CENTERX + 5.2, FF, CENTERZ - 0.4);
	v2.p = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 0.4);
	v3.p = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 0.5);
	m_pBathRoomWall->Setup(v.p, v1.p, v2.p, v3.p, NULL);


	m_pBathRoomDoor = new cRectMake;
	v.nindex = 2;
	v.isOpen = false;
	v.p = D3DXVECTOR3(CENTERX + 5.9, FF, CENTERZ - 3);
	v1.p = D3DXVECTOR3(CENTERX + 5.9, FF, CENTERZ - 2.5);
	v2.p = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 2.5);
	v3.p = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 3);
	m_pBathRoomDoor->Setup(v.p, v1.p, v2.p, v3.p, NULL);


	m_pFFRoomDoor = new cRectMake;
	v.nindex = 2;
	v.isOpen = false;
	v.p = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ + 3);
	v1.p = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ + 3.5);
	v2.p = D3DXVECTOR3(CENTERX + 6.1, FF, CENTERZ + 3.5);
	v3.p = D3DXVECTOR3(CENTERX + 6.1, FF, CENTERZ + 3);
	m_pFFRoomDoor->Setup(v.p, v1.p, v2.p, v3.p, NULL);

	m_pSFRoomDoor1 = new cRectMake;
	v.nindex = 2;
	v.isOpen = false;
	v.p = D3DXVECTOR3(CENTERX + 7.7, SF, CENTERZ + 1);
	v1.p = D3DXVECTOR3(CENTERX + 7.7, SF, CENTERZ + 1.5);
	v2.p = D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ + 1.5);
	v3.p = D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ + 1);
	m_pSFRoomDoor1->Setup(v.p, v1.p, v2.p, v3.p, NULL);


	m_pSFRoomDoor2 = new cRectMake;
	v.nindex = 2;
	v.isOpen = false;
	v.p = D3DXVECTOR3(CENTERX + 9, SF, CENTERZ + 1);
	v1.p = D3DXVECTOR3(CENTERX + 9, SF, CENTERZ + 1.5);
	v2.p = D3DXVECTOR3(CENTERX + 9.1, SF, CENTERZ + 1.5);
	v3.p = D3DXVECTOR3(CENTERX + 9.1, SF, CENTERZ + 1);
	m_pSFRoomDoor2->Setup(v.p, v1.p, v2.p, v3.p, NULL);

}

