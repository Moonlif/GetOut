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
	m_p2Player = new Player;
	m_p2Player->Setup(FEMALE);
}

void CharacterManager::Update()
{
	if (g_pData->GetIsStartedGame() && g_pData->m_nPlayerNum1P == 1)
	{
		if (m_p1Player) m_p1Player->Update(NULL);
		if (m_p2Player) m_p2Player->Update(g_pData->m_vPosition2P,
			g_pData->m_vRotation2P,
			g_pData->m_eAnimState2P,
			NULL);
	}
	else if (g_pData->GetIsStartedGame() && g_pData->m_nPlayerNum1P == 2)
	{
		if (m_p2Player) m_p2Player->Update(NULL);
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