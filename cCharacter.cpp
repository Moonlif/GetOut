#include "stdafx.h"
#include "cCharacter.h"

#define GRAVITY_ACCEL 0.01f
#define EPSILON 0.1f

cCharacter::cCharacter()
	: m_vDirection(0, 0, 1)
	, m_vPosition(0, 0, 0)
	, m_vRotation(0, 0, 0)
	, m_IsMoving(false)
	, m_IsJumping(false)
	, m_jumpTime(0)
	, m_fGravity(0.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cCharacter::~cCharacter()
{
}

void cCharacter::Setup()
{
}

void cCharacter::Update(iMap* pMap)
{
	m_pMap = pMap;
	m_IsMoving = false;

	if (GetKeyState('A') & 0x8000)
	{
		m_vRotation.y -= 0.1f;
	}
	else if (GetKeyState('D') & 0x8000)
	{
		m_vRotation.y += 0.1f;
	}

	D3DXVECTOR3 vPosition = m_vPosition;
	if (GetKeyState('W') & 0x8000)
	{
		vPosition = m_vPosition + m_vDirection * 0.05f;
		m_IsMoving = true;
	}
	else if (GetKeyState('S') & 0x8000)
	{
		vPosition = m_vPosition - m_vDirection * 0.05f;
		m_IsMoving = true;
	}

	D3DXMATRIXA16 matR, matRX, matRY, matRZ;
	D3DXMatrixRotationX(&matRX, m_vRotation.x);
	D3DXMatrixRotationY(&matRY, m_vRotation.y);
	D3DXMatrixRotationZ(&matRZ, m_vRotation.z);
	matR = matRX * matRY * matRZ;

	if (pMap)
	{
		if (pMap->GetHeight(vPosition.x, vPosition.y, vPosition.z))
		{
			m_vPosition = vPosition;
		}
	}
	else m_vPosition = vPosition;

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = matR * matT;

	m_vDirection = D3DXVECTOR3(0, 0, -1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matRY);
	D3DXVec3Normalize(&m_vDirection, &m_vDirection);
}

void cCharacter::Render()
{
}

D3DXVECTOR3 & cCharacter::GetPosition()
{
	return m_vPosition;
}