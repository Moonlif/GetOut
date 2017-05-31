#include "stdafx.h"
#include "cInteract.h"
#include "cStuff.h"
#include "cTrigger.h"

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
	stuff->Setup(ITEM_KEY1, D3DXVECTOR3(0, 0, 0), true);
	m_vecStuff.push_back(stuff);

	stuff = new cStuff;
	stuff->Setup(ITEM_KEY1, D3DXVECTOR3(0, 2.0f, 0), true);
	m_vecStuff.push_back(stuff);
}

void cInteract::Update()
{
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
