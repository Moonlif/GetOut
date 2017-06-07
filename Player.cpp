#include "stdafx.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
	SAFE_RELEASE(baseSphereMesh);

	if (player) SAFE_DELETE(player);
	if (player_Weapon) SAFE_DELETE(player_Weapon);
}

void Player::Setup(PLAYER_TYPE type, cMap* map)
{
	playerType = type;

	
	map->getSurface()->GetVecVertex();
	
	if (playerType == MALE)
	{
		player = new SkinnedMesh("Male/", "Male.X");
		player_Weapon = new SkinnedMesh("Male_Weapon/", "Male_Weapon.X");

		player_Weapon->SetPosition(position);
		player_Weapon->SetAnimationIndex(3);
		player_Weapon->SetSpeed(0.0f);
		
		player_Weapon->SetSize(1.8f);
		player->SetSize(1.8f);
	}
	else if(playerType == FEMALE) player = new SkinnedMesh("Female/", "Female.X");

	player->SetPosition(position);
	player->SetAnimationIndex(3);
	player->SetSpeed(0.0f);

	D3DXCreateSphere(g_pD3DDevice, 0.5f * player->GetSize(), 16, 16, &baseSphereMesh, nullptr);
}

void Player::Update()
{
	if (g_pKeyManager->isStayKeyDown('W'))
	{
		if (playerType == MALE_WEAPON)
		{
			player_Weapon->SetAnimationIndex(2);
			position -= (player_Weapon->GetDirection() * 2.0f * g_pTimeManager->GetElapsedTime());
		}
		else
		{
			player->SetAnimationIndex(2);
			position -= (player->GetDirection() * 2.0f * g_pTimeManager->GetElapsedTime());
		}
		
	}
	else if (g_pKeyManager->isStayKeyDown('S'))
	{
		if (playerType == MALE_WEAPON)
		{
			player_Weapon->SetAnimationIndex(2);
			position += (player_Weapon->GetDirection() * 2.0f * g_pTimeManager->GetElapsedTime());
		}
		else
		{
			player->SetAnimationIndex(2);
			position += (player->GetDirection() * 2.0f * g_pTimeManager->GetElapsedTime());
		}
	}
	else
	{
		if (playerType == MALE_WEAPON) player_Weapon->SetAnimationIndex(3);
		else player->SetAnimationIndex(3);
	}
	
	if (g_pKeyManager->isStayKeyDown('A'))
	{
		rotationY -= 0.05f;
	}
	else if (g_pKeyManager->isStayKeyDown('D'))
	{
		rotationY += 0.05f;
	}
	
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

	if (playerType == MALE_WEAPON)
	{
		player_Weapon->SetRotation(rotationY);
		player_Weapon->SetPosition(position);
	}
	else
	{
		player->SetRotation(rotationY);
		player->SetPosition(position);
	}

	//머리위치(카메라 위치)
	if(playerType == FEMALE) headPosition = position + D3DXVECTOR3(0, 1.0f, 0);
	else headPosition = position + D3DXVECTOR3(0, 1.2f, 0);

	//테스트용 구체
	baseSphere.center = position;
	if (baseSphereMesh)
	{
		D3DXMatrixIdentity(&baseSphereLocal);
		D3DXMATRIX baselocalRotation, baselocalranslation;
		D3DXMatrixRotationX(&baselocalRotation, D3DX_PI * 0.5f);
		D3DXMatrixTranslation(&baselocalranslation, baseSphere.center.x, baseSphere.center.y + 0.5f, baseSphere.center.z);
		baseSphereLocal *= (baselocalRotation * baselocalranslation);
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

	if (baseSphereMesh && showBoundingSphere)
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		g_pD3DDevice->SetTexture(0, nullptr);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &baseSphereLocal);
		baseSphereMesh->DrawSubset(0);
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}

bool Player::GetHeight(IN float x, OUT float & y, IN float z, cMap* map)
{
	{
		//D3DXVECTOR3 vRayPos(x, 1000, z);
		//D3DXVECTOR3 vRayDir(0, -1, 0);
		//for (size_t i = 0; i < map->getSurface()->GetVecVertex.size(); i += 3) {
		//	float u, v, f;

		//	if (D3DXIntersectTri(
		//		map->getSurface()->GetVecVertex[i + 0],
		//		map->getSurface()->GetVecVertex[i + 1],
		//		map->getSurface()->GetVecVertex[i + 2],
		//		&vRayPos,
		//		&vRayDir,
		//		&u,
		//		&v,
		//		&f
		//	)) {
		//		y = 1000 - f;
		//		return true;
		//	}
		//}
		return false;
	}
}
