#include "stdafx.h"
#include "cInteract.h"
#include "cRay.h"

cInteract::cInteract()
	: m_n1FBlockCount(0)
	, m_bValve1(false)
	, m_bValve2(false)
	, m_n2FValve1Count(0)
	, m_n2FValve2Count(0)
	, m_n2FButton1Count(0)
	, m_n2FButton2Count(0)
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
	for (int i = 0; i < STUFF_LASTNUM; ++i)
	{
		m_vecStuff.push_back(new cStuff);
	}

	//item
	m_vecStuff[STUFF_CROWBAR]->Setup(STUFF_CROWBAR, D3DXVECTOR3(-40, 12, 12), D3DXVECTOR3(0, D3DX_PI / 2.2f, 0), D3DXVECTOR3(0, 0, 0), 2.0f, 0.2f, g_pData->m_bStuffSwitch[SWITCH_ONMAP_CROWBAR]);
	m_vecStuff[STUFF_PAPER1]->Setup(STUFF_PAPER1, D3DXVECTOR3(10, 0.7f, 18), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), 1.0f, 0.15f, g_pData->m_bStuffSwitch[SWITCH_ONMAP_PAPER1]);
	m_vecStuff[STUFF_PAPER2]->Setup(STUFF_PAPER2, D3DXVECTOR3(-38, 12.7f, -6), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), 1.0f, 0.15f, g_pData->m_bStuffSwitch[SWITCH_ONMAP_PAPER2]);
	m_vecStuff[STUFF_PAPER3]->Setup(STUFF_PAPER3, D3DXVECTOR3(-17.5f, 27.7f, -10.5f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), 1.0f, 0.15f, g_pData->m_bStuffSwitch[SWITCH_ONMAP_PAPER3]);
	m_vecStuff[STUFF_KEY1]->Setup(STUFF_KEY1, D3DXVECTOR3(-14.0f, 0.3f, 1.5f), D3DXVECTOR3(0, D3DX_PI / 2.5f, 0), D3DXVECTOR3(0, 0, 0), 1.0f, 0.15f, g_pData->m_bStuffSwitch[SWITCH_ONMAP_KEY1]);
	m_vecStuff[STUFF_KEY2]->Setup(STUFF_KEY2, D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), 1.0f, 0.15f, g_pData->m_bStuffSwitch[SWITCH_ONMAP_KEY2]);
	m_vecStuff[STUFF_BRICK1]->Setup(STUFF_BRICK1, D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), 1.0f, 0.17f, g_pData->m_bStuffSwitch[SWITCH_ONMAP_BRICK1]);
	m_vecStuff[STUFF_BRICK2]->Setup(STUFF_BRICK2, D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), 1.0f, 0.17f, g_pData->m_bStuffSwitch[SWITCH_ONMAP_BRICK2]);
	m_vecStuff[STUFF_BRICK3]->Setup(STUFF_BRICK3, D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), 1.0f, 0.17f, g_pData->m_bStuffSwitch[SWITCH_ONMAP_BRICK3]);
	m_vecStuff[STUFF_BRICK4]->Setup(STUFF_BRICK4, D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), 1.0f, 0.17f, g_pData->m_bStuffSwitch[SWITCH_ONMAP_BRICK4]);
	m_vecStuff[STUFF_BRICK5]->Setup(STUFF_BRICK5, D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), 1.0f, 0.17f, g_pData->m_bStuffSwitch[SWITCH_ONMAP_BRICK5]);

	//object : StuffCode만으로 만드려다보니 STUFF_NONE자리에 STUFF_WOOD3하나 더 사용함 
	m_vecStuff[STUFF_BOARDBLOCK]->Setup(STUFF_BOARDBLOCK, D3DXVECTOR3(-28, 17.0f, -2.8f), D3DXVECTOR3(0, 0, D3DX_PI / 2.0f), D3DXVECTOR3(0, 0, 0), 3.5f, 0.4f, true);
	m_vecStuff[STUFF_BOX1]->Setup(STUFF_BOX1, D3DXVECTOR3(-9.1f, 3.5f, 19.3f), D3DXVECTOR3(0, D3DX_PI / 2.0f, D3DX_PI / 2.0f), D3DXVECTOR3(-2, 0, 0), 3.5f, 0.2f, true);
	m_vecStuff[STUFF_BRICKPILE]->Setup(STUFF_BRICKPILE, D3DXVECTOR3(12, 12, 19), D3DXVECTOR3(0, 1.2f, 0), D3DXVECTOR3(0, 0, 0), 3.0f, 0.1f, true);
	m_vecStuff[STUFF_CHEST2]->Setup(STUFF_CHEST2, D3DXVECTOR3(10, 0, 18), D3DXVECTOR3(0, -D3DX_PI / 2.0f, 0), D3DXVECTOR3(0, 0, 0), 0.1f, 0.1f, true);
	m_vecStuff[STUFF_CHEST3]->Setup(STUFF_CHEST3, D3DXVECTOR3(11, 2, 18), D3DXVECTOR3(0, -D3DX_PI / 2.0f, 0), D3DXVECTOR3(1, 2, 0), 2.0f, 0.1f, true);
	m_vecStuff[STUFF_EMPTYBOX]->Setup(STUFF_EMPTYBOX, D3DXVECTOR3(-38, 13.0f, -6), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 1, 0), 0.01f, 0.15f, true);
	m_vecStuff[STUFF_TRAP]->Setup(STUFF_TRAP, D3DXVECTOR3(-38, 12.1f, 18.5f), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), 5.0f, 5.0f, true);
	m_vecStuff[STUFF_VALVE1]->Setup(STUFF_VALVE1, D3DXVECTOR3(-4.67f, 30, 0), D3DXVECTOR3(0, D3DX_PI / 2.0f, 0), D3DXVECTOR3(0, 0, 0), 1.5f, 0.2f, true);
	m_vecStuff[STUFF_VALVE2]->Setup(STUFF_VALVE2, D3DXVECTOR3(-4.67f, 30, -8), D3DXVECTOR3(0, D3DX_PI / 2.0f, 0), D3DXVECTOR3(0, 0, 0), 1.5f, 0.2f, true);
	m_vecStuff[STUFF_WOOD1]->Setup(STUFF_WOOD1, D3DXVECTOR3(-6, 15.8f, 22.5f), D3DXVECTOR3(D3DX_PI / 1.6f, D3DX_PI / 2.0f, 0), D3DXVECTOR3(0, 0, 0), 0.1f, 0.08f, true);
	m_vecStuff[STUFF_WOOD2]->Setup(STUFF_WOOD2, D3DXVECTOR3(-13, 12.3f, 16.5f), D3DXVECTOR3(0, 1.0f, 0), D3DXVECTOR3(0, 0, 0), 0.1f, 0.07f, true);
	m_vecStuff[STUFF_WOOD3]->Setup(STUFF_WOOD3, D3DXVECTOR3(3, 12.3f, 16.5f), D3DXVECTOR3(0.0f, 1.3f, 0), D3DXVECTOR3(0, 0, 0), 0.1f, 0.07f, true);
	m_vecStuff[STUFF_NONE]->Setup(STUFF_WOOD3, D3DXVECTOR3(1, 12.5f, 13.5f), D3DXVECTOR3(-0.1f, 2.3f, 0), D3DXVECTOR3(0, 0, 0), 0.1f, 0.07f, true);
	m_vecStuff[STUFF_WOODBOARD1]->Setup(STUFF_WOODBOARD1, D3DXVECTOR3(-7, 12, 19.5f), D3DXVECTOR3(0, D3DX_PI / 2.0f, 0), D3DXVECTOR3(0, 0, 0), 4.0f, 0.22f, true);
	m_vecStuff[STUFF_WOODBOARD2]->Setup(STUFF_WOODBOARD2, D3DXVECTOR3(-6, 12.3f, 18.5f), D3DXVECTOR3(0.07f, 2.3f, 0), D3DXVECTOR3(0, 0, 0), 3.0f, 0.20f, true);
	m_vecStuff[STUFF_BUTTON1]->Setup(STUFF_BUTTON1, D3DXVECTOR3(-8.2f, 24.5f, 14), D3DXVECTOR3(D3DX_PI, 0, 0), D3DXVECTOR3(0, 0, 0), 1.0f, 0.12f, true);
	m_vecStuff[STUFF_BUTTON2]->Setup(STUFF_BUTTON2, D3DXVECTOR3(-8.2f, 24.5f, 14), D3DXVECTOR3(D3DX_PI, 0, 0), D3DXVECTOR3(0, 0, 0), 0.1f, 0.12f, true);
	//m_vecStuff[STUFF_BUTTON3]->Setup(STUFF_BUTTON3, D3DXVECTOR3(-11.5f, 24.5f, 14), D3DXVECTOR3(D3DX_PI, 0, 0), D3DXVECTOR3(0, 0, 0), 1.0f, 0.12f, true);
	//m_vecStuff[STUFF_BUTTON4]->Setup(STUFF_BUTTON4, D3DXVECTOR3(-11.5f, 24.5f, 14), D3DXVECTOR3(D3DX_PI, 0, 0), D3DXVECTOR3(0, 0, 0), 0.1f, 0.12f, true);
}

void cInteract::Update()
{
	//맵정보에 따른 변화
	if (g_pData->m_bStuffSwitch[SWITCH_FIRSTFLOOR_BLOCK] && m_vecStuff[STUFF_BOARDBLOCK]->GetSwitch() == false)
		m_vecStuff[STUFF_BOARDBLOCK]->Reposition(D3DXVECTOR3(-28, 12.15f, 3.8f), D3DXVECTOR3(0, D3DX_PI / 2.0f, D3DX_PI / 2.0f), 0.1f);
	if (g_pData->m_bStuffSwitch[SWITCH_BASEMENT_BOX1] && m_vecStuff[STUFF_BOX1]->GetSwitch() == false)
		m_vecStuff[STUFF_BOX1]->Reposition(D3DXVECTOR3(-5.0f, 0, 21.0f), D3DXVECTOR3(0, D3DX_PI / 2.0f, 0));
	if (g_pData->m_bStuffSwitch[SWITCH_BASEMENT_CHEST] && m_vecStuff[STUFF_CHEST3]->GetSwitch() == false)
		m_vecStuff[STUFF_CHEST3]->Reposition(D3DXVECTOR3(10, 6, 18), D3DXVECTOR3(0, -D3DX_PI / 2.0f, -D3DX_PI / 2.0f));
	if (g_pData->m_bStuffSwitch[SWITCH_FIRSTFLOOR_TRAP] && m_vecStuff[STUFF_TRAP]->GetSwitch() == false)
		m_vecStuff[STUFF_TRAP]->Reposition(D3DXVECTOR3(-38, 12, 18.5f), D3DXVECTOR3(0, 0, -D3DX_PI / 2.0f));
	if (m_bValve1)
	{
		m_vecStuff[STUFF_VALVE1]->Reposition(m_vecStuff[STUFF_VALVE1]->GetPosition(), D3DXVECTOR3((float)m_n2FValve1Count * D3DX_PI / 2.0f, D3DX_PI / 2.0f, 0));
		m_bValve1 = false;
	}
	if (m_bValve2)
	{
		m_vecStuff[STUFF_VALVE2]->Reposition(m_vecStuff[STUFF_VALVE2]->GetPosition(), D3DXVECTOR3((float)m_n2FValve2Count * D3DX_PI / 2.0f, D3DX_PI / 2.0f, 0));
		m_bValve2 = false;
	}
	if (m_vecStuff[STUFF_WOODBOARD1]->GetSwitch() == false)
		m_vecStuff[STUFF_WOODBOARD1]->Reposition(g_pData->m_vStuffPosition[SWITCH_FIRSTFLOOR_WOODBOARD1], m_vecStuff[STUFF_WOODBOARD1]->GetRotation());
	if (g_pData->m_bStuffSwitch[SWITCH_FIRSTFLOOR_WOODBOARD2] && m_vecStuff[STUFF_WOODBOARD2]->GetSwitch() == false)
		m_vecStuff[STUFF_WOODBOARD2]->Reposition(D3DXVECTOR3(-6, 12.0f, 15.5f), D3DXVECTOR3(0.00f, 1.7f, 0), 0.1f);
	if (g_pData->m_bStuffSwitch[SWITCH_SECONDFLOOR_BUTTON1] && m_vecStuff[STUFF_BUTTON1]->GetSwitch() == false)
		m_vecStuff[STUFF_BUTTON1]->Reposition(D3DXVECTOR3(-8.2f, 24, 14), D3DXVECTOR3(D3DX_PI, 0, 0));
	if (g_pData->m_bStuffSwitch[SWITCH_SECONDFLOOR_BUTTON1] == false && m_vecStuff[STUFF_BUTTON1]->GetSwitch() == false)
		m_vecStuff[STUFF_BUTTON1]->Reposition(D3DXVECTOR3(-8.2f, 24.5f, 14), D3DXVECTOR3(D3DX_PI, 0, 0));
	//if (g_pData->m_bStuffSwitch[SWITCH_SECONDFLOOR_BUTTON2] && m_vecStuff[STUFF_BUTTON3]->GetSwitch() == false)
	//	m_vecStuff[STUFF_BUTTON3]->Reposition(D3DXVECTOR3(-11.5f, 24, 14), D3DXVECTOR3(D3DX_PI, 0, 0));
	//if (g_pData->m_bStuffSwitch[SWITCH_SECONDFLOOR_BUTTON2] == false && m_vecStuff[STUFF_BUTTON3]->GetSwitch() == false)
	//	m_vecStuff[STUFF_BUTTON3]->Reposition(D3DXVECTOR3(-11.5f, 24.5f, 14), D3DXVECTOR3(D3DX_PI, 0, 0));


	//캐릭터 행동에 따른 변화
	//m_n2FButton1Count = 0;
	//m_n2FButton2Count = 0;
	//D3DXVECTOR3 vPlayerPos;
	//if (g_pData->m_nPlayerNum1P == 1) vPlayerPos = g_pData->m_vPosition1P;
	//else if (g_pData->m_nPlayerNum1P == 2) vPlayerPos = g_pData->m_vPosition2P;
	//float dis = D3DXVec3Length(&(vPlayerPos - m_vecStuff[STUFF_BUTTON1]->GetPosition()));
	//if (dis <= 1.0f) m_n2FButton1Count += 6;
	////float dis2 = D3DXVec3Length(&(vPlayerPos - m_vecStuff[STUFF_BUTTON3]->GetPosition()));
	////if (dis <= 1.0f) m_n2FButton2Count += 6;

	//for (int i = STUFF_BRICK1; i < STUFF_BRICK5; ++i)
	//{
	//	float distance;
	//	distance = D3DXVec3Length(&(m_vecStuff[i]->GetPosition() - m_vecStuff[STUFF_BUTTON1]->GetPosition()));
	//	if (distance <= 1.0f) m_n2FButton1Count++;
	//	distance = D3DXVec3Length(&(m_vecStuff[i]->GetPosition() - m_vecStuff[STUFF_BUTTON3]->GetPosition()));
	//	if (distance <= 1.0f) m_n2FButton2Count++;
	//}

	//if (m_n2FButton1Count > 5) g_pData->m_bStuffSwitch[SWITCH_SECONDFLOOR_BUTTON1] = true;
	//else g_pData->m_bStuffSwitch[SWITCH_SECONDFLOOR_BUTTON1] = false;
	//if (m_n2FButton2Count > 5) g_pData->m_bStuffSwitch[SWITCH_SECONDFLOOR_BUTTON2] = true;
	//else g_pData->m_bStuffSwitch[SWITCH_SECONDFLOOR_BUTTON2] = false;

	//picking
	if (g_pData->GetIsInvenOpen() == false)
	{
		int keyState = 0;
		if (GetAsyncKeyState(VK_LBUTTON) & 0x0001) keyState = 1;
		else if (GetAsyncKeyState(VK_RBUTTON) & 0x0001) keyState = 2;
		//PickStuff(keyState, vPlayerPos);
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

void cInteract::PickStuff(int keyState, D3DXVECTOR3 playerPos)
{
	if (keyState == 0) return;

	bool lButton = false;
	if (keyState == 1) lButton = true;

	cRay Ray = cRay::RayAtWorldSpace(g_ptMouse.x, g_ptMouse.y);

	for each(auto it in m_vecStuff)
	{
		if (it == NULL) continue;

		if (Ray.IsPicked(it->GetPosition(), it->GetRadius()) && it->GetIsOnMap())
		{
			switch (it->GetStuffCode())
			{
			case STUFF_BOARDBLOCK:
				//if(현재 무기가 빠루)
			{
				//if (g_pData->m_nPlayerNum == 1) //남자면
				m_n1FBlockCount++;
				if (m_n1FBlockCount > 3) g_pData->m_bStuffSwitch[SWITCH_FIRSTFLOOR_BLOCK] = true;
			}
			return;
			case STUFF_BOX1:
				g_pData->m_bStuffSwitch[SWITCH_BASEMENT_BOX1] = true;
				return;
			case STUFF_CHEST3:
				g_pData->m_bStuffSwitch[SWITCH_BASEMENT_CHEST] = true;
				return;
			case STUFF_TRAP:
				g_pData->m_bStuffSwitch[SWITCH_FIRSTFLOOR_TRAP] = true;
				return;
			case STUFF_WOODBOARD1:
				if (it->GetPosition().x > -32 && g_pData->m_bStuffSwitch[SWITCH_FIRSTFLOOR_WOODBOARD2] == true)
				{
					g_pData->m_vStuffPosition[SWITCH_FIRSTFLOOR_WOODBOARD1] = it->GetPosition() + D3DXVECTOR3(-9, 0, 0);
					if (g_pData->m_vStuffPosition[SWITCH_FIRSTFLOOR_WOODBOARD1].x <= -32) g_pData->m_bStuffSwitch[SWITCH_FIRSTFLOOR_WOODBOARD1] = true;
				}
				break;
			case STUFF_WOODBOARD2:
				if (g_pData->m_bStuffSwitch[SWITCH_FIRSTFLOOR_TRAP] == true) g_pData->m_bStuffSwitch[SWITCH_FIRSTFLOOR_WOODBOARD2] = true;
				return;
			case STUFF_VALVE1:
				if (m_vecStuff[14]->GetSwitch() == true) continue;
				m_bValve1 = true;
				if (lButton) m_n2FValve1Count--;
				else m_n2FValve1Count++;
				if (m_n2FValve1Count > 8)
				{
					m_n2FValve1Count = 8;
					g_pData->m_bStuffSwitch[SWITCH_SECONDFLOOR_VALVE1] = true;
				}
				else if (m_n2FValve1Count < -8) m_n2FValve1Count = -8;
				return;
			case STUFF_VALVE2:
				if (m_vecStuff[15]->GetSwitch() == true) continue;
				m_bValve2 = true;
				if (lButton) m_n2FValve2Count--;
				else m_n2FValve2Count++;
				if (m_n2FValve2Count < -8)
				{
					m_n2FValve2Count = -8;
					g_pData->m_bStuffSwitch[SWITCH_SECONDFLOOR_VALVE2] = true;
				}
				else if (m_n2FValve2Count > 8) m_n2FValve2Count = 8;
				return;
			case STUFF_BUTTON1:
				g_pData->m_bStuffSwitch[SWITCH_SECONDFLOOR_BUTTON1] = true;
				return;
			case STUFF_CROWBAR:
				g_pData->GetItem(STUFF_CROWBAR);
				return;
			case STUFF_PAPER1:
				if (g_pData->m_bStuffSwitch[SWITCH_BASEMENT_CHEST])
				{
					g_pData->GetItem(STUFF_PAPER1);
				}
				return;
			case STUFF_PAPER2:
				g_pData->GetItem(STUFF_PAPER2);
				return;
			case STUFF_PAPER3:
				g_pData->GetItem(STUFF_PAPER3);
				return;
			case STUFF_KEY1:
				g_pData->GetItem(STUFF_KEY1);
				return;
			case STUFF_KEY2:
				g_pData->GetItem(STUFF_KEY2);
				return;
			case STUFF_BRICK1:
				g_pData->GetItem(STUFF_BRICK1);
				return;
			case STUFF_BRICK2:
				g_pData->GetItem(STUFF_BRICK2);
				return;
			case STUFF_BRICK3:
				g_pData->GetItem(STUFF_BRICK3);
				return;
			case STUFF_BRICK4:
				g_pData->GetItem(STUFF_BRICK4);
				return;
			case STUFF_BRICK5:
				g_pData->GetItem(STUFF_BRICK5);
				return;
			case STUFF_BRICKPILE:
				for (int i = 0; i < 5; ++i)
				{
					if (g_pData->m_bStuffSwitch[STUFF_BRICK1 + i] == false)
					{
						g_pData->GetItem(StuffCode(STUFF_BRICK1 + i));
						return;
					}
				}
				break;
			}
		}
	}

}