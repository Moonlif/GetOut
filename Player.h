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
	D3DXVECTOR3		checkPosition;
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3,	headPosition, headPosition)
	D3DXVECTOR3		direction;
	float			rotY;
	bool			isDraw;

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
	void SetPosition(D3DXVECTOR3 pos) { position = pos; }
	
	inline void SetDraw(bool is) { isDraw = is; }
	inline D3DXVECTOR3& GetDirection() { return direction; }
	void SetRotation(float fRotation) { rotY = fRotation; }

	void SetDirection(D3DXVECTOR3 dir) { direction = dir; }

	void MoveCharacter(cMap* pMap);
	//void CheckPosition(cMap* pMap);
};

