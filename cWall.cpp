#include "stdafx.h"
#include "cWall.h"


cWall::cWall()
{

}
cWall::~cWall()
{
	//지하
	
	for each (auto it in m_vecB1F)
	{
		SAFE_DELETE(it);
	}

	//1층
	for each (auto it in m_vecFF)
	{
		SAFE_DELETE(it);
	}

	//2층
	for each (auto it in m_vecSF)
	{
		SAFE_DELETE(it);
	}

}

void cWall::Setup()
{
	// 지하
	SetupB1F();
	// 1층
	SetupFF();
	//2층
	SetupSF();
}

void cWall::Render()
{
	//지하 1층
	RenderB1F();
	RenderFF();
	RenderSF();
}

void cWall::SetupB1F()
{
	/************************************
		지하 1층 전체
	*************************************/
	//스타팅 방 위쪽
	m_pB1Up = new cRectMake;
	m_pB1Up->Setup(D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 4)
		, "Texture/maps/castlebase_ceiling03.dds");
	m_vecB1F.push_back(m_pB1Up);

	//2번째 방 위쪽
	m_pB1Up_1 = new cRectMake;
	m_pB1Up_1->Setup(D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 12, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 4)
		, "Texture/maps/castlebase_ceiling03.dds");
	m_vecB1F.push_back(m_pB1Up_1);

	//스타팅 방 왼쪽	
	m_pB1Left = new cRectMake;
	m_pB1Left->Setup(D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ + 4)
		, "Texture/maps/castlebase_ceiling03.dds");
	m_vecB1F.push_back(m_pB1Left);


	//2번째방 오른쪽
	m_pB1Right = new cRectMake;
	m_pB1Right->Setup(D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 12, FF, CENTERZ + 4)
		, D3DXVECTOR3(CENTERX + 12, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 0)
		, "Texture/maps/castlebase_ceiling03.dds");
	m_vecB1F.push_back(m_pB1Right);
	//스타팅방 아래쪽
	m_pB1Down = new cRectMake;
	m_pB1Down->Setup(D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 3, B1F, CENTERZ + 0)
		, "Texture/maps/castlebase_ceiling03.dds");
	m_vecB1F.push_back(m_pB1Down);

	//2번째방 첫번째 아래 
	m_pB1Down_1 = new cRectMake;
	m_pB1Down_1->Setup(D3DXVECTOR3(CENTERX + 9, B1F, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 9, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 8, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 8, B1F, CENTERZ + 0)
		, "Texture/maps/castlebase_ceiling03.dds");
	m_vecB1F.push_back(m_pB1Down_1);

	//2번째방 두번째 아래
	m_pB1Down_2 = new cRectMake;
	m_pB1Down_2->Setup(D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 12, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 10, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 10, B1F, CENTERZ + 0)
		, "Texture/maps/castlebase_ceiling03.dds");
	m_vecB1F.push_back(m_pB1Down_2);

	//계단 첫번째 벽
	m_pB1Stairs = new cRectMake;
	m_pB1Stairs->Setup(D3DXVECTOR3(CENTERX + 9, B1F, CENTERZ - 3)
		, D3DXVECTOR3(CENTERX + 9, FF, CENTERZ - 3)
		, D3DXVECTOR3(CENTERX + 9, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 9, B1F, CENTERZ + 0)
		, "Texture/maps/castlebase_ceiling03.dds");
	m_vecB1F.push_back(m_pB1Stairs);

	//계단 두번째 벽
	m_pB1Stairs_1 = new cRectMake;
	m_pB1Stairs_1->Setup(D3DXVECTOR3(CENTERX + 10, B1F, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 10, FF, CENTERZ + 0)
		, D3DXVECTOR3(CENTERX + 10, FF, CENTERZ - 3)
		, D3DXVECTOR3(CENTERX + 10, B1F, CENTERZ - 3)
		, "Texture/maps/castlebase_ceiling03.dds");
	m_vecB1F.push_back(m_pB1Stairs_1);



	/************************************
		지하 1층 사이벽 
	*************************************/
	//스타팅 룸1 벽1
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

	//스타팅 룸1 벽2
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

	//스타팅 룸1 벽3
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
		1층 전체
	********************************/
	
	{
		//거실 위쪽
		m_pFFUp_1 = new cRectMake;
		m_pFFUp_1->Setup(D3DXVECTOR3(CENTERX + 6.1, FF, CENTERZ + 4)
			, D3DXVECTOR3(CENTERX + 6.1, SF, CENTERZ + 4)
			, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ + 4)
			, D3DXVECTOR3(CENTERX + 13, FF, CENTERZ + 4)
			, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFUp_1);
	
		//통로 아래
		m_pFFDown = new cRectMake;
		m_pFFDown->Setup(D3DXVECTOR3(CENTERX + 13, FF, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 6, FF, CENTERZ - 4)
			, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFDown);


		//현관쪽 벽1
		m_pFFDoorR1 = new cRectMake;
		m_pFFDoorR1->Setup(D3DXVECTOR3(CENTERX + 13, FF, CENTERZ - 3.5)
			, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ - 3.5)
			, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 13, FF, CENTERZ - 4)
			, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFDoorR1);
		
		//현관쪽 벽2
		m_pFFDoorR2 = new cRectMake;
		m_pFFDoorR2->Setup(D3DXVECTOR3(CENTERX + 13, FF, CENTERZ + 4)
			, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ + 4)
			, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ - 2.5)
			, D3DXVECTOR3(CENTERX + 13, FF, CENTERZ - 2.5)
			, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFDoorR2);
	
		//현관쪽 벽3
		m_pFFDoorR3 = new cRectMake;
		m_pFFDoorR3->Setup(D3DXVECTOR3(CENTERX + 13, SF - 0.3, CENTERZ - 2.5)
			, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ - 2.5)
			, D3DXVECTOR3(CENTERX + 13, SF, CENTERZ - 3.5)
			, D3DXVECTOR3(CENTERX + 13, SF - 0.3, CENTERZ - 3.5)
			, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFDoorR3);
			
	}
	/**********************************
		화장실
	**********************************/
	D3DXVECTOR3 v, v1, v2, v3;
	{
		//화장실 왼쪽 벽
		m_pFFLeft_1 = new cRectMake;
		m_pFFLeft_1->Setup(D3DXVECTOR3(CENTERX + 3, FF, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 3, SF, CENTERZ - 4)
			, D3DXVECTOR3(CENTERX + 3, SF, CENTERZ - 0.4)
			, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ - 0.4)
			, "Texture/maps/bathRoom.jpg");
		m_vecFF.push_back(m_pFFLeft_1);

		//화장실 아래
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

		//오른쪽 1
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

		
		//오른쪽 2
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


		//오른쪽 3
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


		//위쪽 1
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

		//위쪽 2
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
		방
	**********************************/
	{
		//방 위쪽
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

		//방 왼쪽 벽
		m_pFFLeft = new cRectMake;
		m_pFFLeft->Setup(D3DXVECTOR3(CENTERX + 3, FF, CENTERZ - 0.4)
			, D3DXVECTOR3(CENTERX + 3, SF, CENTERZ - 0.4)
			, D3DXVECTOR3(CENTERX + 3, SF, CENTERZ + 4)
			, D3DXVECTOR3(CENTERX + 3, FF, CENTERZ + 4)
			, "Texture/maps/images.jpg");
		m_vecFF.push_back(m_pFFLeft);

		//방 오른쪽1
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

		//방 오른쪽2
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
	
		//방 오른쪽3
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
		계단
	************************/
	{
		//계단 왼쪽
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

		//계단 오른쪽
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
		//계단 뒤쪽
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
		
		//계단 오른쪽2
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

		
		//계단 뒤쪽2
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
		2층 전체
	*********************************************/
	//위쪽
	m_pSFUp = new cRectMake;
	m_pSFUp->Setup(D3DXVECTOR3(CENTERX + 6, SF, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 6, TOP, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 10.7, TOP, CENTERZ + 3)
		, D3DXVECTOR3(CENTERX + 10.7, SF, CENTERZ + 3)
		, "Texture/maps/images.jpg");
	m_vecSF.push_back(m_pSFUp);

	//왼쪽
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


	//오른쪽
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

	//아래쪽
	m_pSFDown = new cRectMake;
	m_pSFDown->Setup(D3DXVECTOR3(CENTERX + 10.7, SF, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 10.7, TOP, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 6, TOP, CENTERZ - 2.2)
		, D3DXVECTOR3(CENTERX + 6, SF, CENTERZ - 2.2)
		, "Texture/maps/images.jpg");
	m_vecSF.push_back(m_pSFDown);

	/******************************
		왼쪽 방
	******************************/
	D3DXVECTOR3 v, v1, v2, v3;
	//왼쪽방 첫번째 벽
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

	//왼쪽방 두번째 벽
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

	//왼쪽방 문위 벽
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
		오른쪽 방
	******************************/

	v = D3DXVECTOR3(CENTERX + 9, SF, CENTERZ - 2.2);
	v1 = D3DXVECTOR3(CENTERX + 9, TOP, CENTERZ - 2.2);
	v2 = D3DXVECTOR3(CENTERX + 9, SF, CENTERZ + 0.7);
	v3 = D3DXVECTOR3(CENTERX + 9, TOP, CENTERZ + 0.7);

	//왼쪽방 첫번째 벽
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

	//왼쪽방 두번째 벽
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

	//왼쪽방 문위 벽
	m_pSFRRoom3 = new cRectMake;
	m_pSFRRoom3->Setup(v, v1, v2, v3, "Texture/maps/images.jpg");
	m_vecSF.push_back(m_pSFRRoom3);

	m_pSFRRoom3_1 = new cRectMake;
	m_pSFRRoom3_1->Setup(v3, v2, v1, v, "Texture/maps/images.jpg");
	m_vecSF.push_back(m_pSFRRoom3_1);

	//>>>17.06.15 수정
	//왼쪽방 왼쪽 화살표
	m_pSFLeftArrowPrint = new cRectMake;
	m_pSFLeftArrowPrint->Setup(
		D3DXVECTOR3(CENTERX + 9.01, TOP - 0.7, CENTERZ - 0.5),
		D3DXVECTOR3(CENTERX + 9.01, TOP, CENTERZ - 0.5),
		D3DXVECTOR3(CENTERX + 9.01, TOP - 0.7, CENTERZ + 0.5),
		D3DXVECTOR3(CENTERX + 9.01, TOP, CENTERZ + 0.5),
		"Texture/maps/left_arrow.png");
	m_vecSF.push_back(m_pSFLeftArrowPrint);

	//왼쪽방 오른쪽 화살표

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
