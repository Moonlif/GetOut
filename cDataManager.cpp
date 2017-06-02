#include "stdafx.h"
#include "cDataManager.h"
#include "cMtlTex.h"

#include "cObjLoader.h"

cDataManager::cDataManager()
	:m_pFont(NULL)
{
}


cDataManager::~cDataManager()
{
}

void cDataManager::Setup()
{
	//Using by Interaction 
	//{
	//	cObjLoader loader;

	//	m_mapItemName[ITEM_KEY1] = "KEY1";
	//	m_mapItemSize[ITEM_KEY1] = 0.5f;
	//	m_mapItemMesh[ITEM_KEY1] = loader.LoadMesh(m_mapItemVecMtlTex[ITEM_KEY1], "interactObj", "box.obj");
	//}

	g_pFontManager->CreateFont2D(m_pFont, 30, 30, 100, "±¼¸²Ã¼");
}

void cDataManager::Destroy()
{
	for each (auto it in m_mapItemMesh)
	{
		SAFE_RELEASE(it.second);
	}

	for each(auto it in m_mapItemVecMtlTex)
	{
		for (int i = 0; i < it.second.size(); i++)
		{
			SAFE_RELEASE(it.second[i]);
		}
	}

	SAFE_RELEASE(m_pFont);
}

void cDataManager::Chat(string Text)
{
	m_listChat_SEND.push_back(Text);
}

string cDataManager::GetText()
{
	if (m_listChat_SEND.empty())
	{
		string size;
		size = m_listChat_SEND.size();
		return size;
	}

	string Text = m_listChat_SEND.front();
	m_listChat_SEND.pop_front();
	return Text;
}

void cDataManager::Render(LPD3DXSPRITE pSprite)
{
	int x = 20, y = 30;
	RECT rc;
	SetRect(&rc, x, y, x + 1, y);
	string Text = to_string(m_listChat_RECV.size());
	m_pFont->DrawTextA(pSprite, Text.c_str(), 10, &rc, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(0, 0, 0));
}
