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
	stuff->Setup((StuffCode)1, D3DXVECTOR3(0, 0, 0), true);
	m_vecStuff.push_back(stuff);

	stuff = new cStuff;
	stuff->Setup(STUFF_BOX1, D3DXVECTOR3(0, 5.0f, 0), true);
	m_vecStuff.push_back(stuff);

	stuff = new cStuff;
	stuff->Setup(STUFF_KEY1, D3DXVECTOR3(5.0f, 2.0f, 0), true);
	m_vecStuff.push_back(stuff);
}

void cInteract::Update()
{
	//picking
	cRay Ray = cRay::RayAtWorldSpace(g_ptMouse.x, g_ptMouse.y);
	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
	{
		for each(auto it in m_vecStuff)
		{
			if (Ray.IsPicked(it->GetPosition(), it->GetRadius()))
			{
				//switch (it->GetStuffCode())
				//{
				//case ITEM_BASEMENT_JAILKEY:
				//{
				//	int a = 0;
				//}
				//	break;
				//}
		
			}
		}
	}

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
