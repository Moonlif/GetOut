#include "stdafx.h"
#include "Monster.h"

Monster::Monster()
	: position(D3DXVECTOR3(0, 0, 0))
	, direction(D3DXVECTOR3(0, 0, 1))
	, rotY(0.0f)
	, monAni(ANIM_DEATH)
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

	if(monAni = ANIM_WALK) moveMonster();

	//몬스터 방향, 위치
	monster->SetRotation(rotY);
	monster->SetPosition(position);
	monster->SetDirection(direction);
}
void Monster::Render()
{
	if (monster) monster->UpdateAndRender();
}

void Monster::moveMonster()
{
	rotY = GetAngle(position, g_pData->Get1PPosition());

	direction = position - g_pData->Get1PPosition();
	D3DXVec3Normalize(&direction, &direction);

	position -= (direction * 8.0f * g_pTimeManager->GetElapsedTime());
	monster->SetPosition(position);
}

float Monster::GetAngle(D3DXVECTOR3& myPosition, D3DXVECTOR3& targetPosition)
{
	D3DXVECTOR3 a(0, 0, 1);
	D3DXVECTOR3 b = myPosition - targetPosition;

	float aLength = D3DXVec3Length(&a);
	float bLength = D3DXVec3Length(&b);
	float dot = D3DXVec3Dot(&a, &b);

	D3DXVECTOR3 cross;
	D3DXVec3Cross(&cross, &a, &b);
	if (cross.y < 0)
	{
		dot *= -1;
	}

	float angle = acos(dot / (aLength * bLength));

	D3DXVECTOR3 c(1, 0, 0);
	bool over180 = false;
	if (D3DXVec3Dot(&b, &c) < 0.0f)
	{
		over180 = true;
	}

	if (over180)
	{
		angle += D3DX_PI;
	}

	return angle;
}