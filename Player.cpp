#include "stdafx.h"
#include "Player.h"

Player::Player()
	: position(D3DXVECTOR3(0, 0, 4))
	, headPosition(D3DXVECTOR3(0, 0, 0))
	, direction(D3DXVECTOR3(0, 0, 1))
	, player(NULL)
	, player_Weapon(NULL)
	, playerType(MALE)
	, aniState(ANIM_IDLE)
{
}

Player::~Player()
{
	if (player) SAFE_DELETE(player);
	if (player_Weapon) SAFE_DELETE(player_Weapon);
}

void Player::Setup(PLAYER_TYPE type)
{
	playerType = type;

	if (playerType == MALE)
	{
		player = new SkinnedMesh("Male/", "Male.X");
		player_Weapon = new SkinnedMesh("Male_Weapon/", "Male_Weapon.X");

		player_Weapon->SetPosition(position);
		player_Weapon->SetAnimationIndex(3);
		player_Weapon->SetSpeed(0.0f);

		player_Weapon->SetSize(1.8f * 4.3f);
		player->SetSize(1.8f * 4.3f);
	}
	else if (playerType == FEMALE)
	{
		player = new SkinnedMesh("Female/", "Female.X");
		player->SetPosition(position);
		player->SetAnimationIndex(3);
		player->SetSpeed(0.0f);
		player->SetSize(1.0f * 4.0f);
	}

}

void Player::Update(cMap* pMap)
{
	D3DXVECTOR3 vPosition = position;

	switch (aniState)
	{
	case ANIM_IDLE:
		if (playerType == MALE_WEAPON) player_Weapon->SetAnimationIndex(3);
		else player->SetAnimationIndex(3);
		break;
	case ANIM_WALK:
		if (playerType == MALE_WEAPON) player_Weapon->SetAnimationIndex(2);
		else player->SetAnimationIndex(2);
		break;
	case ANIM_ATTACK:
		if (playerType == MALE_WEAPON) player_Weapon->SetAnimationIndex(1);
		else player->SetAnimationIndex(1);
		break;
	case ANIM_DEATH:
		if (playerType == MALE_WEAPON) player_Weapon->SetAnimationIndex(0);
		else player->SetAnimationIndex(0);
		break;
	}

	if (g_pKeyManager->isStayKeyDown('W'))
	{
		if (playerType == MALE_WEAPON)
		{
			aniState = ANIM_WALK;
			vPosition -= (player_Weapon->GetDirection() * 2.0f * g_pTimeManager->GetElapsedTime());
		}
		else
		{
			aniState = ANIM_WALK;
			vPosition -= (player->GetDirection() * 2.0f * g_pTimeManager->GetElapsedTime());
		}
		
	}
	else if (g_pKeyManager->isStayKeyDown('S'))
	{
		if (playerType == MALE_WEAPON)
		{
			aniState = ANIM_WALK;
			vPosition += (player_Weapon->GetDirection() * 2.0f * g_pTimeManager->GetElapsedTime());
		}
		else
		{
			aniState = ANIM_WALK;
			vPosition += (player->GetDirection() * 2.0f * g_pTimeManager->GetElapsedTime());
		}
	}
	else
	{
		if (playerType == MALE_WEAPON) aniState = ANIM_IDLE;
		else aniState = ANIM_IDLE;
	}
	
	//<< 무기장착 테스트용
	if (g_pKeyManager->isOnceKeyDown('C') && (playerType == MALE || playerType == MALE_WEAPON))
	{
		if (playerType == MALE)
		{
			playerType = MALE_WEAPON;
		}
		else if (playerType == MALE_WEAPON)
		{
			playerType = MALE;
		}
	}
	//:>>

	/*if (surfaceData)
	{
		position = surfaceData;
	}*/

	//<< 테스트용
	position = vPosition; 
	//>>

	if (playerType == MALE_WEAPON)
	{
		player_Weapon->SetDirection(direction);
		player_Weapon->SetPosition(position);
	}
	else
	{
		player->SetDirection(direction);
		player->SetPosition(position);
	}

	//머리위치(카메라 위치)
	if(playerType == FEMALE) headPosition = position + D3DXVECTOR3(0, 1.0f, 0);
	else headPosition = position + D3DXVECTOR3(0, 1.2f, 0);
}

void Player::Update(D3DXVECTOR3 pos, D3DXVECTOR3 dir, animationState ani, cMap* pMap)
{
	D3DXVECTOR3 vPosition = pos;

	aniState = ani;

	switch (aniState)
	{
	case ANIM_IDLE:
		if (playerType == MALE_WEAPON) player_Weapon->SetAnimationIndex(3);
		else player->SetAnimationIndex(3);
		break;
	case ANIM_WALK:
		if (playerType == MALE_WEAPON) player_Weapon->SetAnimationIndex(2);
		else player->SetAnimationIndex(2);
		break;
	case ANIM_ATTACK:
		if (playerType == MALE_WEAPON) player_Weapon->SetAnimationIndex(1);
		else player->SetAnimationIndex(1);
		break;
	case ANIM_DEATH:
		if (playerType == MALE_WEAPON) player_Weapon->SetAnimationIndex(0);
		else player->SetAnimationIndex(0);
		break;
	}

	if (playerType == MALE_WEAPON)
	{
		player_Weapon->SetDirection(dir);
		player_Weapon->SetPosition(pos);
	}
	else
	{
		player->SetDirection(dir);
		player->SetPosition(pos);
	}
}

void Player::Render()
{
	if (playerType == MALE_WEAPON)
	{
		if (player_Weapon) player_Weapon->UpdateAndRender();
	}
	else
	{
		if (player) player->UpdateAndRender();
	}
}

bool Player::GetHeight(IN float x, OUT float & y, IN float z, cMap * map)
{
	{
		D3DXVECTOR3 vRayPos(x, 1000, z);
		D3DXVECTOR3 vRayDir(0, -1, 0);
		for (size_t i = 0; i < map->getSurface()->GetVecVertex().size(); i += 3) {
			float u, v, f;

			if (D3DXIntersectTri(
				&map->getSurface()->GetVecVertex()[i + 0],
				&map->getSurface()->GetVecVertex()[i + 1],
				&map->getSurface()->GetVecVertex()[i + 2],
				&vRayPos,
				&vRayDir,
				&u,
				&v,
				&f
			)) {
				y = 1000 - f;
				return true;
			}
		}
		return false;
	}
}
