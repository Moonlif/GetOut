#include "stdafx.h"
#include "cSurface.h"


cSurface::cSurface()
	: m_pTexture(NULL)
	, m_pB1StartRoom(NULL)
	, m_pB1Prison(NULL)
	, m_pB1StartSpace(NULL)
	, m_pB1NextRoom(NULL)
	, m_pB1StairPass(NULL)

	, m_pFFPassage(NULL)
	, m_pFFPassage2(NULL)
	, m_pFFLivingRoom(NULL)
	, m_pFFLivingRoom2(NULL)
	, m_pFFRoom(NULL)
	, m_pFFBathRoom(NULL)
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
	, m_pFFCollision(NULL)

	, m_pB1StairSurface(NULL)
	, m_pFFStairSurface(NULL)
{
	
}


cSurface::~cSurface()
{
	//ÁöÇÏ
	SAFE_DELETE(m_pB1StartRoom);
	SAFE_DELETE(m_pB1Prison);
	SAFE_DELETE(m_pB1StartSpace);
	SAFE_DELETE(m_pB1NextRoom);
	SAFE_DELETE(m_pB1StairSurface);
	SAFE_DELETE(m_pB1StairPass);

	//1Ãþ
	SAFE_DELETE(m_pFFPassage);
	SAFE_DELETE(m_pFFPassage2);
	SAFE_DELETE(m_pFFLivingRoom);
	SAFE_DELETE(m_pFFLivingRoom2);
	SAFE_DELETE(m_pFFRoom);
	SAFE_DELETE(m_pFFBathRoom);
	SAFE_DELETE(m_pFFStairSurface);

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
	SAFE_DELETE(m_pFFCollision);

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
	Surface v0, v1, v2, v3;
	v0.p = D3DXVECTOR3(CENTERX + 3.5, B1F, CENTERZ + 0.5);
	v1.p = D3DXVECTOR3(CENTERX + 3.5, B1F, CENTERZ + 1.5); 
	v2.p = D3DXVECTOR3(CENTERX + 7.5, B1F, CENTERZ + 1.5);
	v3.p = D3DXVECTOR3(CENTERX + 7.5, B1F, CENTERZ + 0.5);
	v0.floor = 0;
	v1.floor = 0;
	v2.floor = 0;
	v3.floor = 0;
	m_pB1StartRoom->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);

	//°¨¿Á
	m_pB1Prison = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 3.5, B1F, CENTERZ + 2.4);
	v1.p = D3DXVECTOR3(CENTERX + 3.5, B1F, CENTERZ + 3.5);
	v2.p = D3DXVECTOR3(CENTERX + 6, B1F, CENTERZ + 3.5);
	v3.p = D3DXVECTOR3(CENTERX + 6, B1F, CENTERZ + 2.4);
	v0.floor = 0;
	v1.floor = 0;
	v2.floor = 0;
	v3.floor = 0;
	m_pB1Prison->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);

	//½ºÅ¸Æ®·ë °ø°£
	m_pB1StartSpace = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 6.5, B1F, CENTERZ + 1.5);
	v1.p = D3DXVECTOR3(CENTERX + 6.5, B1F, CENTERZ + 4);
	v2.p = D3DXVECTOR3(CENTERX + 7.5, B1F, CENTERZ + 4);
	v3.p = D3DXVECTOR3(CENTERX + 7.5, B1F, CENTERZ + 1.5);
	v0.floor = 0;
	v1.floor = 0;
	v2.floor = 0;
	v3.floor = 0;
	m_pB1StartSpace->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);

	//ÁöÇÏ ¹æ
	m_pB1NextRoom = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 8.4, B1F, CENTERZ + 0.5);
	v1.p = D3DXVECTOR3(CENTERX + 8.4, B1F, CENTERZ + 3.5);
	v2.p = D3DXVECTOR3(CENTERX + 11.5, B1F, CENTERZ + 3.5);
	v3.p = D3DXVECTOR3(CENTERX + 11.5, B1F, CENTERZ + 0.5);
	v0.floor = 0;
	v1.floor = 0;
	v2.floor = 0;
	v3.floor = 0;
	m_pB1NextRoom->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);
	
	//°è´Ü °¡´Â±æ
	m_pB1StairPass = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 9.3, B1F, CENTERZ + 0.5);
	v1.p = D3DXVECTOR3(CENTERX + 9.1, B1F, CENTERZ - 0.3);
	v2.p = D3DXVECTOR3(CENTERX + 9.7, B1F, CENTERZ - 0.3);
	v3.p = D3DXVECTOR3(CENTERX + 9.7, B1F, CENTERZ + 0.5);
	v0.floor = 0;
	v1.floor = 0;
	v2.floor = 0;
	v3.floor = 0;
	m_pB1StairPass->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);

	//ÁöÇÏ 1Ãþ °è´Ü
	m_pB1StairSurface = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 9.3, FF, CENTERZ - 3);
	v1.p = D3DXVECTOR3(CENTERX + 9.1, B1F, CENTERZ + 0);
	v2.p = D3DXVECTOR3(CENTERX + 9.7, B1F, CENTERZ + 0);
	v3.p = D3DXVECTOR3(CENTERX + 9.7, FF, CENTERZ - 3);
	v0.floor = 0;
	v1.floor = 0;
	v2.floor = 0;
	v3.floor = 0;
	m_pB1StairSurface->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);
	v0.floor = 1;
	v1.floor = 1;
	v2.floor = 1;
	v3.floor = 1;
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);



	//>>1Ãþ

	//1Ãþ Åë·Î1
	m_pFFPassage = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 6.5, FF, CENTERZ - 3.6);
	v1.p = D3DXVECTOR3(CENTERX + 6.5, FF, CENTERZ - 3);
	v2.p = D3DXVECTOR3(CENTERX + 12.5, FF, CENTERZ - 3);
	v3.p = D3DXVECTOR3(CENTERX + 12.5, FF, CENTERZ - 3.6);
	v0.floor = 1;
	v1.floor = 1;
	v2.floor = 1;
	v3.floor = 1;
	m_pFFPassage->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);

	//1Ãþ Åë·Î2
	m_pFFPassage2 = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 6.3, FF, CENTERZ - 3);
	v1.p = D3DXVECTOR3(CENTERX + 6.3, FF, CENTERZ - 0.8);
	v2.p = D3DXVECTOR3(CENTERX + 7.4, FF, CENTERZ - 0.8);
	v3.p = D3DXVECTOR3(CENTERX + 7.4, FF, CENTERZ - 3);
	v0.floor = 1;
	v1.floor = 1;
	v2.floor = 1;
	v3.floor = 1;
	m_pFFPassage2->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);
	//°Å½Ç
	m_pFFLivingRoom = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 10.1, FF, CENTERZ - 3.5);
	v1.p = D3DXVECTOR3(CENTERX + 10.1, FF, CENTERZ + 3.7);
	v2.p = D3DXVECTOR3(CENTERX + 12.7, FF, CENTERZ + 3.7);
	v3.p = D3DXVECTOR3(CENTERX + 12.7, FF, CENTERZ - 3.5);
	v0.floor = 1;
	v1.floor = 1;
	v2.floor = 1;
	v3.floor = 1;
	m_pFFLivingRoom->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);

	//°Å½Ç 2
	m_pFFLivingRoom2 = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 6.1, FF, CENTERZ - 0.1);
	v1.p = D3DXVECTOR3(CENTERX + 6.1, FF, CENTERZ + 3.7);
	v2.p = D3DXVECTOR3(CENTERX + 10.1, FF, CENTERZ + 3.7);
	v3.p = D3DXVECTOR3(CENTERX + 10.1, FF, CENTERZ - 0.1);
	v0.floor = 1;
	v1.floor = 1;
	v2.floor = 1;
	v3.floor = 1;
	m_pFFLivingRoom2->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);

	//¹æ
	m_pFFRoom = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 4.5, FF, CENTERZ - 0.2);
	v1.p = D3DXVECTOR3(CENTERX + 4.5, FF, CENTERZ + 3.7);
	v2.p = D3DXVECTOR3(CENTERX + 5.7, FF, CENTERZ + 3.7);
	v3.p = D3DXVECTOR3(CENTERX + 5.7, FF, CENTERZ - 0.2);
	v0.floor = 1;
	v1.floor = 1;
	v2.floor = 1;
	v3.floor = 1;
	m_pFFRoom->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);

	m_pFFRoom1 = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 2.25);
	v1.p = D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 4);
	v2.p = D3DXVECTOR3(CENTERX + 3.67, FF, CENTERZ + 4);
	v3.p = D3DXVECTOR3(CENTERX + 3.67, FF, CENTERZ + 2.25);
	v0.floor = 1;
	v1.floor = 1;
	v2.floor = 1;
	v3.floor = 1;
	m_pFFRoom1->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);

	//È­Àå½Ç

	m_pFFBathRoom = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 3.3, FF, CENTERZ - 3.7);
	v1.p = D3DXVECTOR3(CENTERX + 3.3, FF, CENTERZ - 0.7);
	v2.p = D3DXVECTOR3(CENTERX + 5.6, FF, CENTERZ - 0.7);
	v3.p = D3DXVECTOR3(CENTERX + 5.6, FF, CENTERZ - 3.7);
	v0.floor = 1;
	v1.floor = 1;
	v2.floor = 1;
	v3.floor = 1;
	m_pFFBathRoom->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);

	//1Ãþ -> 2Ãþ °è´Ü
	m_pFFStairSurface = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 8.1, FF, CENTERZ - 3);
	v1.p = D3DXVECTOR3(CENTERX + 8.1, SF, CENTERZ - 0.3);
	v2.p = D3DXVECTOR3(CENTERX + 8.7, SF, CENTERZ - 0.3);
	v3.p = D3DXVECTOR3(CENTERX + 8.7, FF, CENTERZ - 3);
	v0.floor = 1;
	v1.floor = 1;
	v2.floor = 1;
	v3.floor = 1;
	m_pFFStairSurface->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);
	v0.floor = 2;
	v1.floor = 2;
	v2.floor = 2;
	v3.floor = 2;
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);
	//2Ãþ
	
	//2Ãþ Åë·Î
	m_pSFPassage = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 8.1, SF, CENTERZ - 0.5);
	v1.p = D3DXVECTOR3(CENTERX + 8.1, SF, CENTERZ + 2.5);
	v2.p = D3DXVECTOR3(CENTERX + 8.7, SF, CENTERZ + 2.6);
	v3.p = D3DXVECTOR3(CENTERX + 8.7, SF, CENTERZ - 0.5);
	v0.floor = 2;
	v1.floor = 2;
	v2.floor = 2;
	v3.floor = 2;
	m_pSFPassage->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);


	//2Ãþ ·ë1
	m_pSFRoom = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 9.4, SF, CENTERZ - 1.9);
	v1.p = D3DXVECTOR3(CENTERX + 9.4, SF, CENTERZ + 3);
	v2.p = D3DXVECTOR3(CENTERX + 10.3, SF, CENTERZ + 3);
	v3.p = D3DXVECTOR3(CENTERX + 10.3, SF, CENTERZ - 1.9);
	v0.floor = 2;
	v1.floor = 2;
	v2.floor = 2;
	v3.floor = 2;
	m_pSFRoom->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	vecVertex.push_back(v0);
	vecVertex.push_back(v1);
	vecVertex.push_back(v2);

	vecVertex.push_back(v0);
	vecVertex.push_back(v2);
	vecVertex.push_back(v3);


	//2Ãþ ·ë2
	m_pSFRoom2 = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 6.3, SF, CENTERZ - 1.9);
	v1.p = D3DXVECTOR3(CENTERX + 6.3, SF, CENTERZ + 2.7);
	v2.p = D3DXVECTOR3(CENTERX + 7.4, SF, CENTERZ + 2.7);
	v3.p = D3DXVECTOR3(CENTERX + 7.4, SF, CENTERZ - 1.9);
	v0.floor = 2;
	v1.floor = 2;
	v2.floor = 2;
	v3.floor = 2;
	m_pSFRoom2->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
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
	m_pB1StairSurface->Render();
	m_pB1StairPass->Render();

	//1Ãþ 
	m_pFFPassage->Render();
	m_pFFPassage2->Render();
	m_pFFLivingRoom->Render();
	m_pFFLivingRoom2->Render();
	m_pFFRoom->Render();
	m_pFFRoom1->Render();
	m_pFFBathRoom->Render();
	m_pFFStairSurface->Render();

	//2Ãþ
	m_pSFPassage->Render();
	m_pSFRoom->Render();
	m_pSFRoom2->Render();


	//Åë·Î
	m_pB1Door->Render();
	m_pB1PrisonDoor->Render();
	m_pBathRoomWall->Render();
	m_pBathRoomDoor->Render();
	m_pFFRoomDoor->Render();
	m_pSFRoomDoor1->Render();
	m_pSFRoomDoor2->Render();
	//¹«³ÊÁø ¹Ù´Ú
	m_pFFCollision->Render();
	m_pWoodWay->Render();

	/*
	if (m_pCheked[0].isOpen == true) 
	if (m_pCheked[1].isOpen == true) 
	if (m_pCheked[2].isOpen == true) 
	if (m_pCheked[3].isOpen == true) 
	if (m_pCheked[4].isOpen == true) 
	if (m_pCheked[5].isOpen == true) 
	if (m_pCheked[6].isOpen == true) 
	
	if (m_pCheked[7].isOpen == true) 
	*/
}

void cSurface::PassSetup()
{
	/*	0 °¨¿Á SWITCH_DOOR_PRISON
		1 ÁöÇÏ Åë·Î 
		2 È­Àå½Ç º® 
		3 È­Àå½Ç ¹® 
		4 1Ãþ¹æ 
		5 2Ãþ¹æ ¿ÞÂÊ 
		6 2Ãþ¹æ ¿À¸¥ÂÊ
		7 1Ãþ ¹«³ÊÁø ¹Ù´Ú Ãß°¡
		8 ³ª¹« Åä¸· Ãß°¡
	*/
	PassSurface v0, v1, v2, v3;
	//°¨¿Á ¹®
	m_pB1PrisonDoor = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 5, B1F, CENTERZ + 0.5);
	v1.p = D3DXVECTOR3(CENTERX + 5, B1F, CENTERZ + 2.4);
	v2.p = D3DXVECTOR3(CENTERX + 6.5, B1F, CENTERZ + 2.4);
	v3.p = D3DXVECTOR3(CENTERX + 6.5, B1F, CENTERZ + 0.5); 
	m_pB1PrisonDoor->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	PassInput(v0, v1, v2, v3, SWITCH_DOOR_PRISON);


	//°¨¿Á -> ÁöÇÏ½Ç º®
	m_pB1Door = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 7.5, B1F, CENTERZ + 3);
	v1.p = D3DXVECTOR3(CENTERX + 7.5, B1F, CENTERZ + 3.5);
	v2.p = D3DXVECTOR3(CENTERX + 8.4, B1F, CENTERZ + 3.5);
	v3.p = D3DXVECTOR3(CENTERX + 8.4, B1F, CENTERZ + 3);
	m_pB1Door->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	PassInput(v0, v1, v2, v3, 1);


	//È­Àå½Ç -> ¹æ º®
	m_pBathRoomWall = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 5.2, FF, CENTERZ - 0.7);
	v1.p = D3DXVECTOR3(CENTERX + 5.2, FF, CENTERZ - 0.2);
	v2.p = D3DXVECTOR3(CENTERX + 5.7, FF, CENTERZ - 0.2);
	v3.p = D3DXVECTOR3(CENTERX + 5.7, FF, CENTERZ - 0.7);
	m_pBathRoomWall->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	PassInput(v0, v1, v2, v3, 2);


	//È­Àå½Ç -> Åë·Î ¹®
	m_pBathRoomDoor = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 5.6, FF, CENTERZ - 3);
	v1.p = D3DXVECTOR3(CENTERX + 5.6, FF, CENTERZ - 2.5);
	v2.p = D3DXVECTOR3(CENTERX + 6.5, FF, CENTERZ - 2.5);
	v3.p = D3DXVECTOR3(CENTERX + 6.5, FF, CENTERZ - 3);
	m_pBathRoomDoor->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	PassInput(v0, v1, v2, v3, SWITCH_DOOR_1STTOILET);

	//1Ãþ¹æ ¹®
	m_pFFRoomDoor = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 5.7, FF, CENTERZ + 3);
	v1.p = D3DXVECTOR3(CENTERX + 5.7, FF, CENTERZ + 3.5);
	v2.p = D3DXVECTOR3(CENTERX + 6.1, FF, CENTERZ + 3.5);
	v3.p = D3DXVECTOR3(CENTERX + 6.1, FF, CENTERZ + 3);
	m_pFFRoomDoor->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	PassInput(v0, v1, v2, v3, SWITCH_DOOR_1STROOM);

	//2Ãþ¹æ ¹®
	m_pSFRoomDoor1 = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 7.4, SF, CENTERZ + 1);
	v1.p = D3DXVECTOR3(CENTERX + 7.4, SF, CENTERZ + 1.5);
	v2.p = D3DXVECTOR3(CENTERX + 8.1, SF, CENTERZ + 1.5);
	v3.p = D3DXVECTOR3(CENTERX + 8.1, SF, CENTERZ + 1);
	m_pSFRoomDoor1->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	PassInput(v0, v1, v2, v3, SWITCH_DOOR_2NDROOM1);

	//2Ãþ¹æ ¹® 2
	m_pSFRoomDoor2 = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 8.7, SF, CENTERZ + 1);
	v1.p = D3DXVECTOR3(CENTERX + 8.7, SF, CENTERZ + 1.5);
	v2.p = D3DXVECTOR3(CENTERX + 9.4, SF, CENTERZ + 1.5);
	v3.p = D3DXVECTOR3(CENTERX + 9.4, SF, CENTERZ + 1);
	m_pSFRoomDoor2->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	PassInput(v0, v1, v2, v3, SWITCH_DOOR_2NDROOM2);

	//¹«³ÊÁø ÃµÀå
	m_pFFCollision = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 2);
	v1.p = D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 4);
	v2.p = D3DXVECTOR3(CENTERX + 4.5, FF, CENTERZ + 4);
	v3.p = D3DXVECTOR3(CENTERX + 4.5, FF, CENTERZ + 2);
	m_pFFCollision->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	PassInput(v0, v1, v2, v3, 7);

	//³ª¹« ÆÇÀÚ
	m_pWoodWay = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 3.1);
	v1.p = D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 3.4);
	v2.p = D3DXVECTOR3(CENTERX + 4.5, FF, CENTERZ + 3.4);
	v3.p = D3DXVECTOR3(CENTERX + 4.5, FF, CENTERZ + 3.1);
	m_pWoodWay->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	PassInput(v0, v1, v2, v3, 8);
}

void cSurface::PassInput(PassSurface v0, PassSurface v1, PassSurface v2, PassSurface v3, int index)
{
	v0.nindex = index;
	v1.nindex = index;
	v2.nindex = index;
	v3.nindex = index;
	//m_pCheked[index].nIndex = index;
	//m_pCheked[index].isOpen = false;


	passVertex.push_back(v0);
	passVertex.push_back(v1);
	passVertex.push_back(v2);

	passVertex.push_back(v0);
	passVertex.push_back(v2);
	passVertex.push_back(v3);
}



