#include "stdafx.h"
#include "cFloor.h"


cFloor::cFloor()
	: m_pTexture(NULL)
	, m_pB1StartRoom(NULL)
	, m_pB1Prison(NULL)
	, m_pB1StartSpace(NULL)
	, m_pB1NextRoom(NULL)
	, m_pFFPassage(NULL)
	, m_pFFPassage2(NULL)
	, m_pFFLivingRoom(NULL)
	, m_pFFRoom(NULL)
	, m_pFBathRoom(NULL)
	, m_pSFPassage(NULL)
	, m_pSFRoom(NULL)
	, m_pSFRoom2(NULL)

{
}


cFloor::~cFloor()
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
	SAFE_DELETE(m_pFFRoom);
	SAFE_DELETE(m_pFBathRoom);
	for (size_t i = 0; i < 10; i++) {
		SAFE_DELETE(m_pB1Stair2[i]);
	}
	//2Ãþ
	SAFE_DELETE(m_pSFPassage);
	SAFE_DELETE(m_pSFRoom);
	SAFE_DELETE(m_pSFRoom2);


	SAFE_RELEASE(m_pTexture);
}

void cFloor::Setup()
{
	/*
	ÁÂÇ¥ »ç°¢Çü ÀÔ·Â
	1 2
	0 3
	*/
	//>> ÁöÇÏ 
	//½ºÅ¸Æ® ·ë
	m_pB1StartRoom = new cRectMake;
	D3DXVECTOR3 v0, v1, v2, v3;
	v0 = D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ); vecVertex.push_back(v0);
	v1 = D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ + 2); vecVertex.push_back(v1);
	v2 = D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 2); vecVertex.push_back(v2);
	v3 = D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ); vecVertex.push_back(v3);
	m_pB1StartRoom->Setup(v0, v1, v2, v3, NULL);
	//°¨¿Á
	m_pB1Prison = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ + 2.1); vecVertex.push_back(v0);
	v1 = D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ + 4); vecVertex.push_back(v1);
	v2 = D3DXVECTOR3(CENTERX + 6.4, B1F, CENTERZ + 4); vecVertex.push_back(v2);
	v3 = D3DXVECTOR3(CENTERX + 6.4, B1F, CENTERZ + 2.1); vecVertex.push_back(v3);
	m_pB1Prison->Setup(v0, v1, v2, v3, "texture/maps/cs_office_texture_142.jpg");
	//½ºÅ¸Æ®·ë °ø°£
	m_pB1StartSpace = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 6.5, B1F, CENTERZ + 2); vecVertex.push_back(v0);
	v1 = D3DXVECTOR3(CENTERX + 6.5, B1F, CENTERZ + 4); vecVertex.push_back(v1);
	v2 = D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 4); vecVertex.push_back(v2);
	v3 = D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 2); vecVertex.push_back(v3);
	m_pB1StartSpace->Setup(v0, v1, v2, v3, NULL);
	//ÁöÇÏ ¹æ
	m_pB1NextRoom = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 8.1, B1F, CENTERZ); vecVertex.push_back(v0);
	v1 = D3DXVECTOR3(CENTERX + 8.1, B1F, CENTERZ + 4); vecVertex.push_back(v1);
	v2 = D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 4); vecVertex.push_back(v2);
	v3 = D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ); vecVertex.push_back(v3);
	m_pB1NextRoom->Setup(v0, v1, v2, v3, NULL);
	//ÁöÇÏ -> 1Ãþ °è´Ü
	for (size_t i = 0; i < 10; i++) {
		m_pB1Stair[i] = new cRectMake;
		v0 = D3DXVECTOR3(CENTERX + 9, (FF - B1F) * 0.1 * i, CENTERZ - 0.5 + (-0.3 * i)); vecVertex.push_back(v0);
		v1 = D3DXVECTOR3(CENTERX + 9, (FF - B1F) * 0.1 * i, CENTERZ + (-0.3 * i)); vecVertex.push_back(v1);
		v2 = D3DXVECTOR3(CENTERX + 10, (FF - B1F) * 0.1 * i, CENTERZ + (-0.3 * i)); vecVertex.push_back(v2);
		v3 = D3DXVECTOR3(CENTERX + 10, (FF - B1F) * 0.1 * i, CENTERZ - 0.5 + (-0.3 * i)); vecVertex.push_back(v3);
		m_pB1Stair[i]->Setup(v0, v1, v2, v3, NULL);
	}

	//m_pRoomRect->Setup(D3DXVECTOR3(5, 0, 0), D3DXVECTOR3(5, 0, 3), D3DXVECTOR3(15, 0, 3), D3DXVECTOR3(15, 0, 0));

	//>>1Ãþ

	//1Ãþ Åë·Î1
	m_pFFPassage = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 4); vecVertex.push_back(v0);
	v1 = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 3); vecVertex.push_back(v1);
	v2 = D3DXVECTOR3(CENTERX + 13, FF, CENTERZ - 3); vecVertex.push_back(v2);
	v3 = D3DXVECTOR3(CENTERX + 13, FF, CENTERZ - 4); vecVertex.push_back(v3);
	m_pFFPassage->Setup(v0, v1, v2, v3, NULL);
	//1Ãþ Åë·Î2
	m_pFFPassage2 = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 3); vecVertex.push_back(v0);
	v1 = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 0.5); vecVertex.push_back(v1);
	v2 = D3DXVECTOR3(CENTERX + 7.8, FF, CENTERZ - 0.5); vecVertex.push_back(v2);
	v3 = D3DXVECTOR3(CENTERX + 7.8, FF, CENTERZ - 3); vecVertex.push_back(v3);
	m_pFFPassage2->Setup(v0, v1, v2, v3, NULL);
	//°Å½Ç
	m_pFFLivingRoom = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 10.1, FF, CENTERZ - 3); vecVertex.push_back(v0);
	v1 = D3DXVECTOR3(CENTERX + 10.1, FF, CENTERZ + 2); vecVertex.push_back(v1);
	v2 = D3DXVECTOR3(CENTERX + 13, FF, CENTERZ + 2); vecVertex.push_back(v2);
	v3 = D3DXVECTOR3(CENTERX + 13, FF, CENTERZ - 3); vecVertex.push_back(v3);
	m_pFFLivingRoom->Setup(v0, v1, v2, v3, NULL);
	//¹æ
	m_pFFRoom = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 5, FF, CENTERZ - 0.4); vecVertex.push_back(v0);
	v1 = D3DXVECTOR3(CENTERX + 5, FF, CENTERZ + 2); vecVertex.push_back(v1);
	v2 = D3DXVECTOR3(CENTERX + 10, FF, CENTERZ + 2); vecVertex.push_back(v2);
	v3 = D3DXVECTOR3(CENTERX + 10, FF, CENTERZ - 0.4); vecVertex.push_back(v3);
	m_pFFRoom->Setup(v0, v1, v2, v3, NULL);
	//È­Àå½Ç
	m_pFBathRoom = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 5, FF, CENTERZ - 4); vecVertex.push_back(v0);
	v1 = D3DXVECTOR3(CENTERX + 5, FF, CENTERZ - 0.5); vecVertex.push_back(v1);
	v2 = D3DXVECTOR3(CENTERX + 5.9, FF, CENTERZ - 0.5); vecVertex.push_back(v2);
	v3 = D3DXVECTOR3(CENTERX + 5.9, FF, CENTERZ - 4); vecVertex.push_back(v3);
	m_pFBathRoom->Setup(v0, v1, v2, v3, NULL);
	//1Ãþ -> 2Ãþ °è´Ü
	for (size_t i = 0; i < 10; i++) {
		m_pB1Stair2[i] = new cRectMake;
		v0 = D3DXVECTOR3(CENTERX + 7.9, ((SF - FF) * 0.1 * i) + FF, CENTERZ - 3 + (0.3 * i)); vecVertex.push_back(v0);
		v1 = D3DXVECTOR3(CENTERX + 7.9, ((SF - FF) * 0.1 * i) + FF, CENTERZ - 2.5 + (0.3 * i)); vecVertex.push_back(v1);
		v2 = D3DXVECTOR3(CENTERX + 8.9, ((SF - FF) * 0.1 * i) + FF, CENTERZ - 2.5 + (0.3 * i)); vecVertex.push_back(v2);
		v3 = D3DXVECTOR3(CENTERX + 8.9, ((SF - FF) * 0.1 * i) + FF, CENTERZ - 3 + (0.3 * i)); vecVertex.push_back(v3);
		m_pB1Stair2[i]->Setup(v0, v1, v2, v3, NULL);
	}

	//2Ãþ
	//2Ãþ Åë·Î
	m_pSFPassage = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ + 0.3); vecVertex.push_back(v0);
	v1 = D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ + 3); vecVertex.push_back(v1);
	v2 = D3DXVECTOR3(CENTERX + 9, SF, CENTERZ + 3); vecVertex.push_back(v2);
	v3 = D3DXVECTOR3(CENTERX + 9, SF, CENTERZ + 0.3); vecVertex.push_back(v3);
	m_pSFPassage->Setup(v0, v1, v2, v3, NULL);
	//2Ãþ ·ë1
	m_pSFRoom = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 9.1, SF, CENTERZ - 2.2); vecVertex.push_back(v0);
	v1 = D3DXVECTOR3(CENTERX + 9.1, SF, CENTERZ + 3); vecVertex.push_back(v1);
	v2 = D3DXVECTOR3(CENTERX + 10.7, SF, CENTERZ + 3); vecVertex.push_back(v2);
	v3 = D3DXVECTOR3(CENTERX + 10.7, SF, CENTERZ - 2.2); vecVertex.push_back(v3);
	m_pSFRoom->Setup(v0, v1, v2, v3, NULL);
	//2Ãþ ·ë2
	m_pSFRoom2 = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 2.2); vecVertex.push_back(v0);
	v1 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ + 3); vecVertex.push_back(v1);
	v2 = D3DXVECTOR3(CENTERX + 7.7, SF, CENTERZ + 3); vecVertex.push_back(v2);
	v3 = D3DXVECTOR3(CENTERX + 7.7, SF, CENTERZ - 2.2); vecVertex.push_back(v3);
	m_pSFRoom2->Setup(v0, v1, v2, v3, NULL);
}

void cFloor::Render()
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
	m_pFFRoom->Render();
	m_pFBathRoom->Render();
	for (size_t i = 0; i < 10; i++) {
		m_pB1Stair2[i]->Render();
	}

	//2Ãþ
	m_pSFPassage->Render();
	m_pSFRoom->Render();
	m_pSFRoom2->Render();
}
