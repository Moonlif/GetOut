#include "stdafx.h"
#include "cWall.h"


cWall::cWall()
{

}
cWall::~cWall()
{
	//����
	
	for each (auto it in m_vecB1F)
	{
		SAFE_DELETE(it);
	}

	//1��
	for each (auto it in m_vecFF)
	{
		SAFE_DELETE(it);
	}

	//2��
	for each (auto it in m_vecSF)
	{
		SAFE_DELETE(it);
	}

}

void cWall::Setup()
{
	// ����
	SetupB1F();
	// 1��
	SetupFF();
	//2��
	SetupSF();
}

void cWall::Render()
{
	//���� 1��
	RenderB1F();
	RenderFF();
	RenderSF();
}

void cWall::SetupB1F()
{
	/************************************
		���� 1�� ��ü
	*************************************/
	//��Ÿ�� �� ����
	m_pB1Up = new cRectMake;
	m_pB1Up->Setup(D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 4)
		, "Texture/maps/castlebase_ceiling03.dds");
	m_vecB1F.push_back(m_pB1Up);

	//2��° �� ����
	m_pB1Up_1 = new cRectMake;
	m_pB1Up_1->Setup(D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 12, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 4)
		, "Texture/maps/castlebase_ceiling03.dds");
	m_vecB1F.push_back(m_pB1Up_1);

	//��Ÿ�� �� ����	
	m_pB1Left = new cRectMake;
	m_pB1Left->Setup(D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ + 4)
		, "Texture/maps/castlebase_ceiling03.dds");
	m_vecB1F.push_back(m_pB1Left);


	//2��°�� ������
	m_pB1Right = new cRectMake;
	m_pB1Right->Setup(D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 12, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 12, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 0)
		, "Texture/maps/castlebase_ceiling03.dds");
	m_vecB1F.push_back(m_pB1Right);
	//��Ÿ�ù� �Ʒ���
	m_pB1Down = new cRectMake;
	m_pB1Down->Setup(D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ + 0)
		, "Texture/maps/castlebase_ceiling03.dds");
	m_vecB1F.push_back(m_pB1Down);

	//2��°�� ù��° �Ʒ� 
	m_pB1Down_1 = new cRectMake;
	m_pB1Down_1->Setup(D3DXVECTOR3(CENTERX + 9, B1F, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 9, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 0)
		, "Texture/maps/castlebase_ceiling03.dds");
	m_vecB1F.push_back(m_pB1Down_1);

	//2��°�� �ι�° �Ʒ�
	m_pB1Down_2 = new cRectMake;
	m_pB1Down_2->Setup(D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 12, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 10, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 10, B1F, CENTERZ + 0)
		, "Texture/maps/castlebase_ceiling03.dds");
	m_vecB1F.push_back(m_pB1Down_2);

	//��� ù��° ��
	m_pB1Stairs = new cRectMake;
	m_pB1Stairs->Setup(D3DXVECTOR3(CENTERX + 9, B1F, CENTERZ - 3)
		, D3DXVECTOR3(CENTERX + 9, FF, CENTERZ - 3)
		, D3DXVECTOR3(CENTERX + 9, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 9, B1F, CENTERZ + 0)
		, "Texture/maps/castlebase_ceiling03.dds");
	m_vecB1F.push_back(m_pB1Stairs);

	//��� �ι�° ��
	m_pB1Stairs_1 = new cRectMake;
	m_pB1Stairs_1->Setup(D3DXVECTOR3(CENTERX + 10, B1F, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 10, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 10, FF, CENTERZ - 3)
		, D3DXVECTOR3(CENTERX + 10, B1F, CENTERZ - 3)
		, "Texture/maps/castlebase_ceiling03.dds");
	m_vecB1F.push_back(m_pB1Stairs_1);



	/************************************
		���� 1�� ���̺� 
	*************************************/
	//��Ÿ�� ��1 ��1
	D3DXVECTOR3 v, v1, v2, v3;
	v = D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 4);
	v1 = D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 4);
	v2 = D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 3.5);
	v3 = D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 3.5);
	m_pB1RoomRight1 = new cRectMake;
	m_pB1RoomRight1->Setup(v, v1, v2, v3, "Texture/maps/castlebase_ceiling03.dds");
	m_vecB1F.push_back(m_pB1RoomRight1);

	m_pB1RoomRight1_1 = new cRectMake;
	m_pB1RoomRight1_1->Setup(v3, v2, v1, v, "Texture/maps/castlebase_ceiling03.dds");
	m_vecB1F.push_back(m_pB1RoomRight1_1);

	//��Ÿ�� ��1 ��2
	v = D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 3);
	v1 = D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 3);
	v2 = D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 0);
	v3 = D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 0);
	m_pB1RoomRight2 = new cRectMake;
	m_pB1RoomRight2->Setup(v, v1, v2, v3, "Texture/maps/castlebase_ceiling03.dds");
	m_vecB1F.push_back(m_pB1RoomRight2);

	m_pB1RoomRight2_1 = new cRectMake;
	m_pB1RoomRight2_1->Setup(v3, v2, v1, v, "Texture/maps/castlebase_ceiling03.dds");
	m_vecB1F.push_back(m_pB1RoomRight2_1);

	//��Ÿ�� ��1 ��3
	v3 = D3DXVECTOR3(CENTERX + 8, 1.5, CENTERZ + 3);
	v2 = D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 3);
	v1 = D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 3.5);
	v = D3DXVECTOR3(CENTERX + 8, 1.5, CENTERZ + 3.5);
	m_pB1RoomRight3 = new cRectMake;
	m_pB1RoomRight3->Setup(v, v1, v2, v3, "Texture/maps/castlebase_ceiling03.dds");
	m_vecB1F.push_back(m_pB1RoomRight3);

	m_pB1RoomRight3_1 = new cRectMake;
	m_pB1RoomRight3_1->Setup(v3, v2, v1, v, "Texture/maps/castlebase_ceiling03.dds");
	m_vecB1F.push_back(m_pB1RoomRight3_1);

}

void cWall::SetupFF()
{
	/*******************************
		1�� ��ü
	********************************/
	
	{
		//�Ž� ����
		m_pFFUp_1 = new cRectMake;
		m_pFFUp_1->Setup(D3DXVECTOR3(CENTERX + 6.1, FF, CENTERZ + 4)
			, D3DXVECTOR3(CENTERX + 6.1, SF, CENTERZ + 4)
			, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ + 4)
			, D3DXVECTOR3(CENTERX + 13, FF, CENTERZ + 4)
			, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFUp_1);
	
		//��� �Ʒ�
		m_pFFDown = new cRectMake;
		m_pFFDown->Setup(D3DXVECTOR3(CENTERX + 13, FF, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 4)
			, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFDown);


		//������ ��1
		m_pFFDoorR1 = new cRectMake;
		m_pFFDoorR1->Setup(D3DXVECTOR3(CENTERX + 13, FF, CENTERZ - 3.5)
			, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ - 3.5)
			, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 13, FF, CENTERZ - 4)
			, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFDoorR1);
		
		//������ ��2
		m_pFFDoorR2 = new cRectMake;
		m_pFFDoorR2->Setup(D3DXVECTOR3(CENTERX + 13, FF, CENTERZ + 4)
			, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ + 4)
			, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ - 2.5)
			, D3DXVECTOR3(CENTERX + 13, FF, CENTERZ - 2.5)
			, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFDoorR2);
	
		//������ ��3
		m_pFFDoorR3 = new cRectMake;
		m_pFFDoorR3->Setup(D3DXVECTOR3(CENTERX + 13, SF - 0.3, CENTERZ - 2.5)
			, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ - 2.5)
			, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ - 3.5)
			, D3DXVECTOR3(CENTERX + 13, SF - 0.3, CENTERZ - 3.5)
			, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFDoorR3);
			
	}
	/**********************************
		ȭ���
	**********************************/
	D3DXVECTOR3 v, v1, v2, v3;
	{
		//ȭ��� ���� ��
		m_pFFLeft_1 = new cRectMake;
		m_pFFLeft_1->Setup(D3DXVECTOR3(CENTERX + 3, FF, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 3, SF, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 3, SF, CENTERZ - 0.4)
			, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ - 0.4)
			, "Texture/maps/bathRoom.jpg");
		m_vecFF.push_back(m_pFFLeft_1);

		//ȭ��� �Ʒ�
		m_pFFDown_1 = new cRectMake;
		m_pFFDown_1->Setup(D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 3, SF, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ - 4)
			, "Texture/maps/bathRoom.jpg");
		m_vecFF.push_back(m_pFFDown_1);

		m_pFFBathRoomPrint = new cRectMake;
		m_pFFBathRoomPrint->Setup(D3DXVECTOR3(CENTERX + 5, FF + 0.5, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 5, SF - 0.5, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 4, SF - 0.3, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 4, FF + 0.7, CENTERZ - 4)
			, "Texture/maps/maze_writing05.dds");
		m_vecFF.push_back(m_pFFBathRoomPrint);

		//������ 1
		v = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 4);
		v1 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 4);
		v2 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 3.5);
		v3 = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 3.5);

		m_pFFBathRoomR1 = new cRectMake;
		m_pFFBathRoomR1->Setup(v3, v2, v1, v, "Texture/maps/bathRoom.jpg"); 
		m_vecFF.push_back(m_pFFBathRoomR1);

		m_pFFBathRoomR1_1 = new cRectMake;
		m_pFFBathRoomR1_1->Setup(v, v1, v2, v3, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFBathRoomR1_1);

		
		//������ 2
		v = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 0.5);
		v1 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 0.5);
		v2 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 2.63);
		v3 = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 2.63);
		
		m_pFFBathRoomR2 = new cRectMake;
		m_pFFBathRoomR2->Setup(v, v1, v2, v3, "Texture/maps/bathRoom.jpg");
		m_vecFF.push_back(m_pFFBathRoomR2);

		m_pFFBathRoomR2_1 = new cRectMake;
		m_pFFBathRoomR2_1->Setup(v3, v2, v1, v, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFBathRoomR2_1);


		//������ 3
		v = D3DXVECTOR3(CENTERX + 6, SF - 0.62, CENTERZ - 3.5);
		v1 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 3.5);
		v2 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 2.5);
		v3 = D3DXVECTOR3(CENTERX + 6, SF - 0.62, CENTERZ - 2.5);
		
		m_pFFBathRoomR3 = new cRectMake;
		m_pFFBathRoomR3->Setup(v3, v2, v1, v, "Texture/maps/bathRoom.jpg"); 
		m_vecFF.push_back(m_pFFBathRoomR3);

		m_pFFBathRoomR3_1 = new cRectMake;
		m_pFFBathRoomR3_1->Setup(v, v1, v2, v3, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFBathRoomR3_1);


		//���� 1
		v = D3DXVECTOR3(CENTERX + 3, FF, CENTERZ - 0.5);
		v1 = D3DXVECTOR3(CENTERX + 3, SF, CENTERZ - 0.5);
		v2 = D3DXVECTOR3(CENTERX + 5.2, SF, CENTERZ - 0.5);
		v3 = D3DXVECTOR3(CENTERX + 5.2, FF, CENTERZ - 0.5);
		m_pFFBathRoomU1 = new cRectMake;
		m_pFFBathRoomU1->Setup(v, v1, v2, v3, "Texture/maps/bathRoom.jpg");
		m_vecFF.push_back(m_pFFBathRoomU1);

		m_pFFBathRoomU1_1 = new cRectMake;
		m_pFFBathRoomU1_1->Setup(v3, v2, v1, v, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFBathRoomU1_1);

		//���� 2
		v = D3DXVECTOR3(CENTERX + 5.2, SF - 0.7, CENTERZ - 0.5);
		v1 = D3DXVECTOR3(CENTERX + 5.2, SF, CENTERZ - 0.5);
		v2 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 0.5);
		v3 = D3DXVECTOR3(CENTERX + 6, SF - 0.7, CENTERZ - 0.5);
		m_pFFBathRoomU2 = new cRectMake;
		m_pFFBathRoomU2->Setup(v, v1, v2, v3, "Texture/maps/bathRoom.jpg");
		m_vecFF.push_back(m_pFFBathRoomU2);

		m_pFFBathRoomU2_1 = new cRectMake;
		m_pFFBathRoomU2_1->Setup(v3, v2, v1, v, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFBathRoomU2_1);

	}
	/**********************************
		��
	**********************************/
	{
		//�� ����
		m_pFFUp = new cRectMake;
		m_pFFUp->Setup(D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 4)
			, D3DXVECTOR3(CENTERX + 3, SF, CENTERZ + 4)
			, D3DXVECTOR3(CENTERX + 6.1, SF, CENTERZ + 4)
			, D3DXVECTOR3(CENTERX + 6.1, FF, CENTERZ + 4)
			, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFUp);

		m_pFFRoomPrint1 = new cRectMake;
		m_pFFRoomPrint1->Setup(D3DXVECTOR3(CENTERX + 3.5, FF, CENTERZ + 4)
			, D3DXVECTOR3(CENTERX + 3.5, SF, CENTERZ + 4)
			, D3DXVECTOR3(CENTERX + 4.2, SF, CENTERZ + 4)
			, D3DXVECTOR3(CENTERX + 4.2, FF, CENTERZ + 4)
			, "Texture/maps/sketch_torture_device_saw.dds");
		m_vecFF.push_back(m_pFFRoomPrint1);

		m_pFFRoomPrint2 = new cRectMake;
		m_pFFRoomPrint2->Setup(D3DXVECTOR3(CENTERX + 4.3, FF, CENTERZ + 4)
			, D3DXVECTOR3(CENTERX + 4.3, SF, CENTERZ + 4)
			, D3DXVECTOR3(CENTERX + 5, SF, CENTERZ + 4)
			, D3DXVECTOR3(CENTERX + 5, FF, CENTERZ + 4)
			, "Texture/maps/sketch_torture_device_strappado.dds");
		m_vecFF.push_back(m_pFFRoomPrint2);

		//�� ���� ��
		m_pFFLeft = new cRectMake;
		m_pFFLeft->Setup(D3DXVECTOR3(CENTERX + 3, FF, CENTERZ - 0.4)
			, D3DXVECTOR3(CENTERX + 3, SF, CENTERZ - 0.4)
			, D3DXVECTOR3(CENTERX + 3, SF, CENTERZ + 4)
			, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 4)
			, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFLeft);

		//�� ������1
		v = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ + 4);
		v1 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ + 4);
		v2 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ + 3.65);
		v3 = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ + 3.65);
		m_pFFRoomR1 = new cRectMake;
		m_pFFRoomR1->Setup(v, v1, v2, v3, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFRoomR1);

		m_pFFRoomR1_1 = new cRectMake;
		m_pFFRoomR1_1->Setup(v3, v2, v1, v, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFRoomR1_1);

		//�� ������2
		v = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ + 2.8);
		v1 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ + 2.8);
		v2 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 0.5);
		v3 = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 0.5);
		m_pFFRoomR2 = new cRectMake;
		m_pFFRoomR2->Setup(v, v1, v2, v3, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFRoomR2);

		m_pFFRoomR2_1 = new cRectMake;
		m_pFFRoomR2_1->Setup(v3, v2, v1, v, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFRoomR2_1);
	
		//�� ������3
		v = D3DXVECTOR3(CENTERX + 6, SF - 0.67, CENTERZ + 3.65);
		v1 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ + 3.65);
		v2 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ + 2.8);
		v3 = D3DXVECTOR3(CENTERX + 6, SF - 0.67, CENTERZ + 2.8);
		m_pFFRoomR3 = new cRectMake;
		m_pFFRoomR3->Setup(v, v1, v2, v3, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFRoomR3);

		m_pFFRoomR3_1 = new cRectMake;
		m_pFFRoomR3_1->Setup(v3, v2, v1, v, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFRoomR3_1);
	}
	/************************
		���
	************************/
	{
		//��� ����
		v = D3DXVECTOR3(CENTERX + 9, FF, CENTERZ - 3);
		v1 = D3DXVECTOR3(CENTERX + 9, SF, CENTERZ - 3);
		v2 = D3DXVECTOR3(CENTERX + 9, SF, CENTERZ - 0.3);
		v3 = D3DXVECTOR3(CENTERX + 9, FF, CENTERZ - 0.3);
		m_pFFStairs1 = new cRectMake;
		m_pFFStairs1->Setup(v, v1, v2, v3, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFStairs1);

		m_pFFStairs1_1 = new cRectMake;
		m_pFFStairs1_1->Setup(v3, v2, v1, v, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFStairs1_1);

		//��� ������
		v =  D3DXVECTOR3(CENTERX + 7.8, FF, CENTERZ - 3);
		v1 = D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ - 3);
		v2 = D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ - 0.3);
		v3 = D3DXVECTOR3(CENTERX + 7.8, FF, CENTERZ - 0.3);
		m_pFFStairs2 = new cRectMake;
		m_pFFStairs2->Setup(v, v1, v2, v3, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFStairs2);

		m_pFFStairs2_1 = new cRectMake;
		m_pFFStairs2_1->Setup(v3, v2, v1, v, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFStairs2_1);
		//��� ����
		v = D3DXVECTOR3(CENTERX + 9, FF, CENTERZ - 0.3);
		v1 = D3DXVECTOR3(CENTERX + 9, SF, CENTERZ - 0.3);
		v2 = D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ - 0.3);
		v3 = D3DXVECTOR3(CENTERX + 7.8, FF, CENTERZ - 0.3);
		m_pFFStairs3 = new cRectMake;
		m_pFFStairs3->Setup(v, v1, v2, v3, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFStairs3);

		m_pFFStairs3_1 = new cRectMake;
		m_pFFStairs3_1->Setup(v3, v2, v1, v, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFStairs3_1);
		
		//��� ������2
		v = D3DXVECTOR3(CENTERX + 10, FF, CENTERZ - 3);
		v1 = D3DXVECTOR3(CENTERX + 10, SF, CENTERZ - 3);
		v2 = D3DXVECTOR3(CENTERX + 10, SF, CENTERZ - 0.3);
		v3 = D3DXVECTOR3(CENTERX + 10, FF, CENTERZ - 0.3);
		m_pFFStairs4 = new cRectMake;
		m_pFFStairs4->Setup(v, v1, v2, v3, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFStairs4);

		m_pFFStairs4_1 = new cRectMake;
		m_pFFStairs4_1->Setup(v3, v2, v1, v, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFStairs4_1);

		
		//��� ����2
		v = D3DXVECTOR3(CENTERX + 10, FF, CENTERZ - 0.3);
		v1 = D3DXVECTOR3(CENTERX + 10, SF, CENTERZ - 0.3);
		v2 = D3DXVECTOR3(CENTERX + 9, SF, CENTERZ - 0.3);
		v3 = D3DXVECTOR3(CENTERX + 9, FF, CENTERZ - 0.3);
		m_pFFStairs5 = new cRectMake;
		m_pFFStairs5->Setup(v, v1, v2, v3, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFStairs5);

		m_pFFStairs5_1 = new cRectMake;
		m_pFFStairs5_1->Setup(v3, v2, v1, v, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFStairs5_1);
	}
}

void cWall::SetupSF()
{
	/*********************************************
		2�� ��ü
	*********************************************/
	//����
	m_pSFUp = new cRectMake;
	m_pSFUp->Setup(D3DXVECTOR3(CENTERX + 6, SF, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 6, TOP, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 10.7, TOP, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 10.7, SF, CENTERZ + 3)
		, "Texture/maps/images.jpg");
	m_vecSF.push_back(m_pSFUp);

	//����
	m_pSFLeft = new cRectMake;
	m_pSFLeft->Setup(D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 6, TOP, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 6, TOP, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 6, SF, CENTERZ + 3)
		, "Texture/maps/images.jpg");
	m_vecSF.push_back(m_pSFLeft);


	m_pSFLeftPrint = new cRectMake;
	m_pSFLeftPrint->Setup(D3DXVECTOR3(CENTERX + 6, TOP - 1, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 6, TOP, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 6, TOP, CENTERZ + -1)
		, D3DXVECTOR3(CENTERX + 6, TOP - 1, CENTERZ - 1)
		, "Texture/maps/chalk_hieroglyphs.dds");
	m_vecSF.push_back(m_pSFLeftPrint);


	//������
	m_pSFRight = new cRectMake;
	m_pSFRight->Setup(D3DXVECTOR3(CENTERX + 10.7, SF, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 10.7, TOP, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 10.7, TOP, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 10.7, SF, CENTERZ - 2.2)
		, "Texture/maps/images.jpg");
	m_vecSF.push_back(m_pSFRight);


	m_pSFRightPrint_1 = new cRectMake;
	m_pSFRightPrint_1->Setup(D3DXVECTOR3(CENTERX + 10.7, SF, CENTERZ + 2)
		, D3DXVECTOR3(CENTERX + 10.7, TOP, CENTERZ + 2)
		, D3DXVECTOR3(CENTERX + 10.7, TOP, CENTERZ - 1.5)
		, D3DXVECTOR3(CENTERX + 10.7, SF, CENTERZ - 1.5)
		, "Texture/maps/maze_writing02.dds");
	m_vecSF.push_back(m_pSFRightPrint_1);

	//�Ʒ���
	m_pSFDown = new cRectMake;
	m_pSFDown->Setup(D3DXVECTOR3(CENTERX + 10.7, SF, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 10.7, TOP, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 6, TOP, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 2.2)
		, "Texture/maps/images.jpg");
	m_vecSF.push_back(m_pSFDown);

	/******************************
		���� ��
	******************************/
	D3DXVECTOR3 v, v1, v2, v3;
	//���ʹ� ù��° ��
	v = D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ - 2.2);
	v1 = D3DXVECTOR3(CENTERX + 7.8, TOP, CENTERZ - 2.2);
	v2 = D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ + 0.7);
	v3 = D3DXVECTOR3(CENTERX + 7.8, TOP, CENTERZ + 0.7);
	m_pSFLRoom1 = new cRectMake;
	m_pSFLRoom1->Setup(v, v1, v2, v3, "Texture/maps/images.jpg");
	m_vecSF.push_back(m_pSFLRoom1);

	m_pSFLRoom1_1 = new cRectMake;
	m_pSFLRoom1_1->Setup(v3, v2, v1, v, "Texture/maps/images.jpg");
	m_vecSF.push_back(m_pSFLRoom1_1);

	m_pSFRightPrint = new cRectMake;
	m_pSFRightPrint->Setup(D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 7.8, TOP, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ + 1)
		, D3DXVECTOR3(CENTERX + 7.8, TOP, CENTERZ + 1)
		, "Texture/maps/chalk_alchemy_circles.dds");
	m_vecSF.push_back(m_pSFRightPrint);

	//���ʹ� �ι�° ��
	v = D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ + 1.65);
	v1 = D3DXVECTOR3(CENTERX + 7.8, TOP, CENTERZ + 1.65);
	v2 = D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ + 3);
	v3 = D3DXVECTOR3(CENTERX + 7.8, TOP, CENTERZ + 3);
	m_pSFLRoom2 = new cRectMake;
	m_pSFLRoom2->Setup(v, v1, v2, v3, "Texture/maps/images.jpg");
	m_vecSF.push_back(m_pSFLRoom2);

	m_pSFLRoom2_1 = new cRectMake;
	m_pSFLRoom2_1->Setup(v3, v2, v1, v, "Texture/maps/images.jpg");
	m_vecSF.push_back(m_pSFLRoom2_1);

	//���ʹ� ���� ��
	v = D3DXVECTOR3(CENTERX + 7.8, TOP - 0.5, CENTERZ + 0.7);
	v1 = D3DXVECTOR3(CENTERX + 7.8, TOP, CENTERZ + 0.7);
	v2 = D3DXVECTOR3(CENTERX + 7.8, TOP - 0.5, CENTERZ + 1.65);
	v3 = D3DXVECTOR3(CENTERX + 7.8, TOP, CENTERZ + 1.65);
	
	m_pSFLRoom3 = new cRectMake;
	m_pSFLRoom3->Setup(v, v1, v2, v3, "Texture/maps/images.jpg");
	m_vecSF.push_back(m_pSFLRoom3);

	m_pSFLRoom3_1 = new cRectMake;
	m_pSFLRoom3_1->Setup(v3, v2, v1, v, "Texture/maps/images.jpg");
	m_vecSF.push_back(m_pSFLRoom3_1);
	

	/******************************
		������ ��
	******************************/

	v = D3DXVECTOR3(CENTERX + 9, SF, CENTERZ - 2.2);
	v1 = D3DXVECTOR3(CENTERX + 9, TOP, CENTERZ - 2.2);
	v2 = D3DXVECTOR3(CENTERX + 9, SF, CENTERZ + 0.7);
	v3 = D3DXVECTOR3(CENTERX + 9, TOP, CENTERZ + 0.7);

	//���ʹ� ù��° ��
	m_pSFRRoom1 = new cRectMake;
	m_pSFRRoom1->Setup(v, v1, v2, v3, "Texture/maps/images.jpg");
	m_vecSF.push_back(m_pSFRRoom1);
	m_pSFRRoom1_1 = new cRectMake;
	m_pSFRRoom1_1->Setup(v3, v2, v1, v, "Texture/maps/images.jpg");
	m_vecSF.push_back(m_pSFRRoom1_1);

	v = D3DXVECTOR3(CENTERX + 9, SF, CENTERZ + 1.65);
	v1 = D3DXVECTOR3(CENTERX + 9, TOP, CENTERZ + 1.65);
	v2 = D3DXVECTOR3(CENTERX + 9, SF, CENTERZ + 3);
	v3 = D3DXVECTOR3(CENTERX + 9, TOP, CENTERZ + 3);

	//���ʹ� �ι�° ��
	m_pSFRRoom2 = new cRectMake;
	m_pSFRRoom2->Setup(v, v1, v2, v3, "Texture/maps/images.jpg");
	m_vecSF.push_back(m_pSFRRoom2);

	m_pSFRRoom2_1 = new cRectMake;
	m_pSFRRoom2_1->Setup(v3, v2, v1, v, "Texture/maps/images.jpg");
	m_vecSF.push_back(m_pSFRRoom2_1);

	v = D3DXVECTOR3(CENTERX + 9, TOP - 0.5, CENTERZ + 0.7);
	v1 = D3DXVECTOR3(CENTERX + 9, TOP, CENTERZ + 0.7);
	v2 = D3DXVECTOR3(CENTERX + 9, TOP - 0.5, CENTERZ + 1.65);
	v3 = D3DXVECTOR3(CENTERX + 9, TOP, CENTERZ + 1.65);

	//���ʹ� ���� ��
	m_pSFRRoom3 = new cRectMake;
	m_pSFRRoom3->Setup(v, v1, v2, v3, "Texture/maps/images.jpg");
	m_vecSF.push_back(m_pSFRRoom3);

	m_pSFRRoom3_1 = new cRectMake;
	m_pSFRRoom3_1->Setup(v3, v2, v1, v, "Texture/maps/images.jpg");
	m_vecSF.push_back(m_pSFRRoom3_1);

	//>>>17.06.15 ����
	//���ʹ� ���� ȭ��ǥ
	m_pSFLeftArrowPrint = new cRectMake;
	m_pSFLeftArrowPrint->Setup(
		D3DXVECTOR3(CENTERX + 9.01, TOP - 0.7, CENTERZ - 0.5),
		D3DXVECTOR3(CENTERX + 9.01, TOP, CENTERZ - 0.5),
		D3DXVECTOR3(CENTERX + 9.01, TOP - 0.7, CENTERZ + 0.5),
		D3DXVECTOR3(CENTERX + 9.01, TOP, CENTERZ + 0.5),
		"Texture/maps/left_arrow.png");
	m_vecSF.push_back(m_pSFLeftArrowPrint);

	//���ʹ� ������ ȭ��ǥ

	m_pSFRightArrowPrint = new cRectMake;
	m_pSFRightArrowPrint->Setup(
		D3DXVECTOR3(CENTERX + 9.01, TOP - 0.7, CENTERZ - 1.7),
		D3DXVECTOR3(CENTERX + 9.01, TOP, CENTERZ - 1.7),
		D3DXVECTOR3(CENTERX + 9.01, TOP - 0.7, CENTERZ - 0.7),
		D3DXVECTOR3(CENTERX + 9.01, TOP, CENTERZ - 0.7),
		"Texture/maps/right_arrow.png");
	m_vecSF.push_back(m_pSFRightArrowPrint);
	//////////<<<<<<<<<<<<<<<<<<<<<<<<
}

void cWall::RenderB1F()
{

	for each (auto it in m_vecB1F)
	{
		it->Render();
	}

}

void cWall::RenderFF()
{
	for each (auto it in m_vecFF)
	{
		it->Render();
	}
}

void cWall::RenderSF()
{
	for each (auto it in m_vecSF)
	{
		it->Render();
	}
}
