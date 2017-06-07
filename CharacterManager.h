#pragma once
#include "Player.h"

class CharacterManager
{

private:
	Player* m_p1Player;
	Player* m_p2Player;

public:
	void Setup();
	void Update();
	void Render();

	CharacterManager();
	~CharacterManager();

	D3DXVECTOR3& GetTargetPos();
};

