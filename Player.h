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
	D3DXVECTOR3		position = D3DXVECTOR3(0,0,0);
	D3DXVECTOR3		headPosition = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3		sightTarget = D3DXVECTOR3(0, 0, 0);
	float			rotationY = 0.0f;
	D3DXVECTOR3		direction = D3DXVECTOR3(0, 0, 1);

	D3DXMATRIXA16	worldMat;

	SkinnedMesh* player = nullptr;
	SkinnedMesh* player_Weapon = nullptr;

	PLAYER_TYPE playerType;

	BoundingShere baseSphere = BoundingShere(D3DXVECTOR3(0, 0, 0), 0.5f);
	LPD3DXMESH baseSphereMesh = nullptr;
	D3DXMATRIXA16 baseSphereLocal;

	bool showBoundingSphere = false;

public:
	Player();
	~Player();

	void Setup(PLAYER_TYPE type, cMap* map);
	void Update();
	void Render();

	inline D3DXVECTOR3& GetPosition() { return position; }
	inline D3DXVECTOR3& GetHeadPosition() { return headPosition; }
	inline D3DXVECTOR3& GetSightTarget() { return sightTarget; }

	bool GetHeight(IN float x, OUT float & y, IN float z, cMap* map);
	

};

