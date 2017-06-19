#include "stdafx.h"
#include "cSurface.h"


cSurface::cSurface()
{

}


cSurface::~cSurface()
{

	for each (auto it in vecSurface)
	{
		SAFE_DELETE(it);
	}
	//SAFE_RELEASE(m_pTexture);
}

void cSurface::Setup()
{
	/*
	��ǥ �簢�� �Է�
	1 2
	0 3
	//012 023
	*/
	//>> ���� 
	//��ŸƮ ��
	m_pB1StartRoom = new cRectMake;
	D3DXVECTOR3 v0, v1, v2, v3;

	v0 = D3DXVECTOR3(CENTERX + 3.5, B1F, CENTERZ + 0.5);
	v1 = D3DXVECTOR3(CENTERX + 3.5, B1F, CENTERZ + 1.5);
	v2 = D3DXVECTOR3(CENTERX + 7.5, B1F, CENTERZ + 1.5);
	v3 = D3DXVECTOR3(CENTERX + 7.5, B1F, CENTERZ + 0.5);
	m_pB1StartRoom->Setup(v0, v1, v2, v3, NULL);
	InsertVector(0, v0, v1, v2, v3, m_pB1StartRoom);

	//����
	m_pB1Prison = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 3.5, B1F, CENTERZ + 2.4);
	v1 = D3DXVECTOR3(CENTERX + 3.5, B1F, CENTERZ + 3.5);
	v2 = D3DXVECTOR3(CENTERX + 6, B1F, CENTERZ + 3.5);
	v3 = D3DXVECTOR3(CENTERX + 6, B1F, CENTERZ + 2.4);
	m_pB1Prison->Setup(v0, v1, v2, v3, NULL);
	InsertVector(0, v0, v1, v2, v3, m_pB1Prison);

	//��ŸƮ�� ����
	m_pB1StartSpace = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 6.5, B1F, CENTERZ + 1.5);
	v1 = D3DXVECTOR3(CENTERX + 6.5, B1F, CENTERZ + 3.5);
	v2 = D3DXVECTOR3(CENTERX + 7.5, B1F, CENTERZ + 3.5);
	v3 = D3DXVECTOR3(CENTERX + 7.5, B1F, CENTERZ + 1.5);
	m_pB1StartSpace->Setup(v0, v1, v2, v3, NULL);
	InsertVector(0, v0, v1, v2, v3, m_pB1StartSpace);

	//���� ��
	m_pB1NextRoom = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 8.4, B1F, CENTERZ + 0.5);
	v1 = D3DXVECTOR3(CENTERX + 8.4, B1F, CENTERZ + 3.5);
	v2 = D3DXVECTOR3(CENTERX + 11.5, B1F, CENTERZ + 3.5);
	v3 = D3DXVECTOR3(CENTERX + 11.5, B1F, CENTERZ + 0.5);
	m_pB1NextRoom->Setup(v0, v1, v2, v3, NULL);
	InsertVector(0, v0, v1, v2, v3, m_pB1NextRoom);

	//��� ���±�
	m_pB1StairPass = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 9.3, B1F, CENTERZ + 0.5);
	v1 = D3DXVECTOR3(CENTERX + 9.1, B1F, CENTERZ - 0.3);
	v2 = D3DXVECTOR3(CENTERX + 9.7, B1F, CENTERZ - 0.3);
	v3 = D3DXVECTOR3(CENTERX + 9.7, B1F, CENTERZ + 0.5);
	m_pB1StairPass->Setup(v0, v1, v2, v3, NULL);
	InsertVector(0, v0, v1, v2, v3, m_pB1StairPass);

	//���� 1�� ���
	m_pB1StairSurface = new cRectMake;
	//>>>>>>17.06.15  
	v0 = D3DXVECTOR3(CENTERX + 9.3, FF, CENTERZ - 3);
	v1 = D3DXVECTOR3(CENTERX + 9.3, B1F, CENTERZ + 0);
	v2 = D3DXVECTOR3(CENTERX + 9.7, B1F, CENTERZ + 0);
	v3 = D3DXVECTOR3(CENTERX + 9.7, FF, CENTERZ - 3);
	//<<<<<<<<<<
	m_pB1StairSurface->Setup(v0, v1, v2, v3, NULL);
	InsertVector(0, v0, v1, v2, v3, m_pB1StairSurface);
	m_pB1StairSurface_1 = new cRectMake;
	m_pB1StairSurface_1->Setup(v0, v1, v2, v3, NULL);
	InsertVector(1, v0, v1, v2, v3, m_pB1StairSurface_1);

	//>>1��

	//1�� ���1
	m_pFFPassage = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 6.5, FF, CENTERZ - 3.6);
	v1 = D3DXVECTOR3(CENTERX + 6.5, FF, CENTERZ - 3);
	v2 = D3DXVECTOR3(CENTERX + 12.5, FF, CENTERZ - 3);
	v3 = D3DXVECTOR3(CENTERX + 12.5, FF, CENTERZ - 3.6);
	m_pFFPassage->Setup(v0, v1, v2, v3, NULL);
	InsertVector(1, v0, v1, v2, v3, m_pFFPassage);

	//1�� ���2
	m_pFFPassage2 = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 6.3, FF, CENTERZ - 3);
	v1 = D3DXVECTOR3(CENTERX + 6.3, FF, CENTERZ - 0.8);
	v2 = D3DXVECTOR3(CENTERX + 7.4, FF, CENTERZ - 0.8);
	v3 = D3DXVECTOR3(CENTERX + 7.4, FF, CENTERZ - 3);
	m_pFFPassage2->Setup(v0, v1, v2, v3, NULL);
	InsertVector(1, v0, v1, v2, v3, m_pFFPassage2);

	//�Ž�
	m_pFFLivingRoom = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 10.1, FF, CENTERZ - 3.5);
	v1 = D3DXVECTOR3(CENTERX + 10.1, FF, CENTERZ + 3.7);
	v2 = D3DXVECTOR3(CENTERX + 12.7, FF, CENTERZ + 3.7);
	v3 = D3DXVECTOR3(CENTERX + 12.7, FF, CENTERZ - 3.5);
	m_pFFLivingRoom->Setup(v0, v1, v2, v3, NULL);
	InsertVector(1, v0, v1, v2, v3, m_pFFLivingRoom);


	//�Ž� 2
	m_pFFLivingRoom2 = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 6.1, FF, CENTERZ - 0.1);
	v1 = D3DXVECTOR3(CENTERX + 6.1, FF, CENTERZ + 3.7);
	v2 = D3DXVECTOR3(CENTERX + 10.1, FF, CENTERZ + 3.7);
	v3 = D3DXVECTOR3(CENTERX + 10.1, FF, CENTERZ - 0.1);

	m_pFFLivingRoom2->Setup(v0, v1, v2, v3, NULL);
	InsertVector(1, v0, v1, v2, v3, m_pFFLivingRoom2);

	//��
	
	m_pFFRoom = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 4.3, FF, CENTERZ - 0.2);
	v1 = D3DXVECTOR3(CENTERX + 4.3, FF, CENTERZ + 3.7);
	v2 = D3DXVECTOR3(CENTERX + 5.7, FF, CENTERZ + 3.7);
	v3 = D3DXVECTOR3(CENTERX + 5.7, FF, CENTERZ - 0.2);
	m_pFFRoom->Setup(v0, v1, v2, v3, NULL);
	InsertVector(1, v0, v1, v2, v3, m_pFFRoom);
	
	
	m_pFFRoom1 = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 2.25);
	v1 = D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 4);
	v2 = D3DXVECTOR3(CENTERX + 3.67, FF, CENTERZ + 4);
	v3 = D3DXVECTOR3(CENTERX + 3.67, FF, CENTERZ + 2.25);
	m_pFFRoom1->Setup(v0, v1, v2, v3, NULL);
	InsertVector(1, v0, v1, v2, v3, m_pFFRoom1);
	
	//ȭ���

	m_pFFBathRoom = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 3.3, FF, CENTERZ - 3.7);
	v1 = D3DXVECTOR3(CENTERX + 3.3, FF, CENTERZ - 0.7);
	v2 = D3DXVECTOR3(CENTERX + 5.6, FF, CENTERZ - 0.7);
	v3 = D3DXVECTOR3(CENTERX + 5.6, FF, CENTERZ - 3.7);
	m_pFFBathRoom->Setup(v0, v1, v2, v3, NULL);
	InsertVector(1, v0, v1, v2, v3, m_pFFBathRoom);

	//1�� -> 2�� ���
	m_pFFStairSurface = new cRectMake;
	//>>> 17.06.15
	v0 = D3DXVECTOR3(CENTERX + 8.1, FF, CENTERZ - 3);
	v1 = D3DXVECTOR3(CENTERX + 8.1, SF, CENTERZ - 0.3);
	v2 = D3DXVECTOR3(CENTERX + 8.7, SF, CENTERZ - 0.3);
	v3 = D3DXVECTOR3(CENTERX + 8.7, FF, CENTERZ - 3);
	//<<<<
	m_pFFStairSurface->Setup(v0, v1, v2, v3, NULL);
	InsertVector(1, v0, v1, v2, v3, m_pFFStairSurface);
	m_pFFStairSurface_2 = new cRectMake;
	m_pFFStairSurface_2->Setup(v0, v1, v2, v3, NULL);
	InsertVector(2, v0, v1, v2, v3, m_pFFStairSurface_2);


	//2��
	//2�� ���
	m_pSFPassage = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 8.1, SF, CENTERZ - 0.5);
	v1 = D3DXVECTOR3(CENTERX + 8.1, SF, CENTERZ + 2.5);
	v2 = D3DXVECTOR3(CENTERX + 8.7, SF, CENTERZ + 2.6);
	v3 = D3DXVECTOR3(CENTERX + 8.7, SF, CENTERZ - 0.5);
	m_pSFPassage->Setup(v0, v1, v2, v3, NULL);
	InsertVector(2, v0, v1, v2, v3, m_pSFPassage);

	//2�� ��1
	m_pSFRoom = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 9.4, SF, CENTERZ - 1.9);
	v1 = D3DXVECTOR3(CENTERX + 9.4, SF, CENTERZ + 3);
	v2 = D3DXVECTOR3(CENTERX + 10.3, SF, CENTERZ + 3);
	v3 = D3DXVECTOR3(CENTERX + 10.3, SF, CENTERZ - 1.9);
	m_pSFRoom->Setup(v0, v1, v2, v3, NULL);
	InsertVector(2, v0, v1, v2, v3, m_pSFRoom);


	//2�� ��2
	m_pSFRoom2 = new cRectMake;
	v0 = D3DXVECTOR3(CENTERX + 6.3, SF, CENTERZ - 1.9);
	v1 = D3DXVECTOR3(CENTERX + 6.3, SF, CENTERZ + 2.7);
	v2 = D3DXVECTOR3(CENTERX + 7.4, SF, CENTERZ + 2.7);
	v3 = D3DXVECTOR3(CENTERX + 7.4, SF, CENTERZ - 1.9);
	m_pSFRoom2->Setup(v0, v1, v2, v3, NULL);
	InsertVector(2, v0, v1, v2, v3, m_pSFRoom2);
	PassSetup();
}

void cSurface::Render()
{
	for each (auto it in vecSurface)
	{
		it->Render();
	}
}

void cSurface::PassSetup()
{
	/*
	0 ���� SWITCH_DOOR_PRISON
	1 ���� ���
	2 ȭ��� ��
	3 ȭ��� ��
	4 1����
	5 2���� ����
	6 2���� ������
	7 1�� ������ �ٴ� �߰�
	8 ���� �丷 �߰�
	*/
	PassSurface v0, v1, v2, v3;
	//���� ��
	m_pB1PrisonDoor = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 5, B1F, CENTERZ + 0.5);
	v1.p = D3DXVECTOR3(CENTERX + 5, B1F, CENTERZ + 2.4);
	v2.p = D3DXVECTOR3(CENTERX + 6.5, B1F, CENTERZ + 2.4);
	v3.p = D3DXVECTOR3(CENTERX + 6.5, B1F, CENTERZ + 0.5);
	m_pB1PrisonDoor->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	PassInput(v0, v1, v2, v3, SWITCH_DOOR_PRISON, m_pB1PrisonDoor);


	//���� -> ���Ͻ� ��
	m_pB1Door = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 7.5, B1F, CENTERZ + 3);
	v1.p = D3DXVECTOR3(CENTERX + 7.5, B1F, CENTERZ + 3.5);
	v2.p = D3DXVECTOR3(CENTERX + 8.4, B1F, CENTERZ + 3.5);
	v3.p = D3DXVECTOR3(CENTERX + 8.4, B1F, CENTERZ + 3);
	m_pB1Door->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	PassInput(v0, v1, v2, v3, SWITCH_BASEMENT_BOX1, m_pB1Door);


	//ȭ��� -> �� ��
	m_pBathRoomWall = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 5.2, FF, CENTERZ - 0.7);
	v1.p = D3DXVECTOR3(CENTERX + 5.2, FF, CENTERZ - 0.2);
	v2.p = D3DXVECTOR3(CENTERX + 5.7, FF, CENTERZ - 0.2);
	v3.p = D3DXVECTOR3(CENTERX + 5.7, FF, CENTERZ - 0.7);
	m_pBathRoomWall->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	PassInput(v0, v1, v2, v3, SWITCH_FIRSTFLOOR_BLOCK, m_pBathRoomWall);


	//ȭ��� -> ��� ��
	m_pBathRoomDoor = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 5.6, FF, CENTERZ - 3);
	v1.p = D3DXVECTOR3(CENTERX + 5.6, FF, CENTERZ - 2.5);
	v2.p = D3DXVECTOR3(CENTERX + 6.5, FF, CENTERZ - 2.5);
	v3.p = D3DXVECTOR3(CENTERX + 6.5, FF, CENTERZ - 3);
	m_pBathRoomDoor->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	PassInput(v0, v1, v2, v3, SWITCH_DOOR_1STTOILET, m_pBathRoomDoor);

	//1���� ��
	m_pFFRoomDoor = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 5.7, FF, CENTERZ + 3);
	v1.p = D3DXVECTOR3(CENTERX + 5.7, FF, CENTERZ + 3.5);
	v2.p = D3DXVECTOR3(CENTERX + 6.1, FF, CENTERZ + 3.5);
	v3.p = D3DXVECTOR3(CENTERX + 6.1, FF, CENTERZ + 3);
	m_pFFRoomDoor->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	PassInput(v0, v1, v2, v3, SWITCH_DOOR_1STROOM, m_pFFRoomDoor);

	//2���� ��
	m_pSFRoomDoor1 = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 7.4, SF, CENTERZ + 1);
	v1.p = D3DXVECTOR3(CENTERX + 7.4, SF, CENTERZ + 1.5);
	v2.p = D3DXVECTOR3(CENTERX + 8.1, SF, CENTERZ + 1.5);
	v3.p = D3DXVECTOR3(CENTERX + 8.1, SF, CENTERZ + 1);
	m_pSFRoomDoor1->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	PassInput(v0, v1, v2, v3, SWITCH_DOOR_2NDROOM1, m_pSFRoomDoor1);

	//2���� �� 2
	m_pSFRoomDoor2 = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 8.7, SF, CENTERZ + 1);
	v1.p = D3DXVECTOR3(CENTERX + 8.7, SF, CENTERZ + 1.5);
	v2.p = D3DXVECTOR3(CENTERX + 9.4, SF, CENTERZ + 1.5);
	v3.p = D3DXVECTOR3(CENTERX + 9.4, SF, CENTERZ + 1);
	m_pSFRoomDoor2->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	PassInput(v0, v1, v2, v3, SWITCH_DOOR_2NDROOM2, m_pSFRoomDoor2);

	//���� ����
	m_pWoodWay = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 3.1);
	v1.p = D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 3.4);
	v2.p = D3DXVECTOR3(CENTERX + 4.3, FF, CENTERZ + 3.4);
	v3.p = D3DXVECTOR3(CENTERX + 4.3, FF, CENTERZ + 3.1);
	m_pWoodWay->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	PassInput(v0, v1, v2, v3, SWITCH_FIRSTFLOOR_WOODBOARD1, m_pWoodWay);

	//������ õ��
	
	m_pFFCollision = new cRectMake;
	v0.p = D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 1);
	v1.p = D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 4);
	v2.p = D3DXVECTOR3(CENTERX + 4.3, FF, CENTERZ + 4);
	v3.p = D3DXVECTOR3(CENTERX + 4.3, FF, CENTERZ + 1);
	m_pFFCollision->Setup(v0.p, v1.p, v2.p, v3.p, NULL);
	PassInput(v0, v1, v2, v3, SWITCH_FIRSTFLOOR_TRAP, m_pFFCollision);

	
}

void cSurface::InsertVector(int floor, D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, cRectMake* rec)
{
	Surface sf0, sf1, sf2, sf3;
	sf0.p = v0;
	sf1.p = v1;
	sf2.p = v2;
	sf3.p = v3;

	sf0.floor = floor;
	sf1.floor = floor;
	sf2.floor = floor;
	sf3.floor = floor;

	vecVertex.push_back(sf0);
	vecVertex.push_back(sf1);
	vecVertex.push_back(sf2);

	vecVertex.push_back(sf0);
	vecVertex.push_back(sf2);
	vecVertex.push_back(sf3);

	vecSurface.push_back(rec);
}

void cSurface::PassInput(PassSurface v0, PassSurface v1, PassSurface v2, PassSurface v3, int index, cRectMake* rec)
{
	v0.nindex = index;
	v1.nindex = index;
	v2.nindex = index;
	v3.nindex = index;


	passVertex.push_back(v0);
	passVertex.push_back(v1);
	passVertex.push_back(v2);
	passVertex.push_back(v0);
	passVertex.push_back(v2);
	passVertex.push_back(v3);

	vecSurface.push_back(rec);
}



