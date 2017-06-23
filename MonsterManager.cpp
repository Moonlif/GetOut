#include "stdafx.h"
#include "MonsterManager.h"

MonsterManager::MonsterManager()
{
	m_vecMonster.clear();
}
MonsterManager::~MonsterManager()
{
	m_vecMonster.clear();
}

void MonsterManager::Update()
{
	for (auto iter = m_vecMonster.begin(); iter != m_vecMonster.end(); ++iter)
	{
		(*iter)->Update();
	}
}

void MonsterManager::Render()
{
	for (auto iter = m_vecMonster.begin(); iter != m_vecMonster.end(); ++iter)
	{
		(*iter)->Render();
	}
}

void MonsterManager::CreateMonster(D3DXVECTOR3 pos, char* szFolder, char* szFile)
{
	Monster* tempMonster = new Monster;
	tempMonster->Setup(pos, szFolder, szFile);
	m_vecMonster.push_back(tempMonster);
}