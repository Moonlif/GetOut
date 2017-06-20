#include "stdafx.h"
#include "Monster.h"

Monster::Monster()
	: position(D3DXVECTOR3(0, 0, 0))
	, direction(D3DXVECTOR3(0, 0, 1))
	, rotY(0.0f)
	, monAni(ANIM_IDLE)
	, attackSphere(BoundingShere(D3DXVECTOR3(0, 0, 0), 2.0f))
	, attackSphereMesh(NULL)
{
}
Monster::~Monster()
{
	SAFE_RELEASE(attackSphereMesh);
	SAFE_DELETE(monster);
}

void Monster::Setup(D3DXVECTOR3 pos, char* szFolder, char* szFile)
{
	position = pos;

	monster = new SkinnedMesh(szFolder, szFile);
	monster->SetRotation(rotY);
	monster->SetPosition(position);
	monster->SetAnimationIndex(3);
	monster->SetSpeed(0.0f);
	monster->SetSize(7.6f);

	attackSphere.radius = 2.0f;
	attackSphere.center = position + D3DXVECTOR3(0,0,0);
	//D3DXCreateSphere(g_pD3DDevice, attackSphere.radius, 16, 8, &attackSphereMesh, NULL);
}
void Monster::Update()
{
	attackSphere.center = position;

	switch (monAni)
	{
	case ANIM_IDLE:
		monster->SetAnimationIndex(3);
		break;
	case ANIM_WALK:
		monster->SetAnimationIndex(2);
		break;
	case ANIM_ATTACK:
		monster->SetAnimationIndex(1);
		break;
	case ANIM_DEATH:
		monster->SetAnimationIndex(0);
		break;
	}

	//몬스터 방향, 위치
	monster->SetRotation(rotY);
	monster->SetPosition(position);
	monster->SetDirection(direction);
}
void Monster::Render()
{
	if (monster) monster->UpdateAndRender();
}