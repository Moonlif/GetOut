#include "stdafx.h"
#include "cWall.h"


cWall::cWall()
	: m_pB1Up(NULL)
	, m_pB1Left(NULL)
	, m_pB1Down(NULL)
	, m_pB1Down_1(NULL)
	, m_pB1Down_2(NULL)
	, m_pB1Right(NULL)
	, m_pB1Stairs(NULL)
	, m_pB1Stairs_1(NULL)
	, m_pB1RoomRight1(NULL)
	, m_pB1RoomRight1_1(NULL)
	, m_pB1RoomRight2(NULL)
	, m_pB1RoomRight2_1(NULL)
	, m_pB1RoomRight3(NULL)
	, m_pB1RoomRight3_1(NULL)

	, m_pFFUp(NULL)
	, m_pFFUp_1(NULL)
	, m_pFFLeft(NULL)
	, m_pFFLeft_1(NULL)
	, m_pFFDown(NULL)
	, m_pFFDown_1(NULL)
	, m_pFFBathRoomR1(NULL)
	, m_pFFBathRoomR1_1(NULL)
	, m_pFFBathRoomR2(NULL)
	, m_pFFBathRoomR2_1(NULL)
	, m_pFFBathRoomR3(NULL)
	, m_pFFBathRoomR3_1(NULL)
	, m_pFFBathRoomU1(NULL)
	, m_pFFBathRoomU1_1(NULL)
	, m_pFFBathRoomU2(NULL)
	, m_pFFBathRoomU2_1(NULL)
	, m_pFFRoomR1(NULL)
	, m_pFFRoomR1_1(NULL)
	, m_pFFRoomR2(NULL)
	, m_pFFRoomR2_1(NULL)
	, m_pFFRoomR3(NULL)
	, m_pFFRoomR3_1(NULL)
	, m_pFFStairs1(NULL)
	, m_pFFStairs1_1(NULL)
	, m_pFFStairs2(NULL)
	, m_pFFStairs2_1(NULL)
	, m_pFFStairs3(NULL)
	, m_pFFDoorR1(NULL)
	, m_pFFDoorR2(NULL)
	, m_pFFDoorR3(NULL)

	, m_pSFUp(NULL)
	, m_pSFLeft(NULL)
	, m_pSFDown(NULL)
	, m_pSFRight(NULL)
	, m_pSFLRoom1(NULL)
	, m_pSFLRoom1_1(NULL)
	, m_pSFLRoom2(NULL)
	, m_pSFLRoom2_1(NULL)
	, m_pSFLRoom3(NULL)
	, m_pSFLRoom3_1(NULL)
	, m_pSFRRoom1(NULL)
	, m_pSFRRoom1_1(NULL)
	, m_pSFRRoom2(NULL)
	, m_pSFRRoom2_1(NULL)
	, m_pSFRRoom3(NULL)
	, m_pSFRRoom3_1(NULL)
	
{

}
cWall::~cWall()
{
	//����
	{
		SAFE_DELETE(m_pB1Up);
		SAFE_DELETE(m_pB1Left);
		SAFE_DELETE(m_pB1Down);
		SAFE_DELETE(m_pB1Down_1);
		SAFE_DELETE(m_pB1Down_2);
		SAFE_DELETE(m_pB1Right);
		SAFE_DELETE(m_pB1Stairs);
		SAFE_DELETE(m_pB1Stairs_1);


		SAFE_DELETE(m_pB1RoomRight1);
		SAFE_DELETE(m_pB1RoomRight1_1);
		SAFE_DELETE(m_pB1RoomRight2);
		SAFE_DELETE(m_pB1RoomRight2_1);
		SAFE_DELETE(m_pB1RoomRight3);
		SAFE_DELETE(m_pB1RoomRight3_1);
	}
	//1��
	{
		SAFE_DELETE(m_pFFUp);
		SAFE_DELETE(m_pFFUp_1);
		SAFE_DELETE(m_pFFLeft);
		SAFE_DELETE(m_pFFLeft_1);
		SAFE_DELETE(m_pFFDown);
		SAFE_DELETE(m_pFFDown_1);
	
		SAFE_DELETE(m_pFFBathRoomR1);
		SAFE_DELETE(m_pFFBathRoomR1_1);
		SAFE_DELETE(m_pFFBathRoomR2);
		SAFE_DELETE(m_pFFBathRoomR2_1);
		SAFE_DELETE(m_pFFBathRoomR3);
		SAFE_DELETE(m_pFFBathRoomR3_1);
		SAFE_DELETE(m_pFFBathRoomU1);
		SAFE_DELETE(m_pFFBathRoomU1_1);
		SAFE_DELETE(m_pFFBathRoomU2);
		SAFE_DELETE(m_pFFBathRoomU2_1);

		SAFE_DELETE(m_pFFRoomR1);
		SAFE_DELETE(m_pFFRoomR1_1);
		SAFE_DELETE(m_pFFRoomR2);
		SAFE_DELETE(m_pFFRoomR2_1);
		SAFE_DELETE(m_pFFRoomR3);
		SAFE_DELETE(m_pFFRoomR3_1);

		SAFE_DELETE(m_pFFStairs1);
		SAFE_DELETE(m_pFFStairs1_1);
		SAFE_DELETE(m_pFFStairs2);
		SAFE_DELETE(m_pFFStairs2_1);
		SAFE_DELETE(m_pFFStairs3);

		SAFE_DELETE(m_pFFDoorR1);
		SAFE_DELETE(m_pFFDoorR2);
		SAFE_DELETE(m_pFFDoorR3);
	}
	//2��
	{
		SAFE_DELETE(m_pSFUp);
		SAFE_DELETE(m_pSFLeft);
		SAFE_DELETE(m_pSFDown);
		SAFE_DELETE(m_pSFRight);

		SAFE_DELETE(m_pSFLRoom1);
		SAFE_DELETE(m_pSFLRoom1_1);
		SAFE_DELETE(m_pSFLRoom2);
		SAFE_DELETE(m_pSFLRoom2_1);
		SAFE_DELETE(m_pSFLRoom3);
		SAFE_DELETE(m_pSFLRoom3_1);

		SAFE_DELETE(m_pSFRRoom1);
		SAFE_DELETE(m_pSFRRoom1_1);
		SAFE_DELETE(m_pSFRRoom2);
		SAFE_DELETE(m_pSFRRoom2_1);
		SAFE_DELETE(m_pSFRRoom3);
		SAFE_DELETE(m_pSFRRoom3_1);
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
	//2��° �� ����
	m_pB1Up_1 = new cRectMake;
	m_pB1Up_1->Setup(D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 12, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 4)
		, "Texture/maps/game.png");
	//��Ÿ�� �� ����	
	m_pB1Left = new cRectMake;
	m_pB1Left->Setup(D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ + 4)
		, "Texture/maps/cs_office_texture_8.jpg");

	//2��°�� ����
	m_pB1Right = new cRectMake;
	m_pB1Right->Setup(D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 12, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 12, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 0)
		, "Texture/maps/cs_office_texture_8.jpg");
	
	//��Ÿ�ù� �Ʒ���
	m_pB1Down = new cRectMake;
	m_pB1Down->Setup(D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ + 0)
		, "Texture/maps/castlebase_ceiling03.dds");
	//2��°�� ù��° �Ʒ� 
	m_pB1Down_1 = new cRectMake;
	m_pB1Down_1->Setup(D3DXVECTOR3(CENTERX + 9, B1F, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 9, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 0)
		, "Texture/maps/cs_office_texture_8.jpg");
	//2��°�� �ι�° �Ʒ�
	m_pB1Down_2 = new cRectMake;
	m_pB1Down_2->Setup(D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 12, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 10, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 10, B1F, CENTERZ + 0)
		, "Texture/maps/cs_office_texture_8.jpg");
	//��� ù��° ��
	m_pB1Stairs = new cRectMake;
	m_pB1Stairs->Setup(D3DXVECTOR3(CENTERX + 9, B1F, CENTERZ - 3)
		, D3DXVECTOR3(CENTERX + 9, FF, CENTERZ - 3)
		, D3DXVECTOR3(CENTERX + 9, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 9, B1F, CENTERZ + 0)
		, "Texture/maps/cs_office_texture_8.jpg");
	//��� �ι�° ��
	m_pB1Stairs_1 = new cRectMake;
	m_pB1Stairs_1->Setup(D3DXVECTOR3(CENTERX + 10, B1F, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 10, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 10, FF, CENTERZ - 3)
		, D3DXVECTOR3(CENTERX + 10, B1F, CENTERZ - 3)
		, "Texture/maps/cs_office_texture_8.jpg");


	/************************************
		���� 1�� ���̺� 
	*************************************/
	//��Ÿ�� ��1 ��
	D3DXVECTOR3 v, v1, v2, v3;
	v = D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 4);
	v1 = D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 4);
	v2 = D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 3.5);
	v3 = D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 3.5);
	m_pB1RoomRight1 = new cRectMake;
	m_pB1RoomRight1->Setup(v, v1, v2, v3, "Texture/maps/castlebase_ceiling03.dds");
	m_pB1RoomRight1_1 = new cRectMake;
	m_pB1RoomRight1_1->Setup(v3, v2, v1, v, "Texture/maps/cs_office_texture_8.jpg");

	v = D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 3);
	v1 = D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 3);
	v2 = D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 0);
	v3 = D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 0);
	m_pB1RoomRight2 = new cRectMake;
	m_pB1RoomRight2->Setup(v, v1, v2, v3, "Texture/maps/castlebase_ceiling03.dds");
	m_pB1RoomRight2_1 = new cRectMake;
	m_pB1RoomRight2_1->Setup(v3, v2, v1, v, "Texture/maps/cs_office_texture_8.jpg");

	v3 = D3DXVECTOR3(CENTERX + 8, 1.5, CENTERZ + 3);
	v2 = D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 3);
	v1 = D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 3.5);
	v = D3DXVECTOR3(CENTERX + 8, 1.5, CENTERZ + 3.5);
	m_pB1RoomRight3 = new cRectMake;
	m_pB1RoomRight3->Setup(v, v1, v2, v3, "Texture/maps/castlebase_ceiling03.dds");
	m_pB1RoomRight3_1 = new cRectMake;
	m_pB1RoomRight3_1->Setup(v3, v2, v1, v, NULL);

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
			, "Texture/maps/cs_office_texture_8.jpg");
	
		//��� �Ʒ�
		m_pFFDown = new cRectMake;
		m_pFFDown->Setup(D3DXVECTOR3(CENTERX + 13, FF, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 4)
			, NULL);


		//������ ��
		m_pFFDoorR1 = new cRectMake;
		m_pFFDoorR1->Setup(D3DXVECTOR3(CENTERX + 13, FF, CENTERZ - 3.5)
			, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ - 3.5)
			, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 13, FF, CENTERZ - 4)
			, "Texture/maps/cs_office_texture_8.jpg");
		
		m_pFFDoorR2 = new cRectMake;
		m_pFFDoorR2->Setup(D3DXVECTOR3(CENTERX + 13, FF, CENTERZ + 4)
			, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ + 4)
			, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ - 2.5)
			, D3DXVECTOR3(CENTERX + 13, FF, CENTERZ - 2.5)
			, "Texture/maps/cs_office_texture_8.jpg");
	
		
		m_pFFDoorR3 = new cRectMake;
		m_pFFDoorR3->Setup(D3DXVECTOR3(CENTERX + 13, SF - 0.3, CENTERZ - 2.5)
			, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ - 2.5)
			, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ - 3.5)
			, D3DXVECTOR3(CENTERX + 13, SF - 0.3, CENTERZ - 3.5)
			, "Texture/maps/cs_office_texture_8.jpg");
			
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

		//ȭ��� �Ʒ�
		m_pFFDown_1 = new cRectMake;
		m_pFFDown_1->Setup(D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 3, SF, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ - 4)
			, "Texture/maps/bathRoom.jpg");

		//������
		v = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 4);
		v1 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 4);
		v2 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 3);
		v3 = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 3);

		m_pFFBathRoomR1 = new cRectMake;
		m_pFFBathRoomR1->Setup(v3, v2, v1, v, "Texture/maps/bathRoom.jpg"); 
		m_pFFBathRoomR1_1 = new cRectMake;
		m_pFFBathRoomR1_1->Setup(v, v1, v2, v3, "Texture/maps/cs_office_texture_8.jpg");
	
		v = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 0.5);
		v1 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 0.5);
		v2 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 2.5);
		v3 = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 2.5);
	
		m_pFFBathRoomR2 = new cRectMake;
		m_pFFBathRoomR2->Setup(v, v1, v2, v3, "Texture/maps/bathRoom.jpg");
		m_pFFBathRoomR2_1 = new cRectMake;
		m_pFFBathRoomR2_1->Setup(v3, v2, v1, v, "Texture/maps/cs_office_texture_8.jpg");

		v = D3DXVECTOR3(CENTERX + 6, SF - 0.5, CENTERZ - 3);
		v1 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 3);
		v2 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 2.5);
		v3 = D3DXVECTOR3(CENTERX + 6, SF - 0.5, CENTERZ - 2.5);
		m_pFFBathRoomR3 = new cRectMake;
		m_pFFBathRoomR3->Setup(v3, v2, v1, v, "Texture/maps/bathRoom.jpg"); 
		m_pFFBathRoomR3_1 = new cRectMake;
		m_pFFBathRoomR3_1->Setup(v, v1, v2, v3, "Texture/maps/cs_office_texture_8.jpg");

		//����
		v = D3DXVECTOR3(CENTERX + 3, FF, CENTERZ - 0.5);
		v1 = D3DXVECTOR3(CENTERX + 3, SF, CENTERZ - 0.5);
		v2 = D3DXVECTOR3(CENTERX + 5.2, SF, CENTERZ - 0.5);
		v3 = D3DXVECTOR3(CENTERX + 5.2, FF, CENTERZ - 0.5);
		m_pFFBathRoomU1 = new cRectMake;
		m_pFFBathRoomU1->Setup(v, v1, v2, v3, "Texture/maps/bathRoom.jpg");
		m_pFFBathRoomU1_1 = new cRectMake;
		m_pFFBathRoomU1_1->Setup(v3, v2, v1, v, "Texture/maps/cs_office_texture_8.jpg");

		v = D3DXVECTOR3(CENTERX + 5.2, FF + 0.3, CENTERZ - 0.5);
		v1 = D3DXVECTOR3(CENTERX + 5.2, SF, CENTERZ - 0.5);
		v2 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 0.5);
		v3 = D3DXVECTOR3(CENTERX + 6, FF + 0.3, CENTERZ - 0.5);
		m_pFFBathRoomU2 = new cRectMake;
		m_pFFBathRoomU2->Setup(v, v1, v2, v3, "Texture/maps/bathRoom.jpg");
		m_pFFBathRoomU2_1 = new cRectMake;
		m_pFFBathRoomU2_1->Setup(v3, v2, v1, v, "Texture/maps/cs_office_texture_8.jpg");
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
			, "Texture/maps/cs_office_texture_8.jpg");

		//�� ���� ��
		m_pFFLeft = new cRectMake;
		m_pFFLeft->Setup(D3DXVECTOR3(CENTERX + 3, FF, CENTERZ - 0.4)
			, D3DXVECTOR3(CENTERX + 3, SF, CENTERZ - 0.4)
			, D3DXVECTOR3(CENTERX + 3, SF, CENTERZ + 4)
			, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 4)
			, "Texture/maps/cs_office_texture_8.jpg");

		//������
		v = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ + 4);
		v1 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ + 4);
		v2 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ + 3.5);
		v3 = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ + 3.5);

		m_pFFRoomR1 = new cRectMake;
		m_pFFRoomR1->Setup(v, v1, v2, v3, "Texture/maps/cs_office_texture_8.jpg");
		m_pFFRoomR1_1 = new cRectMake;
		m_pFFRoomR1_1->Setup(v3, v2, v1, v, "Texture/maps/cs_office_texture_8.jpg");

		v = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ + 3);
		v1 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ + 3);
		v2 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 0.5);
		v3 = D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 0.5);
	
		m_pFFRoomR2 = new cRectMake;
		m_pFFRoomR2->Setup(v, v1, v2, v3, "Texture/maps/cs_office_texture_8.jpg");
		m_pFFRoomR2_1 = new cRectMake;
		m_pFFRoomR2_1->Setup(v3, v2, v1, v, "Texture/maps/cs_office_texture_8.jpg");
	
		v = D3DXVECTOR3(CENTERX + 6, SF - 0.5, CENTERZ + 3.5);
		v1 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ + 3.5);
		v2 = D3DXVECTOR3(CENTERX + 6, SF, CENTERZ + 3);
		v3 = D3DXVECTOR3(CENTERX + 6, SF - 0.5, CENTERZ + 3);
		m_pFFRoomR3 = new cRectMake;
		m_pFFRoomR3->Setup(v, v1, v2, v3, "Texture/maps/cs_office_texture_8.jpg");
		m_pFFRoomR3_1 = new cRectMake;
		m_pFFRoomR3_1->Setup(v3, v2, v1, v, "Texture/maps/cs_office_texture_8.jpg");
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
		m_pFFStairs1->Setup(v, v1, v2, v3, "Texture/maps/cs_office_texture_8.jpg");
		m_pFFStairs1_1 = new cRectMake;
		m_pFFStairs1_1->Setup(v3, v2, v1, v, "Texture/maps/cs_office_texture_8.jpg");
		//��� ������
		v =  D3DXVECTOR3(CENTERX + 7.8, FF, CENTERZ - 3);
		v1 = D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ - 3);
		v2 = D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ - 0.3);
		v3 = D3DXVECTOR3(CENTERX + 7.8, FF, CENTERZ - 0.3);
		m_pFFStairs2 = new cRectMake;
		m_pFFStairs2->Setup(v, v1, v2, v3, "Texture/maps/cs_office_texture_8.jpg");
		m_pFFStairs2_1 = new cRectMake;
		m_pFFStairs2_1->Setup(v3, v2, v1, v, "Texture/maps/cs_office_texture_8.jpg");
		//��� ����
		m_pFFStairs3 = new cRectMake;
		m_pFFStairs3->Setup(D3DXVECTOR3(CENTERX + 9, FF, CENTERZ - 0.3)
			, D3DXVECTOR3(CENTERX + 9, SF, CENTERZ - 0.3)
			, D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ - 0.3)
			, D3DXVECTOR3(CENTERX + 7.8, FF, CENTERZ - 0.3)
			, "Texture/maps/cs_office_texture_8.jpg");
	}
}

void cWall::SetupSF()
{
	/*********************************************
		2�� ��ü
	*********************************************/
	m_pSFUp = new cRectMake;
	m_pSFUp->Setup(D3DXVECTOR3(CENTERX + 6, SF, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 6, TOP, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 10.7, TOP, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 10.7, SF, CENTERZ + 3)
		, "Texture/maps/cs_office_texture_8.jpg");

	m_pSFLeft = new cRectMake;
	m_pSFLeft->Setup(D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 6, TOP, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 6, TOP, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 6, SF, CENTERZ + 3)
		, "Texture/maps/cs_office_texture_8.jpg");

	m_pSFRight = new cRectMake;
	m_pSFRight->Setup(D3DXVECTOR3(CENTERX + 10.7, SF, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 10.7, TOP, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 10.7, TOP, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 10.7, SF, CENTERZ - 2.2)
		, "Texture/maps/cs_office_texture_8.jpg");

	m_pSFDown = new cRectMake;
	m_pSFDown->Setup(D3DXVECTOR3(CENTERX + 10.7, SF, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 10.7, TOP, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 6, TOP, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 2.2)
		, "Texture/maps/cs_office_texture_8.jpg");

	/******************************
		���� ��
	******************************/
	D3DXVECTOR3 v, v1, v2, v3;
	v = D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ - 2.2);
	v1 = D3DXVECTOR3(CENTERX + 7.8, TOP, CENTERZ - 2.2);
	v2 = D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ + 1);
	v3 = D3DXVECTOR3(CENTERX + 7.8, TOP, CENTERZ + 1);
	
	//���ʹ� ù��° ��
	m_pSFLRoom1 = new cRectMake;
	m_pSFLRoom1->Setup(v, v1, v2, v3, "Texture/maps/cs_office_texture_8.jpg");
	
	m_pSFLRoom1_1 = new cRectMake;
	m_pSFLRoom1_1->Setup(v3, v2, v1, v, "Texture/maps/cs_office_texture_8.jpg");
	
	v = D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ + 1.5);
	v1 = D3DXVECTOR3(CENTERX + 7.8, TOP, CENTERZ + 1.5);
	v2 = D3DXVECTOR3(CENTERX + 7.8, SF, CENTERZ + 3);
	v3 = D3DXVECTOR3(CENTERX + 7.8, TOP, CENTERZ + 3);
	
	//���ʹ� �ι�° ��
	m_pSFLRoom2 = new cRectMake;
	m_pSFLRoom2->Setup(v, v1, v2, v3, "Texture/maps/cs_office_texture_8.jpg");
	
	m_pSFLRoom2_1 = new cRectMake;
	m_pSFLRoom2_1->Setup(v3, v2, v1, v, "Texture/maps/cs_office_texture_8.jpg");

	v = D3DXVECTOR3(CENTERX + 7.8, TOP - 0.5, CENTERZ + 1);
	v1 = D3DXVECTOR3(CENTERX + 7.8, TOP, CENTERZ + 1);
	v2 = D3DXVECTOR3(CENTERX + 7.8, TOP - 0.5, CENTERZ + 1.5);
	v3 = D3DXVECTOR3(CENTERX + 7.8, TOP, CENTERZ + 1.5);

	//���ʹ� ���� ��
	m_pSFLRoom3 = new cRectMake;
	m_pSFLRoom3->Setup(v, v1, v2, v3, "Texture/maps/cs_office_texture_8.jpg");

	m_pSFLRoom3_1 = new cRectMake;
	m_pSFLRoom3_1->Setup(v3, v2, v1, v, "Texture/maps/cs_office_texture_8.jpg");
	

	/******************************
		������ ��
	******************************/

	v = D3DXVECTOR3(CENTERX + 9, SF, CENTERZ - 2.2);
	v1 = D3DXVECTOR3(CENTERX + 9, TOP, CENTERZ - 2.2);
	v2 = D3DXVECTOR3(CENTERX + 9, SF, CENTERZ + 1);
	v3 = D3DXVECTOR3(CENTERX + 9, TOP, CENTERZ + 1);

	//���ʹ� ù��° ��
	m_pSFRRoom1 = new cRectMake;
	m_pSFRRoom1->Setup(v, v1, v2, v3, "Texture/maps/cs_office_texture_8.jpg");

	m_pSFRRoom1_1 = new cRectMake;
	m_pSFRRoom1_1->Setup(v3, v2, v1, v, "Texture/maps/cs_office_texture_8.jpg");

	v = D3DXVECTOR3(CENTERX + 9, SF, CENTERZ + 1.5);
	v1 = D3DXVECTOR3(CENTERX + 9, TOP, CENTERZ + 1.5);
	v2 = D3DXVECTOR3(CENTERX + 9, SF, CENTERZ + 3);
	v3 = D3DXVECTOR3(CENTERX + 9, TOP, CENTERZ + 3);

	//���ʹ� �ι�° ��
	m_pSFRRoom2 = new cRectMake;
	m_pSFRRoom2->Setup(v, v1, v2, v3, "Texture/maps/cs_office_texture_8.jpg");

	m_pSFRRoom2_1 = new cRectMake;
	m_pSFRRoom2_1->Setup(v3, v2, v1, v, "Texture/maps/cs_office_texture_8.jpg");

	v = D3DXVECTOR3(CENTERX + 9, TOP - 0.5, CENTERZ + 1);
	v1 = D3DXVECTOR3(CENTERX + 9, TOP, CENTERZ + 1);
	v2 = D3DXVECTOR3(CENTERX + 9, TOP - 0.5, CENTERZ + 1.5);
	v3 = D3DXVECTOR3(CENTERX + 9, TOP, CENTERZ + 1.5);

	//���ʹ� ���� ��
	m_pSFRRoom3 = new cRectMake;
	m_pSFRRoom3->Setup(v, v1, v2, v3, "Texture/maps/cs_office_texture_8.jpg");

	m_pSFRRoom3_1 = new cRectMake;
	m_pSFRRoom3_1->Setup(v3, v2, v1, v, "Texture/maps/cs_office_texture_8.jpg");
}

void cWall::RenderB1F()
{
	m_pB1Up->Render();
	m_pB1Up_1->Render();
	m_pB1Left->Render();
	m_pB1Right->Render();
	m_pB1Down->Render();
	m_pB1Down_1->Render();
	m_pB1Down_2->Render();
	m_pB1Stairs->Render();
	m_pB1Stairs_1->Render();

	m_pB1RoomRight1->Render();
	m_pB1RoomRight1_1->Render();
	m_pB1RoomRight2->Render();
	m_pB1RoomRight2_1->Render();
	m_pB1RoomRight3->Render();
	m_pB1RoomRight3_1->Render();
}

void cWall::RenderFF()
{
	//1��
	m_pFFUp->Render();
	m_pFFUp_1->Render();

	m_pFFLeft->Render();
	m_pFFLeft_1->Render();

	m_pFFDown->Render();
	m_pFFDown_1->Render();

	m_pFFDoorR1->Render();
	m_pFFDoorR2->Render();
	m_pFFDoorR3->Render();

	//ȭ���
	m_pFFBathRoomR1->Render();
	m_pFFBathRoomR1_1->Render();
	m_pFFBathRoomR2->Render();
	m_pFFBathRoomR2_1->Render();
	m_pFFBathRoomR3->Render();
	m_pFFBathRoomR3_1->Render();

	m_pFFBathRoomU1->Render();
	m_pFFBathRoomU1_1->Render();
	m_pFFBathRoomU2->Render();
	m_pFFBathRoomU2_1->Render();
	
	//��
	m_pFFRoomR1->Render();
	m_pFFRoomR1_1->Render();
	m_pFFRoomR2->Render();
	m_pFFRoomR2_1->Render();
	m_pFFRoomR3->Render();
	m_pFFRoomR3_1->Render();

	m_pFFStairs1->Render();
	m_pFFStairs1_1->Render();
	m_pFFStairs2->Render();
	m_pFFStairs2_1->Render();
	m_pFFStairs3->Render();
}

void cWall::RenderSF()
{
	//2��
	m_pSFUp->Render();
	m_pSFLeft->Render();
	m_pSFRight->Render();
	m_pSFDown->Render();


	m_pSFLRoom1->Render();
	m_pSFLRoom1_1->Render();
	m_pSFLRoom2->Render();
	m_pSFLRoom2_1->Render();
	m_pSFLRoom3->Render();
	m_pSFLRoom3_1->Render();

	m_pSFRRoom1->Render();
	m_pSFRRoom1_1->Render();
	m_pSFRRoom2->Render();
	m_pSFRRoom2_1->Render();
	m_pSFRRoom3->Render();
	m_pSFRRoom3_1->Render();

}
