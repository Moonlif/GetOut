#include "stdafx.h"
#include "cUIMesh.h"
#include "SkinnedMesh.h"

cUIMesh::cUIMesh()
	:m_pMesh(NULL)
{


}

cUIMesh::cUIMesh(eMESHTYPE meshType, D3DXVECTOR3 pos)
	:m_pMesh(NULL)
	, m_pSkinnedMesh(NULL)
{
	m_eType = meshType;
	m_vPosition = pos;
	switch (meshType)
	{
	case cUIMesh::BOX:
		D3DXCreateBox(g_pD3DDevice, 1, 1, 1, &m_pMesh, NULL);
		break;
	case cUIMesh::SPHERE:
		D3DXCreateSphere(g_pD3DDevice, 0.5f, 10, 10, &m_pMesh, NULL);
		break;
	case cUIMesh::MALE:
		m_pSkinnedMesh = new SkinnedMesh("Male/", "Male.X");
		m_pSkinnedMesh->SetAnimationIndex(3);
		m_pSkinnedMesh->SetSpeed(0.0f);
		m_pSkinnedMesh->SetSize(1.7f);
		m_pSkinnedMesh->SetPosition(m_vPosition);
		break;
	case cUIMesh::FEMALE:
		m_pSkinnedMesh = new SkinnedMesh("Female/", "Female.X");
		m_pSkinnedMesh->SetAnimationIndex(3);
		m_pSkinnedMesh->SetSpeed(0.0f);
		m_pSkinnedMesh->SetSize(1.2f);
		m_pSkinnedMesh->SetPosition(m_vPosition);
		break;
	default:
		break;
	}

	

	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));

	m_stMtl.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	m_stMtl.Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

	/*playerType = type;

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
	else if (playerType == FEMALE) player = new SkinnedMesh("Female/", "Female.X");

	player->SetPosition(position);
	player->SetAnimationIndex(3);
	player->SetSpeed(0.0f);*/
}


cUIMesh::~cUIMesh()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_DELETE(m_pSkinnedMesh);
}

void cUIMesh::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	if (m_eType == eMESHTYPE::BOX || m_eType == eMESHTYPE::SPHERE)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		g_pD3DDevice->SetMaterial(&m_stMtl);
		m_pMesh->DrawSubset(0);
	}
	else
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		m_pSkinnedMesh->UpdateAndRender();
	}
	cUIObject::Render(pSprite);
}
