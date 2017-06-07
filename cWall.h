#pragma once
#include "cRectMake.h"

class cWall
{
private:
	/********************
		지하
	*********************/
	//위쪽 왼쪽 아래쪽 오른쪽 벽
	cRectMake* m_pB1Up;
	cRectMake* m_pB1Up_1;

	cRectMake* m_pB1Left;
	
	cRectMake* m_pB1Down;
	cRectMake* m_pB1Down_1;
	cRectMake* m_pB1Down_2;
	
	cRectMake* m_pB1Right;
	
	//계단
	cRectMake* m_pB1Stairs;
	cRectMake* m_pB1Stairs_1;


	//방
	cRectMake* m_pB1RoomRight1;
	cRectMake* m_pB1RoomRight1_1;

	cRectMake* m_pB1RoomRight2;
	cRectMake* m_pB1RoomRight2_1;

	cRectMake* m_pB1RoomRight3;
	cRectMake* m_pB1RoomRight3_1;

	/********************
		1층
	*********************/
	cRectMake* m_pFFUp;
	cRectMake* m_pFFUp_1;
	cRectMake* m_pFFLeft;
	cRectMake* m_pFFLeft_1;

	cRectMake* m_pFFDown;
	

	//현관 벽
	cRectMake* m_pFFDoorR1;
	cRectMake* m_pFFDoorR2;
	cRectMake* m_pFFDoorR3;
	

	//화장실 아래
	cRectMake* m_pFFDown_1;
	//화장실 오른쪽벽
	cRectMake* m_pFFBathRoomR1;
	cRectMake* m_pFFBathRoomR1_1;
	cRectMake* m_pFFBathRoomR2;
	cRectMake* m_pFFBathRoomR2_1;
	cRectMake* m_pFFBathRoomR3;
	cRectMake* m_pFFBathRoomR3_1;

	//화장실 위쪽벽
	cRectMake* m_pFFBathRoomU1;
	cRectMake* m_pFFBathRoomU1_1;
	cRectMake* m_pFFBathRoomU2;
	cRectMake* m_pFFBathRoomU2_1;
	
	//방 오른쪽 벽
	cRectMake* m_pFFRoomR1;
	cRectMake* m_pFFRoomR1_1;
	cRectMake* m_pFFRoomR2;
	cRectMake* m_pFFRoomR2_1;
	cRectMake* m_pFFRoomR3;
	cRectMake* m_pFFRoomR3_1;
	//계단
	cRectMake* m_pFFStairs1;
	cRectMake* m_pFFStairs1_1;
	cRectMake* m_pFFStairs2;
	cRectMake* m_pFFStairs2_1;
	cRectMake* m_pFFStairs3;
	/********************
		2층
	*********************/
	cRectMake* m_pSFUp;
	cRectMake* m_pSFLeft;
	cRectMake* m_pSFDown;
	cRectMake* m_pSFRight;

	cRectMake* m_pSFLRoom1;
	cRectMake* m_pSFLRoom1_1;
	cRectMake* m_pSFLRoom2;
	cRectMake* m_pSFLRoom2_1;
	cRectMake* m_pSFLRoom3;
	cRectMake* m_pSFLRoom3_1;

	cRectMake* m_pSFRRoom1;
	cRectMake* m_pSFRRoom1_1;
	cRectMake* m_pSFRRoom2;
	cRectMake* m_pSFRRoom2_1;
	cRectMake* m_pSFRRoom3;
	cRectMake* m_pSFRRoom3_1;

	
public:
	cWall();
	~cWall();
	void Setup();
	void Render();
	void SetupB1F();
	void SetupFF();
	void SetupSF();
	void RenderB1F();
	void RenderFF();
	void RenderSF();
};

