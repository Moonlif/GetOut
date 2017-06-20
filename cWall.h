#pragma once
#include "cRectMake.h"

class cWall
{
private:
	/********************
	����
	*********************/
	std::vector<cRectMake*> m_vecB1F;
	std::vector<cRectMake*> m_vecFF;
	std::vector<cRectMake*> m_vecSF;
	//���� ���� �Ʒ��� ������ ��
	cRectMake* m_pB1Up;
	cRectMake* m_pB1Up_1;

	cRectMake* m_pB1Left;

	cRectMake* m_pB1Down;
	cRectMake* m_pB1Down_1;
	cRectMake* m_pB1Down_2;

	cRectMake* m_pB1Right;

	//���
	cRectMake* m_pB1Stairs;
	cRectMake* m_pB1Stairs_1;


	//��
	cRectMake* m_pB1RoomRight1;
	cRectMake* m_pB1RoomRight1_1;

	cRectMake* m_pB1RoomRight2;
	cRectMake* m_pB1RoomRight2_1;

	cRectMake* m_pB1RoomRight3;
	cRectMake* m_pB1RoomRight3_1;

	/********************
	1��
	*********************/
	cRectMake* m_pFFUp;
	cRectMake* m_pFFUp_1;
	cRectMake* m_pFFLeft;
	cRectMake* m_pFFLeft_1;

	cRectMake* m_pFFDown;


	//���� ��
	cRectMake* m_pFFDoorR1;
	cRectMake* m_pFFDoorR2;
	cRectMake* m_pFFDoorR3;


	//ȭ��� �Ʒ�
	cRectMake* m_pFFDown_1;
	cRectMake* m_pFFBathRoomPrint;
	//ȭ��� �����ʺ�
	cRectMake* m_pFFBathRoomR1;
	cRectMake* m_pFFBathRoomR1_1;
	cRectMake* m_pFFBathRoomR2;
	cRectMake* m_pFFBathRoomR2_1;
	cRectMake* m_pFFBathRoomR3;
	cRectMake* m_pFFBathRoomR3_1;

	//ȭ��� ���ʺ�
	cRectMake* m_pFFBathRoomU1;
	cRectMake* m_pFFBathRoomU1_1;
	cRectMake* m_pFFBathRoomU2;
	cRectMake* m_pFFBathRoomU2_1;

	//�� ������ ��
	cRectMake* m_pFFRoomR1;
	cRectMake* m_pFFRoomR1_1;
	cRectMake* m_pFFRoomR2;
	cRectMake* m_pFFRoomR2_1;
	cRectMake* m_pFFRoomR3;
	cRectMake* m_pFFRoomR3_1;
	cRectMake* m_pFFRoomPrint1;
	cRectMake* m_pFFRoomPrint2;

	//���
	cRectMake* m_pFFStairs1;
	cRectMake* m_pFFStairs1_1;
	cRectMake* m_pFFStairs2;
	cRectMake* m_pFFStairs2_1;
	cRectMake* m_pFFStairs3;
	cRectMake* m_pFFStairs3_1;
	cRectMake* m_pFFStairs4;
	cRectMake* m_pFFStairs4_1;
	cRectMake* m_pFFStairs5;
	cRectMake* m_pFFStairs5_1;
	/********************
	2��
	*********************/
	cRectMake* m_pSFUp;
	cRectMake* m_pSFLeft;
	cRectMake* m_pSFDown;
	cRectMake* m_pSFRight;
	cRectMake* m_pSFLeftPrint;
	cRectMake* m_pSFRightPrint;
	cRectMake* m_pSFRightPrint_1;

	cRectMake* m_pSFLRoom1;
	cRectMake* m_pSFLRoom1_1;
	cRectMake* m_pSFLRoom2;
	cRectMake* m_pSFLRoom2_1;
	cRectMake* m_pSFLRoom3;
	cRectMake* m_pSFLRoom3_1;
	//>>>17.06.15
	cRectMake* m_pSFLeftArrowPrint;
	cRectMake* m_pSFRightArrowPrint;
	////////////<<
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

