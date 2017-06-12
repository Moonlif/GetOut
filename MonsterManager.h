#pragma once
#include "Monster.h"

class MonsterManager
{
private:
	vector<Monster*> m_vecMonster;

public:
	MonsterManager();
	~MonsterManager();

	void Setup();
	void Update();
	void Render();

	void CreateMonster(D3DXVECTOR3 pos, char* szFolder, char* szFile);
};

