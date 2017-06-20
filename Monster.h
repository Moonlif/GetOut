#pragma once
#include "SkinnedMesh.h"

class Monster
{
private:
	SYNTHESIZE(D3DXVECTOR3, position, position);
	SYNTHESIZE(float, rotY, rotY);
	SYNTHESIZE(D3DXVECTOR3, direction, direction);
	SYNTHESIZE(animationState, monAni, monAni);

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

