#include "stdafx.h"
#include "cMap.h"


cMap::cMap()
{

}


cMap::~cMap()
{
	SAFE_DELETE(m_pFloor);
	SAFE_DELETE(m_pWall);
	SAFE_DELETE(m_pSurface);
	SAFE_DELETE(m_pCeiling);
	SAFE_DELETE(m_pObjSurface);
	
	for each (auto it in vecMapObj)
	{
		SAFE_DELETE(it);
	}
	vecMapObj.clear();
}

void cMap::Setup()
{
	g_pSoundManager->AddSound("break_wood", "Sound/EffectSound/break_wood.ogg", true, false);

	g_pLightManager->SetPointLight(5,
		D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),
		D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),
		D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),
		D3DXVECTOR3(0,1,5), 100.0f);

	g_pD3DDevice->LightEnable(5, true);

	/*
	g_pLightManager->SetPointLight(eLIGHT::P_B1F_PRISON,
		D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),
		D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),
		D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f),
		D3DXVECTOR3(5, 1, 5), 10.0f);
	*/
	m_pFloor = new cFloor;
	m_pFloor->Setup();
	m_pWall = new cWall;
	m_pWall->Setup();
	m_pSurface = new cSurface;
	m_pSurface->Setup();
	m_pCeiling = new cCeiling;
	m_pCeiling->Setup();
	m_pObjSurface = new cObjectSurface;
	SetupObject();
}

void cMap::SetupObject()
{
	/*****************************
	지하
	******************************/
	{
		//족쇄
		m_pObjShackles = new cMapObject;
		m_pObjShackles->Setup("Objects/map", "shackles.obj");
		vecMapObj.push_back(m_pObjShackles);

		//쇠창살
		m_pObjPrisonbar = new cMapObject;
		m_pObjPrisonbar->Setup("Objects/map", "wriggle_prison_bar2.obj");
		vecMapObj.push_back(m_pObjPrisonbar);

		//지하실 선반
		m_pObjShelf = new cMapObject;
		m_pObjShelf->Setup("Objects/map", "shelf_no_back.obj");
		vecMapObj.push_back(m_pObjShelf);
		m_pObjSurface->AddSurface(D3DXVECTOR3(CENTERX + 7.3, B1F, CENTERZ - 0.2)
			, D3DXVECTOR3(CENTERX + 7.3, B1F, CENTERZ + 1.7)
			, D3DXVECTOR3(CENTERX + 8.2, B1F, CENTERZ + 1.7)
			, D3DXVECTOR3(CENTERX + 8.2, B1F, CENTERZ - 0.2), 0);

		//지하실 와인 베럴
		m_pObjWinebarrel = new cMapObject;
		m_pObjWinebarrel->Setup("Objects/map", "big_wine_barrel.obj");
		vecMapObj.push_back(m_pObjWinebarrel);
		m_pObjSurface->AddSurface(D3DXVECTOR3(CENTERX + 10.5, B1F, CENTERZ + 0)
			, D3DXVECTOR3(CENTERX + 10.5, B1F, CENTERZ + 1.7)
			, D3DXVECTOR3(CENTERX + 12.2, B1F, CENTERZ + 1.7)
			, D3DXVECTOR3(CENTERX + 12.2, B1F, CENTERZ + 0), 0);

		//박스
		m_pObjBox = new cMapObject;
		m_pObjBox->Setup("Objects", "box.obj");
		vecMapObj.push_back(m_pObjBox);
		m_pObjSurface->AddSurface(D3DXVECTOR3(CENTERX + 9.2, B1F, CENTERZ + 3.3)
			, D3DXVECTOR3(CENTERX + 9.2, B1F, CENTERZ + 4.2)
			, D3DXVECTOR3(CENTERX + 11.2, B1F, CENTERZ + 4.2)
			, D3DXVECTOR3(CENTERX + 11.2, B1F, CENTERZ + 3.3), 0);

		m_pLamp = new cMapObject;
		m_pLamp->Setup("Objects/map", "hanging_lantern_wall.obj");
		vecMapObj.push_back(m_pLamp);

	}

	/*****************************
	1 층
	******************************/
	{
		//피아노
		m_pObjPiano = new cMapObject;
		m_pObjPiano->Setup("Objects/map", "piano.obj");
		vecMapObj.push_back(m_pObjPiano);
		m_pObjSurface->AddSurface(D3DXVECTOR3(CENTERX + 5.8, FF, CENTERZ - 0.7)
			, D3DXVECTOR3(CENTERX + 5.8, FF, CENTERZ + 0.5)
			, D3DXVECTOR3(CENTERX + 8.2, FF, CENTERZ + 0.5)
			, D3DXVECTOR3(CENTERX + 8.2, FF, CENTERZ - 0.7), 1);

		//서랍
		m_pDrawers = new cMapObject;
		m_pDrawers->Setup("Objects/map", "chest_of_drawers_nice.obj");
		vecMapObj.push_back(m_pDrawers);
		m_pObjSurface->AddSurface(D3DXVECTOR3(CENTERX + 7.8, FF, CENTERZ - 0.7)
			, D3DXVECTOR3(CENTERX + 7.8, FF, CENTERZ + 0.5)
			, D3DXVECTOR3(CENTERX + 9, FF, CENTERZ + 0.5)
			, D3DXVECTOR3(CENTERX + 9, FF, CENTERZ - 0.7), 1);

		//침대
		m_pObjBed = new cMapObject;
		m_pObjBed->Setup("Objects/map", "bed_nice.obj");
		vecMapObj.push_back(m_pObjBed);
		m_pObjSurface->AddSurface(D3DXVECTOR3(CENTERX + 2.8, FF, CENTERZ - 0.7)
			, D3DXVECTOR3(CENTERX + 2.8, FF, CENTERZ + 1.9)
			, D3DXVECTOR3(CENTERX + 4.8, FF, CENTERZ + 1.9)
			, D3DXVECTOR3(CENTERX + 4.8, FF, CENTERZ - 0.7), 1);

		//고문 기구
		m_pTorture = new cMapObject;
		m_pTorture->Setup("Objects/map", "torture_saw_setup.obj");
		vecMapObj.push_back(m_pTorture);

		m_pObjSurface->AddSurface(D3DXVECTOR3(CENTERX + 11, FF, CENTERZ - 0.5)
			, D3DXVECTOR3(CENTERX + 11, FF, CENTERZ + 0.9)
			, D3DXVECTOR3(CENTERX + 12.2, FF, CENTERZ + 0.9)
			, D3DXVECTOR3(CENTERX + 12.2, FF, CENTERZ - 0.5), 1);

		m_pObjSurface->AddSurface(D3DXVECTOR3(CENTERX + 8.8, FF, CENTERZ - 0.5)
			, D3DXVECTOR3(CENTERX + 8.8, FF, CENTERZ + 0.9)
			, D3DXVECTOR3(CENTERX + 10, FF, CENTERZ + 0.9)
			, D3DXVECTOR3(CENTERX + 10, FF, CENTERZ - 0.5), 1);

		//돌 테이블
		m_pStonetable = new cMapObject;
		m_pStonetable->Setup("Objects/map", "stone_table.obj");
		vecMapObj.push_back(m_pStonetable);
		m_pObjSurface->AddSurface(D3DXVECTOR3(CENTERX + 9.9, FF, CENTERZ - 3)
			, D3DXVECTOR3(CENTERX + 9.9, FF, CENTERZ - 1)
			, D3DXVECTOR3(CENTERX + 11.2, FF, CENTERZ - 1)
			, D3DXVECTOR3(CENTERX + 11.2, FF, CENTERZ - 3), 1);


		//방 박스
		m_pObjSurface->AddSurface(D3DXVECTOR3(CENTERX + 3.3, FF, CENTERZ + 0)
			, D3DXVECTOR3(CENTERX + 3.3, FF, CENTERZ + 2.5)
			, D3DXVECTOR3(CENTERX + 5.1, FF, CENTERZ + 2.5)
			, D3DXVECTOR3(CENTERX + 5.1, FF, CENTERZ + 0), 1);
	}
	/*****************************
	2 층
	******************************/
	{
		//선반
		m_pObjShelfHigh = new cMapObject;
		m_pObjShelfHigh->Setup("Objects/map", "shelf_high01.obj");
		vecMapObj.push_back(m_pObjShelfHigh);
		m_pObjSurface->AddSurface(D3DXVECTOR3(CENTERX + 5.7, SF, CENTERZ - 0.7)
			, D3DXVECTOR3(CENTERX + 5.7, SF, CENTERZ + 3.3)
			, D3DXVECTOR3(CENTERX + 6.8, SF, CENTERZ + 3.3)
			, D3DXVECTOR3(CENTERX + 6.8, SF, CENTERZ - 0.7), 2);


		//책상
		m_pObjDesk = new cMapObject;
		m_pObjDesk->Setup("Objects/map", "work_desk.obj");
		vecMapObj.push_back(m_pObjDesk);
		m_pObjSurface->AddSurface(D3DXVECTOR3(CENTERX + 6.1, SF, CENTERZ - 2.5)
			, D3DXVECTOR3(CENTERX + 6.1, SF, CENTERZ - 1.3)
			, D3DXVECTOR3(CENTERX + 8, SF, CENTERZ - 1.3)
			, D3DXVECTOR3(CENTERX + 8, SF, CENTERZ - 2.5), 2);

		//아이언메이든
		m_pIronmaiden = new cMapObject;
		m_pIronmaiden->Setup("Objects/map", "iron_maiden.obj");
		vecMapObj.push_back(m_pIronmaiden);
		m_pObjSurface->AddSurface(D3DXVECTOR3(CENTERX + 9, SF, CENTERZ + 1.7)
			, D3DXVECTOR3(CENTERX + 9, SF, CENTERZ + 3.3)
			, D3DXVECTOR3(CENTERX + 10.7, SF, CENTERZ + 3.3)
			, D3DXVECTOR3(CENTERX + 10.7, SF, CENTERZ + 1.7), 2);


		m_pBookPile1 = new cMapObject;
		m_pBookPile1->Setup("Objects/map", "book_pile01.obj");
		vecMapObj.push_back(m_pBookPile1);

		m_pBookRow = new cMapObject;
		m_pBookRow->Setup("Objects/map", "book_row01.obj");
		vecMapObj.push_back(m_pBookRow);
	}

	/*****************************
	오브젝트 서페이스
	******************************/
	{
		//지하 

		//상자
		m_pObjSurface->AddSurface(D3DXVECTOR3(CENTERX + 11.4, B1F, CENTERZ + 2.5)
			, D3DXVECTOR3(CENTERX + 11.4, B1F, CENTERZ + 3.5)
			, D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 3.5)
			, D3DXVECTOR3(CENTERX + 12, B1F, CENTERZ + 2.5), 0);

		//지하 움직이는 상자
		m_pObjSurface->AddSurface(D3DXVECTOR3(CENTERX + 8.8, B1F, CENTERZ + 2.7)
			, D3DXVECTOR3(CENTERX + 8.8, B1F, CENTERZ + 3.5)
			, D3DXVECTOR3(CENTERX + 10.2, B1F, CENTERZ + 3.5)
			, D3DXVECTOR3(CENTERX + 10.2, B1F, CENTERZ + 2.7), 0);

		//1층
		//돌무더기
		m_pObjSurface->AddSurface(D3DXVECTOR3(CENTERX + 11.2, FF, CENTERZ + 3)
			, D3DXVECTOR3(CENTERX + 11.2, FF, CENTERZ + 3.5)
			, D3DXVECTOR3(CENTERX + 12.6, FF, CENTERZ + 3.5)
			, D3DXVECTOR3(CENTERX + 12.6, FF, CENTERZ + 3), 1);

		//돌무더기
		m_pObjSurface->AddSurface(D3DXVECTOR3(CENTERX + 11.5, FF, CENTERZ + 2.3)
			, D3DXVECTOR3(CENTERX + 11.5, FF, CENTERZ + 3)
			, D3DXVECTOR3(CENTERX + 12.6, FF, CENTERZ + 3)
			, D3DXVECTOR3(CENTERX + 12.6, FF, CENTERZ + 2.3), 1);

		//화장실 상자
		m_pObjSurface->AddSurface(D3DXVECTOR3(CENTERX + 3.2, FF, CENTERZ - 1.2)
			, D3DXVECTOR3(CENTERX + 3.2, FF, CENTERZ - 0.7)
			, D3DXVECTOR3(CENTERX + 4, FF, CENTERZ - 0.7)
			, D3DXVECTOR3(CENTERX + 4, FF, CENTERZ - 1.2), 1);
	}
}

void cMap::Update()
{
	
}


void cMap::Render()
{
	//m_pSurface->Render();
	//m_pObjSurface->RenderSurface();
	
	m_pFloor->Render();
	m_pWall->Render();
	m_pCeiling->Render();	
	RenderObject();
}

void cMap::RenderObject()
{
	m_pObjShackles->Render(0.08, 33, 7, -24, 1);

	for (int i = 0; i < 12; i++)
	{
		m_pObjPrisonbar->Render(0.33, -31 - i, 0, 12.8, 0);
	}

	for (int i = 0; i < 12; i++)
	{
		m_pObjPrisonbar->Render(0.33, -22, 0, 12.8 + i, 0);
	}

	m_pObjShelf->Render(0.08, 5, 0, 13.8, 1.5);
	m_pObjBox->Render(1, 0, 1, 23, 0);
	m_pObjBox->Render(1, 2.2, 1, 23, 0);
	m_pObjBox->Render(1, 4.5, 1, 23, 0);
	m_pObjBox->Render(1, -2, 1, 23, 0);
	m_pObjBox->Render(1, -1, 3, 23, 0);
	m_pObjBox->Render(1, 3, 3, 23, 0);
	m_pObjPiano->Render(0.13, -18, 12.1, 0, 0);
	m_pObjBed->Render(0.095, -4, 12, -37, 0.5);
	m_pObjWinebarrel->Render(0.05, 5, 0, -7.5, -0.5);
	m_pObjShelfHigh->Render(0.07, -15, 24.1, -22.5, 0.5);
	m_pObjShelfHigh->Render(0.07, -10, 24.1, -22.5, 0.5);
	m_pObjShelfHigh->Render(0.07, -5, 24.1, -22.5, 0.5);
	m_pObjShelfHigh->Render(0.07, 0, 24.1, -22.5, 0.5);
	m_pDrawers->Render(0.09, -10, 14.5, 0, 0);
	m_pObjDesk->Render(8.5, 18, 24.1, 11, 1);
	m_pIronmaiden->Render(0.1, 0, 24.1, -15, -1);
	m_pTorture->Render(0.1, 3, 12, 1, 0);
	m_pStonetable->Render(0.1, 3, 12, -12, 0);
	m_pBookPile1->Render(0.1, -17, 27.5, -11.5, 0);

	m_pObjBox->Render(1, -31.5, 13.1, 9, 0);
	m_pObjBox->Render(1, -31.5, 15.1, 5, 0);
	m_pObjBox->Render(1, -31.5, 13.1, 6, 0);
	m_pObjBox->Render(1, -31.5, 15.1, 12, 0);
	m_pObjBox->Render(1, -31.5, 13.1, 12, 0);
	m_pObjBox->Render(1, -31.5, 15.1, 10, 0);
	m_pObjBox->Render(1, -31.5, 13.1, 10, 0);

	m_pLamp->Render(0.1, -11, 6, 5, 0);
}


bool cMap::GetSurfaceHeight(IN float x, OUT float & y, IN float z)
{

	int floor;
	if (y >= 22)floor = 2;
	if (y >= 11 && y < 22) floor = 1;
	if (y < 11) floor = 0;

	{
		D3DXVECTOR3 vec[200];
		D3DXMATRIXA16 matS, matWorld;
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matS, 6, 6, 6);
		matWorld = matS;

		if (floor == 0) {
			for (int i = 0; i< m_pSurface->GetVecVertex().size(); i++) {
				if (m_pSurface->GetVecVertex()[i].floor == 0) {
					D3DXVec3TransformCoord(&vec[i], &m_pSurface->GetVecVertex()[i].p, &matWorld);
				}
			}
		}
		if (floor == 1) {
			for (int i = 0; i< m_pSurface->GetVecVertex().size(); i++) {
				if (m_pSurface->GetVecVertex()[i].floor == 1) {
					D3DXVec3TransformCoord(&vec[i], &m_pSurface->GetVecVertex()[i].p, &matWorld);
				}
			}
		}
		if (floor == 2) {
			for (int i = 0; i< m_pSurface->GetVecVertex().size(); i++) {
				if (m_pSurface->GetVecVertex()[i].floor == 2) {
					D3DXVec3TransformCoord(&vec[i], &m_pSurface->GetVecVertex()[i].p, &matWorld);
				}
			}
		}

		D3DXVECTOR3 vRayPos(x, 6 + y, z);
		D3DXVECTOR3 vRayDir(0, -1, 0);
		for (size_t i = 0; i < m_pSurface->GetVecVertex().size(); i += 3) {
			float u, v, f;
			if (D3DXIntersectTri(&vec[i + 0], &vec[i + 1], &vec[i + 2], &vRayPos, &vRayDir, &u, &v, &f))
			{
				y = 6 + y - f;
				return true;
			}
		}
		return false;
	}
}


static bool isTrapIng;
static bool isTrapOpen;
bool cMap::GetObjectSurface(IN float x, OUT float & y, IN float z)
{
	if (isTrapIng) return false;
	int floor;
	if (y >= 22)floor = 2;
	if (y >= 11 && y < 22) floor = 1;
	if (y < 11) floor = 0;
	{
		D3DXVECTOR3 vec[200];
		D3DXMATRIXA16 matS, matWorld;
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matS, 6, 6, 6);
		matWorld = matS;


		if (floor == 0) {
			for (int i = 0; i< m_pObjSurface->GetVecVertex().size(); i++) {
				if (m_pObjSurface->GetVecVertex()[i].floor == 0) {
					D3DXVec3TransformCoord(&vec[i], &m_pObjSurface->GetVecVertex()[i].point, &matWorld);
				}
			}
		}
		if (floor == 1) {
			for (int i = 0; i< m_pObjSurface->GetVecVertex().size(); i++) {
				if (m_pObjSurface->GetVecVertex()[i].floor == 1) {
					D3DXVec3TransformCoord(&vec[i], &m_pObjSurface->GetVecVertex()[i].point, &matWorld);
				}
			}
		}
		if (floor == 2) {
			for (int i = 0; i< m_pObjSurface->GetVecVertex().size(); i++) {
				if (m_pObjSurface->GetVecVertex()[i].floor == 2) {
					D3DXVec3TransformCoord(&vec[i], &m_pObjSurface->GetVecVertex()[i].point, &matWorld);
				}
			}
		}
		D3DXVECTOR3 vRayPos(x, 6 + y, z);
		D3DXVECTOR3 vRayDir(0, -1, 0);
		for (size_t i = 0; i < m_pObjSurface->GetVecVertex().size(); i += 3) {
			float u, v, f;
			if (D3DXIntersectTri(&vec[i + 0], &vec[i + 1], &vec[i + 2], &vRayPos, &vRayDir, &u, &v, &f)) {
				return false;
			}
		}
		return true;
	}
}

bool cMap::GetPassSurface(IN float x, OUT float & y, IN float z)
{
	{
		PassSurface vec[200];
		D3DXMATRIXA16 matS, matWorld;
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matS, 6, 6, 6);
		matWorld = matS;
		for (int i = 0; i < m_pSurface->GetPassVertex().size(); i++) {
			D3DXVec3TransformCoord(&vec[i].p, &m_pSurface->GetPassVertex()[i].p, &matWorld);
			vec[i].nindex = m_pSurface->GetPassVertex()[i].nindex;
		}

		D3DXVECTOR3 vRayPos(x, 6 + y, z);
		D3DXVECTOR3 vRayDir(0, -1, 0);
		for (size_t i = 0; i < m_pSurface->GetPassVertex().size(); i += 3) {
			float u, v, f;
			if (D3DXIntersectTri(&vec[i + 0].p, &vec[i + 1].p, &vec[i + 2].p, &vRayPos, &vRayDir, &u, &v, &f)) {
				if (g_pData->m_bStuffSwitch[SWITCH_DOOR_PRISON] == true && vec[i + 0].nindex == SWITCH_DOOR_PRISON)
					return true;
				else if (g_pData->m_bStuffSwitch[SWITCH_BASEMENT_BOX1] == true && vec[i + 0].nindex == SWITCH_BASEMENT_BOX1)
					return true;
				else if (g_pData->m_bStuffSwitch[SWITCH_FIRSTFLOOR_BLOCK] == true && vec[i + 0].nindex == SWITCH_FIRSTFLOOR_BLOCK)
					return true;
				else if (g_pData->m_bStuffSwitch[SWITCH_DOOR_1STTOILET] == true && vec[i + 0].nindex == SWITCH_DOOR_1STTOILET)
					return true;
				else if (g_pData->m_bStuffSwitch[SWITCH_DOOR_1STROOM] == true && vec[i + 0].nindex == SWITCH_DOOR_1STROOM)
					return true;
				else if (g_pData->m_bStuffSwitch[SWITCH_DOOR_2NDROOM1] == true && vec[i + 0].nindex == SWITCH_DOOR_2NDROOM1)
					return true;
				else if (g_pData->m_bStuffSwitch[SWITCH_DOOR_2NDROOM2] == true && vec[i + 0].nindex == SWITCH_DOOR_2NDROOM2)
					return true;
				else if (g_pData->m_bStuffSwitch[SWITCH_FIRSTFLOOR_WOODBOARD1] == true && vec[i + 0].nindex == SWITCH_FIRSTFLOOR_WOODBOARD1 && g_pData->m_nPlayerNum1P == 2)
					return true;
				else if (g_pData->m_bStuffSwitch[SWITCH_FIRSTFLOOR_WOODBOARD1] == true && vec[i + 0].nindex == SWITCH_FIRSTFLOOR_WOODBOARD1 && g_pData->m_nPlayerNum1P == 1){
					g_pData->TextOutWarningWord(string("남자가 가기에는 판자가 약합니다."));
					return false;
				}
				else if (g_pData->m_bStuffSwitch[SWITCH_FIRSTFLOOR_TRAP] == false && vec[i + 0].nindex == SWITCH_FIRSTFLOOR_TRAP) {	// 트랩
					g_pData->m_bStuffSwitch[SWITCH_FIRSTFLOOR_TRAP] = true;
					if (isTrapOpen != true) {
						if (y > 0) {
							isTrapIng = true;
							return true;
						}
					}
					else return false;
				}
			//	else if (g_pData->m_bStuffSwitch[SWITCH_FIRSTFLOOR_TRAP] == true && vec[i + 0].nindex == SWITCH_FIRSTFLOOR_TRAP) {		// 트랩
				
		//		}
				else
					return false;
			}
		}
	}
}

bool cMap::GetMovePossible(IN float x, OUT float & y, IN float z)
{
	if (isTrapIng && y > 0) {
		y -= 0.5;
		return true;
	}
	else if (y < 0 && isTrapIng == true) {
		g_pSoundManager->Play("break_wood", 1.0f);
		isTrapIng = false;
		isTrapOpen = true;
	}
	if (GetSurfaceHeight(x, y, z) && GetObjectSurface(x, y, z)) {
		return true;
	}
	else if (!GetObjectSurface(x, y, z)) {
		return false;
	}
	else if (!GetSurfaceHeight(x, y, z) && GetPassSurface(x, y, z)) {
		return true;
	}
	else {
		false;
	}

}