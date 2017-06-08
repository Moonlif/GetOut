#include "stdafx.h"
#include "cInteract.h"
#include "cRay.h"

cInteract::cInteract()
	: m_n1FBlockCount(0)
	, m_n2FValve1Count(0)
	, m_n2FValve2Count(0)
{
}


cInteract::~cInteract()
{
	for each (auto it in m_vecStuff)
	{
		SAFE_DELETE(it);
	}
}

void cInteract::Setup()
{
	cStuff* stuff = new cStuff;
	stuff->Setup(STUFF_BOARDBLOCK, D3DXVECTOR3(-28, 17.0f, -2.8f), D3DXVECTOR3(0, 0, D3DX_PI / 2.0f), D3DXVECTOR3(0, 0, 0), 3.5f, 0.4f, true);
	m_vecStuff.push_back(stuff);

	stuff = new cStuff;
	stuff->Setup(STUFF_BOX1, D3DXVECTOR3(-9.3f, 3.5f, 18.5f), D3DXVECTOR3(D3DX_PI/2.0f,0,0), D3DXVECTOR3(0, 0, 1.7f), 3.5f, 0.2f, true);
	m_vecStuff.push_back(stuff);

	stuff = new cStuff;
	stuff->Setup(STUFF_BRICKPILE, D3DXVECTOR3(12, 12, 19), D3DXVECTOR3(0, 1.2f, 0), D3DXVECTOR3(0, 0, 0), 3.0f, 0.1f, true);
	m_vecStuff.push_back(stuff);

	stuff = new cStuff;
	stuff->Setup(STUFF_CHEST2, D3DXVECTOR3(10, 0, 18), D3DXVECTOR3(0, -D3DX_PI/2.0f, 0), D3DXVECTOR3(0, 0, 0), 0.1f, 0.1f, true);
	m_vecStuff.push_back(stuff);

	stuff = new cStuff;
	stuff->Setup(STUFF_CHEST3, D3DXVECTOR3(10, 0, 18), D3DXVECTOR3(0, -D3DX_PI / 2.0f, 0), D3DXVECTOR3(0, 0, 0), 3.0f, 0.1f, true);
	m_vecStuff.push_back(stuff);

	stuff = new cStuff;
	stuff->Setup(STUFF_CROWBAR, D3DXVECTOR3(-40, 12, 12), D3DXVECTOR3(0, D3DX_PI / 2.2f, 0), D3DXVECTOR3(0, 0, 0), 2.0f, 0.2f, true);
	m_vecStuff.push_back(stuff);

	stuff = new cStuff;
	stuff->Setup(STUFF_TRAP, D3DXVECTOR3(-38, 12, 18.5f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), 5.0f, 5.0f, true);
	m_vecStuff.push_back(stuff);

	stuff = new cStuff;
	stuff->Setup(STUFF_WOODBOARD1, D3DXVECTOR3(-7, 12, 19.5f), D3DXVECTOR3(0, D3DX_PI/2.0f, 0), D3DXVECTOR3(0, 0, 0), 4.0f, 0.22f, true);
	m_vecStuff.push_back(stuff);

	stuff = new cStuff;
	stuff->Setup(STUFF_WOODBOARD2, D3DXVECTOR3(-6, 12.3f, 18.5f), D3DXVECTOR3(0.07f, 2.3f, 0), D3DXVECTOR3(0, 0, 0), 3.0f, 0.20f, true);
	m_vecStuff.push_back(stuff);

	stuff = new cStuff;
	stuff->Setup(STUFF_WOOD1, D3DXVECTOR3(-6, 15.8f, 22.5f), D3DXVECTOR3(D3DX_PI/2.0f, -0.3f, D3DX_PI/2.0f), D3DXVECTOR3(0, 0, 0), 0.1f, 0.08f, true);
	m_vecStuff.push_back(stuff);

	stuff = new cStuff;
	stuff->Setup(STUFF_WOOD2, D3DXVECTOR3(-13, 12.3f, 16.5f), D3DXVECTOR3(0, 1.0f, 0), D3DXVECTOR3(0, 0, 0), 0.1f, 0.07f, true);
	m_vecStuff.push_back(stuff);

	stuff = new cStuff;
	stuff->Setup(STUFF_WOOD3, D3DXVECTOR3(3, 12.3f, 16.5f), D3DXVECTOR3(0.2f, 1.3f, 0), D3DXVECTOR3(0, 0, 0), 0.1f, 0.07f, true);
	m_vecStuff.push_back(stuff);

	stuff = new cStuff;
	stuff->Setup(STUFF_WOOD3, D3DXVECTOR3(0, 12.3f, 14.5f), D3DXVECTOR3(0.2f, 2.3f, 0.05f), D3DXVECTOR3(0, 0, 0), 0.1f, 0.07f, true);
	m_vecStuff.push_back(stuff);

	stuff = new cStuff;
	stuff->Setup(STUFF_EMPTYBOX, D3DXVECTOR3(-38, 13.0f, -6), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 1, 0), 2.5f, 0.15f, true);
	m_vecStuff.push_back(stuff);

	stuff = new cStuff;
	stuff->Setup(STUFF_VALVE1, D3DXVECTOR3(-4.67f, 30, 0), D3DXVECTOR3(0, D3DX_PI / 2.0f, 0), D3DXVECTOR3(0, 0, 0), 1.5f, 0.2f, true);
	m_vecStuff.push_back(stuff);

	stuff = new cStuff;
	stuff->Setup(STUFF_VALVE2, D3DXVECTOR3(-4.67f, 30, -8), D3DXVECTOR3(0, D3DX_PI / 2.0f, 0), D3DXVECTOR3(0, 0, 0), 1.5f, 0.2f, true);
	m_vecStuff.push_back(stuff);

	//벽돌
	//stuff = new cStuff;
	//stuff->Setup(STUFF_BRICK, D3DXVECTOR3(7, 0, 5), D3DXVECTOR3(0, 0.5f, 0), D3DXVECTOR3(0, 0, 0), 1.0f, 0.2f, true);
	//m_vecStuff.push_back(stuff);
}

void cInteract::Update()
{
	//맵정보에 따른 변화
	if (g_pData->m_bStuffSwitch[SWITCH_BASEMENT_BOX1] && m_vecStuff[1]->GetSwitch() == false)
		m_vecStuff[1]->Reposition(D3DXVECTOR3(-3.3f, 2.3f, 18.5f), D3DXVECTOR3(D3DX_PI / 2.0f, 0, -D3DX_PI / 2.0f));
	if (g_pData->m_bStuffSwitch[SWITCH_BASEMENT_CHEST] && m_vecStuff[4]->GetSwitch() == false)
		m_vecStuff[4]->Reposition(D3DXVECTOR3(9, 4, 18), D3DXVECTOR3(0, -D3DX_PI / 2.0f, -D3DX_PI / 2.0f));
	if (g_pData->m_bStuffSwitch[SWITCH_BASEMENT_CHEST] == false && m_vecStuff[4]->GetSwitch() == false)
		m_vecStuff[4]->Reposition(D3DXVECTOR3(10, 0, 18), D3DXVECTOR3(0, -D3DX_PI / 2.0f, 0));
	if (g_pData->m_bStuffSwitch[SWITCH_FIRSTFLOOR_TRAP] && m_vecStuff[6]->GetSwitch() == false)
		m_vecStuff[6]->Reposition(D3DXVECTOR3(-38, 12, 18.5f), D3DXVECTOR3(0, 0, -D3DX_PI/2.0f));
	if (m_vecStuff[7]->GetSwitch() == false)
		m_vecStuff[7]->Reposition(g_pData->m_vStuffPosition[SWITCH_FIRSTFLOOR_WOODBOARD1], m_vecStuff[7]->GetRotation());
	if (g_pData->m_bStuffSwitch[SWITCH_FIRSTFLOOR_WOODBOARD2] && m_vecStuff[8]->GetSwitch() == false)
		m_vecStuff[8]->Reposition(D3DXVECTOR3(-6, 12.0f, 15.5f), D3DXVECTOR3(0.00f, 1.7f, 0), 0.1f);
	if (g_pData->m_bStuffSwitch[SWITCH_FIRSTFLOOR_BLOCK] && m_vecStuff[0]->GetSwitch() == false)
		m_vecStuff[0]->Reposition(D3DXVECTOR3(-28, 12.15f, 3.8f), D3DXVECTOR3(0, D3DX_PI/2.0f, D3DX_PI / 2.0f), 0.1f);
	
	m_vecStuff[14]->Reposition(m_vecStuff[14]->GetPosition(), m_vecStuff[14]->GetRotation() + D3DXVECTOR3(m_n2FValve1Count * 5, 0, 0));
	m_vecStuff[15]->Reposition(m_vecStuff[15]->GetPosition(), m_vecStuff[15]->GetRotation() + D3DXVECTOR3(m_n2FValve2Count * 5, 0, 0));

	//캐릭터 행동에 따른 변화
	cRay Ray = cRay::RayAtWorldSpace(g_ptMouse.x, g_ptMouse.y);
	int keyState = 0;
	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001) keyState = 1;
	else if (GetAsyncKeyState(VK_RBUTTON) & 0x0001) keyState = 2;

	if (keyState > 0)
	{
		bool lButton = false;
		if (keyState == 1) lButton = true;

		for each(auto it in m_vecStuff)
		{
			if (Ray.IsPicked(it->GetPosition(), it->GetRadius()))
			{
				switch (it->GetStuffCode())
				{
				case STUFF_BOARDBLOCK:
					//if(현재 무기가 빠루)
				{
					//if (g_pData->m_nPlayerNum == 1) 
						m_n1FBlockCount++;
					if (m_n1FBlockCount > 3) g_pData->m_bStuffSwitch[SWITCH_FIRSTFLOOR_BLOCK] = true;
				}
					break;
				case STUFF_BOX1:
					g_pData->m_bStuffSwitch[SWITCH_BASEMENT_BOX1] = true;
					break;
				case STUFF_CHEST3:
					if (g_pData->m_bStuffSwitch[SWITCH_BASEMENT_CHEST] == false) g_pData->m_bStuffSwitch[SWITCH_BASEMENT_CHEST] = true;
					else g_pData->m_bStuffSwitch[SWITCH_BASEMENT_CHEST] = false;
					break;
				case STUFF_TRAP:
					g_pData->m_bStuffSwitch[SWITCH_FIRSTFLOOR_TRAP] = true;
					break;
				case STUFF_WOODBOARD1:
					if (it->GetPosition().x > -32 && m_vecStuff[8]->GetSwitch() == true)
						g_pData->m_vStuffPosition[SWITCH_FIRSTFLOOR_WOODBOARD1] = it->GetPosition() + D3DXVECTOR3(-9, 0, 0);
					break;
				case STUFF_WOODBOARD2:
					if (m_vecStuff[6]->GetSwitch() == true) g_pData->m_bStuffSwitch[SWITCH_FIRSTFLOOR_WOODBOARD2] = true;
					break;
				case STUFF_VALVE1:
					if (lButton) m_n2FValve1Count--;
					else m_n2FValve1Count++;
					if (m_n2FValve1Count > 10)
					{
						m_n2FValve1Count = 10;
						g_pData->m_bStuffSwitch[SWITCH_SECONDFLOOR_VALVE1] = true;
					}
					else if (m_n2FValve1Count < -10) m_n2FValve1Count = -10;
					break;
				case STUFF_VALVE2:
					if (lButton) m_n2FValve2Count--;
					else m_n2FValve2Count++;
					if (m_n2FValve2Count < -10)
					{
						m_n2FValve2Count = -10;
						g_pData->m_bStuffSwitch[SWITCH_SECONDFLOOR_VALVE2] = true;
					}
					else if (m_n2FValve2Count > 10) m_n2FValve2Count = 10;
					break;
				}
		
			}
		}
	}

	//업데이트
	for each (auto it in m_vecStuff)
	{
		it->Update();
	}
}

void cInteract::Render()
{
	for each (auto it in m_vecStuff)
	{
		it->Render();
	}
}
