#pragma once
#include "SkinnedMesh.h"

class Monster
{
private:
	SYNTHESIZE(D3DXVECTOR3, position, position);
	SYNTHESIZE(float, rotY, rotY);
	D3DXVECTOR3		direction;

	animationState monAni;
	SkinnedMesh* monster;

	BoundingShere attackSphere;
	LPD3DXMESH attackSphereMesh;

public:
	Monster();
	~Monster();

	void Setup(D3DXVECTOR3 pos, char* szFolder, char* szFile);
	void Update();
	void Render();
};

