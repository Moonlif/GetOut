#include "stdafx.h"
#include "CharacterManager.h"


CharacterManager::CharacterManager()
	: m_p1Player(NULL)
	, m_p2Player(NULL)
{
}

CharacterManager::~CharacterManager()
{
	SAFE_DELETE(m_p1Player);
	SAFE_DELETE(m_p2Player);
}

void CharacterManager::Setup()
{
	m_p1Player = new Player;
	m_p1Player->Setup(MALE);
	m_p1Player->SetPosition(D3DXVECTOR3(-30, 0, 18));
	m_p2Player = new Player;
	m_p2Player->Setup(FEMALE);
	m_p2Player->SetPosition(D3DXVECTOR3(-32, 0, 10));

	g_pSocketmanager->SetManPlayer(m_p1Player);
	g_pSocketmanager->SetWomanPlayer(m_p2Player);
}

void CharacterManager::Update(cMap* cmap)
{
	static bool once = true;

	if (g_pData->GetIsStartedGame() && g_pData->m_nPlayerNum1P == 1)
	{
		if (once)
		{
			g_pData->m_vPosition2P = D3DXVECTOR3(-32, 0, 10);
			once = false;
		}
		if (m_p1Player)
		{
			m_p1Player->Update(cmap);
			m_p1Player->SetDraw(false);
		}
		if (m_p2Player) m_p2Player->Update(g_pData->m_vPosition2P,
			g_pData->m_vRotation2P,
			g_pData->m_eAnimState2P,
			NULL);
	}
	else if (g_pData->GetIsStartedGame() && g_pData->m_nPlayerNum1P == 2)
	{
		if (once)
		{
			g_pData->m_vPosition2P = D3DXVECTOR3(-30, 0, 18);
			once = false;
		}
		if (m_p2Player)
		{
			m_p2Player->Update(cmap);
			m_p2Player->SetDraw(false);
		}
		if (m_p1Player) m_p1Player->Update(g_pData->m_vPosition2P,
			g_pData->m_vRotation2P,
			g_pData->m_eAnimState2P,
			NULL);
	}
}
void CharacterManager::Render()
{
	if (g_pData->GetIsStartedGame() && m_p1Player) m_p1Player->Render();
	if (g_pData->GetIsStartedGame() && m_p2Player) m_p2Player->Render();
}

D3DXVECTOR3& CharacterManager::GetTargetPos()
{
	if (g_pData->m_nPlayerNum1P == 1) return m_p1Player->GetheadPosition();
	else if (g_pData->m_nPlayerNum1P == 2) return m_p2Player->GetheadPosition();
}