#include "stdafx.h"
#include "Player.h"
Player::Player()
	: position(D3DXVECTOR3(0, 0, 0))
	, checkPosition(D3DXVECTOR3(0, 0, 0))
	, headPosition(D3DXVECTOR3(0, 0, 0))
	, direction(D3DXVECTOR3(0, 0, 1))
	, rotY(0.0f)
	, isDraw(true)
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
		player->SetPosition(position);
		player->SetAnimationIndexBlend(3);
		player->SetSpeed(0.0f);
		player->SetSize(7.6f);

		player_Weapon = new SkinnedMesh("Male_Weapon/", "Male_Weapon.X");
		player_Weapon->SetPosition(position);
		player_Weapon->SetAnimationIndex(3);
		player_Weapon->SetSpeed(0.0f);
		player_Weapon->SetSize(7.6f);
	}
	else if (playerType == FEMALE)
	{
		player = new SkinnedMesh("Female/", "Female.X");
		player->SetPosition(position);
		player->SetAnimationIndex(3);
		player->SetSpeed(0.0f);
		player->SetSize(4.0f);
	}
}

void Player::Update(cMap* pMap)
{
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

	pMap->GetMovePossible(position.x, position.y, position.z);
	//캐릭터 이동관련 함수
	MoveCharacter(pMap);
	//벽과 충돌중인지 체크
	CheckPosition(pMap);

	//채팅켜지면 IDLE 상태로 변경
	if (g_pData->GetIsOnChat())
	{
		if (playerType == MALE_WEAPON) aniState = ANIM_IDLE;
		else aniState = ANIM_IDLE;
	}
	//이동키 해제시 IDLE 상태로 변경
	if (!g_pKeyManager->isStayKeyDown('W') && !g_pKeyManager->isStayKeyDown('S') &&
		!g_pKeyManager->isStayKeyDown('A') && !g_pKeyManager->isStayKeyDown('D'))
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

	//서버전송용
	g_pData->m_vPosition1P = position;
	g_pData->m_eAnimState1P = aniState;

	//캐릭터 방향
	rotY = g_pData->m_vRotation1P;

	if (playerType == MALE_WEAPON)
	{
		player_Weapon->SetRotation(rotY);
		player_Weapon->SetPosition(position);
	}
	else
	{
		player->SetRotation(rotY);
		player->SetPosition(position);
	}

	//머리위치(카메라 위치)
	if (playerType == FEMALE) headPosition = position + D3DXVECTOR3(0, 6.0f, 0);
	else headPosition = position + D3DXVECTOR3(0, 7.2f, 0);
}

void Player::Update(D3DXVECTOR3 pos, float rot, animationState ani, cMap* pMap)
{
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
		player_Weapon->SetRotation(rot);
		player_Weapon->SetPosition(pos);
	}
	else
	{
		player->SetRotation(rot);
		player->SetPosition(pos);
	}
}

void Player::Render()
{
	if (isDraw)
	{
		if (player) player->SetRender(true);
		if (player_Weapon) player_Weapon->SetRender(true);
	}
	else
	{
		if (player) player->SetRender(false);
		if (player_Weapon) player_Weapon->SetRender(false);
	}

	if (playerType == MALE_WEAPON)
	{
		if (player_Weapon) player_Weapon->UpdateAndRender();
	}
	else
	{
		if (player) player->UpdateAndRender();
	}
}

void Player::MoveCharacter(cMap* pMap)
{
	float checkPoint = 2.0f;
	float moveSpeed = 1.5f;

	//채팅꺼진 상태에서만 작동
	if (!g_pData->GetIsOnChat())
	{
		//앞,뒤 이동
		if (g_pKeyManager->isStayKeyDown('W'))
		{
			if (playerType == MALE_WEAPON)
			{
				aniState = ANIM_WALK;
				checkPosition = position - (player_Weapon->GetDirection() * checkPoint * g_pTimeManager->GetElapsedTime());
				if (pMap->GetMovePossible(checkPosition.x, checkPosition.y, checkPosition.z))
				{
					position -= (player_Weapon->GetDirection() * moveSpeed * g_pTimeManager->GetElapsedTime());
				}
			}
			else
			{
				aniState = ANIM_WALK;
				checkPosition = position - (player->GetDirection() * checkPoint * g_pTimeManager->GetElapsedTime());
				if (pMap->GetMovePossible(checkPosition.x, checkPosition.y, checkPosition.z))
				{
					position -= (player->GetDirection() * moveSpeed * g_pTimeManager->GetElapsedTime());
				}
			}
		}
		else if (g_pKeyManager->isStayKeyDown('S'))
		{
			if (playerType == MALE_WEAPON)
			{
				aniState = ANIM_WALK;
				checkPosition = position + (player_Weapon->GetDirection() * checkPoint * g_pTimeManager->GetElapsedTime());
				if (pMap->GetMovePossible(checkPosition.x, checkPosition.y, checkPosition.z))
				{
					position += (player_Weapon->GetDirection() * moveSpeed * g_pTimeManager->GetElapsedTime());
				}
			}
			else
			{
				aniState = ANIM_WALK;
				checkPosition = position + (player->GetDirection() * checkPoint * g_pTimeManager->GetElapsedTime());
				if (pMap->GetMovePossible(checkPosition.x, checkPosition.y, checkPosition.z))
				{
					position += (player->GetDirection() * moveSpeed * g_pTimeManager->GetElapsedTime());
				}
			}
		}
		//좌,우 이동
		if (g_pKeyManager->isStayKeyDown('A'))
		{
			if (playerType == MALE_WEAPON)
			{
				aniState = ANIM_WALK;

				D3DXVECTOR3 m_vUp, m_vCross;
				m_vUp = D3DXVECTOR3(0, 1, 0);
				D3DXVec3Cross(&m_vCross, &player_Weapon->GetDirection(), &m_vUp);
				//D3DXVec3Normalize(&m_vCross, &m_vCross);

				checkPosition = position - (m_vCross * checkPoint * g_pTimeManager->GetElapsedTime());
				if (pMap->GetMovePossible(checkPosition.x, checkPosition.y, checkPosition.z))
				{
					position -= (m_vCross * moveSpeed * g_pTimeManager->GetElapsedTime());
				}
			}
			else
			{
				aniState = ANIM_WALK;

				D3DXVECTOR3 m_vUp, m_vCross;
				m_vUp = D3DXVECTOR3(0, 1, 0);
				D3DXVec3Cross(&m_vCross, &player->GetDirection(), &m_vUp);
				//D3DXVec3Normalize(&m_vCross, &m_vCross);

				checkPosition = position - (m_vCross * checkPoint * g_pTimeManager->GetElapsedTime());
				if (pMap->GetMovePossible(checkPosition.x, checkPosition.y, checkPosition.z))
				{
					position -= (m_vCross * moveSpeed * g_pTimeManager->GetElapsedTime());
				}
			}
		}
		else if (g_pKeyManager->isStayKeyDown('D'))
		{
			if (playerType == MALE_WEAPON)
			{
				aniState = ANIM_WALK;

				D3DXVECTOR3 m_vUp, m_vCross;
				m_vUp = D3DXVECTOR3(0, 1, 0);
				D3DXVec3Cross(&m_vCross, &player_Weapon->GetDirection(), &m_vUp);
				//D3DXVec3Normalize(&m_vCross, &m_vCross);

				checkPosition = position + (m_vCross * checkPoint * g_pTimeManager->GetElapsedTime());
				if (pMap->GetMovePossible(checkPosition.x, checkPosition.y, checkPosition.z))
				{
					position += (m_vCross * moveSpeed * g_pTimeManager->GetElapsedTime());
				}
			}
			else
			{
				aniState = ANIM_WALK;

				D3DXVECTOR3 m_vUp, m_vCross;
				m_vUp = D3DXVECTOR3(0, 1, 0);
				D3DXVec3Cross(&m_vCross, &player->GetDirection(), &m_vUp);
				//D3DXVec3Normalize(&m_vCross, &m_vCross);

				checkPosition = position + (m_vCross * checkPoint * g_pTimeManager->GetElapsedTime());
				if (pMap->GetMovePossible(checkPosition.x, checkPosition.y, checkPosition.z))
				{
					position += (m_vCross * moveSpeed * g_pTimeManager->GetElapsedTime());
				}
			}
		}
	}
}

void Player::CheckPosition(cMap* pMap)
{
	float checkPoint = 3.0f;

	checkPosition = position - (player->GetDirection() * checkPoint * g_pTimeManager->GetElapsedTime());
	if (!pMap->GetMovePossible(checkPosition.x, checkPosition.y, checkPosition.z))
	{
		g_pData->SetIsCollisionWall(true);
	}
	else if (pMap->GetMovePossible(checkPosition.x, checkPosition.y, checkPosition.z))
	{
		g_pData->SetIsCollisionWall(false);
	}
}