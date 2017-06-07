#include "stdafx.h"
#include "cInteract.h"
#include "cStuff.h"
#include "cTrigger.h"
#include "cRay.h"

cInteract::cInteract()
{
}


cInteract::~cInteract()
{
	for each (auto it in m_vecStuff)
	{
		SAFE_DELETE(it);
	}

	for each (auto it in m_vecTrigger)
	{
		SAFE_DELETE(it);
	}
}

void cInteract::Setup()
{

	cStuff* stuff = new cStuff;
	stuff->Setup(STUFF_BOARDBLOCK, D3DXVECTOR3(-28, 17.0f, -2.8f), D3DXVECTOR3(0, 0, D3DX_PI / 2.0f), D3DXVECTOR3(0, 0, 0), 3.0f, 0.4f, true);
	m_vecStuff.push_back(stuff);

	stuff = new cStuff;
	stuff->Setup(STUFF_BOX1, D3DXVECTOR3(-9.3f, 3.5f, 18.5f), D3DXVECTOR3(D3DX_PI/2.0f,0,0), D3DXVECTOR3(0, 0, 1.7f), 3.5f, 0.2f, true);
	m_vecStuff.push_back(stuff);

	stuff = new cStuff;
	stuff->Setup(STUFF_BRICKPILE, D3DXVECTOR3(12, 12, 19), D3DXVECTOR3(0, 1.2f, 0), D3DXVECTOR3(0, 0, 0), 3.0f, 0.1f, true);
	m_vecStuff.push_back(stuff);

	stuff = new cStuff;
	stuff->Setup(STUFF_CHEST2, D3DXVECTOR3(5, 0, 5), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), 3.0f, 0.1f, true);
	m_vecStuff.push_back(stuff);

	//벽돌
	//stuff = new cStuff;
	//stuff->Setup(STUFF_BRICK, D3DXVECTOR3(7, 0, 5), D3DXVECTOR3(0, 0.5f, 0), D3DXVECTOR3(0, 0, 0), 1.0f, 0.2f, true);
	//m_vecStuff.push_back(stuff);
}

void cInteract::Update()
{
	//맵정보에 따른 변화
	if (g_pData->m_BasementSwitch1 && m_vecStuff[1]->GetSwitch() == false) m_vecStuff[1]->Reposition(D3DXVECTOR3(-3.3f, 2.3f, 18.5f), D3DXVECTOR3(D3DX_PI / 2.0f, 0, -D3DX_PI / 2.0f));

	//캐릭터 행동에 따른 변화
	cRay Ray = cRay::RayAtWorldSpace(g_ptMouse.x, g_ptMouse.y);
	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
	{
		for each(auto it in m_vecStuff)
		{
			if (Ray.IsPicked(it->GetPosition(), it->GetRadius()))
			{
				switch (it->GetStuffCode())
				{
				case STUFF_BOX1:
					g_pData->m_BasementSwitch1 = true;
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

	for each (auto it in m_vecTrigger)
	{
		it->Update();;
	}
}

void cInteract::Render()
{
	for each (auto it in m_vecStuff)
	{
		it->Render();
	}
}
