#pragma once
#include "SkinnedMesh.h"
#include "cMap.h"

enum PLAYER_TYPE
{
	MALE = 0,
	MALE_WEAPON,
	FEMALE
};

class Player
{
private:
	D3DXVECTOR3		position;
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3,	headPosition, headPosition)
	D3DXVECTOR3		direction;
	float			rotY;

	SkinnedMesh* player;
	SkinnedMesh* player_Weapon;

	PLAYER_TYPE playerType;
	animationState aniState;

public:
	Player();
	~Player();

	void Setup(PLAYER_TYPE type);
	void Update(cMap* pMap);
	void Update(D3DXVECTOR3 pos, float rot, animationState ani, cMap* pMap);
	void Render();

	inline D3DXVECTOR3& GetPosition() { return position; }
	inline D3DXVECTOR3& GetDirection() { return direction; }

	void SetDirection(D3DXVECTOR3 dir) { direction = dir; }
	bool GetHeight(IN float x, OUT float & y, IN float z, cMap* map);
};

