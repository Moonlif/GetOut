#include "stdafx.h"
#include "cUIMesh.h"
#include "SkinnedMesh.h"

cUIMesh::cUIMesh()
	:m_pMesh(NULL)
	, m_nCountAnim(0.0f)
{


}

cUIMesh::cUIMesh(eMESHTYPE meshType, D3DXVECTOR3 pos)
	:m_pMesh(NULL)
	, m_pSkinnedMesh(NULL)
	, m_nCountAnim(0.0f)
{
	//세팅값 저장
	m_eType = meshType;
	m_vPosition = pos;

	//메쉬타입에 따른 메쉬 생성
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
		m_pSkinnedMesh->SetAnimationIndexBlend(1);
		m_pSkinnedMesh->SetSpeed(0.0f);
		m_pSkinnedMesh->SetSize(1.7f);
		m_pSkinnedMesh->SetPosition(m_vPosition);
		break;
	case cUIMesh::FEMALE:
		m_pSkinnedMesh = new SkinnedMesh("Female/", "Female.X");
		m_pSkinnedMesh->SetAnimationIndexBlend(1);
		m_pSkinnedMesh->SetSpeed(0.0f);
		m_pSkinnedMesh->SetSize(1.2f);
		m_pSkinnedMesh->SetPosition(m_vPosition);
		break;
	default:
		break;
	}

	
	//머터리얼 설정
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	m_stMtl.Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
}


cUIMesh::~cUIMesh()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_DELETE(m_pSkinnedMesh);
}

void cUIMesh::Update()
{
	if (m_isHidden)
	{
		//히든시 애니메이션, 애니메이션 카운트값 
		m_nCountAnim = 0;
		m_pSkinnedMesh->SetAnimationIndexBlend(1);
		return;
	}

	if (m_eType == cUIMesh::MALE)
	{
		if (m_nCountAnim >= 2.0f)
		{
			//액션 애니메이션 후 아이들값으로 변경
			m_pSkinnedMesh->SetAnimationIndexBlend(3);
		}
		//애니 카운트 더해주기
		if(!m_isHidden)m_nCountAnim += g_pTimeManager->GetElapsedTime();
	}
	else if (m_eType == cUIMesh::FEMALE)
	{
		if (m_nCountAnim >= 1.0f)
		{
			//액션 애니메이션 후 아이들값으로 변경
			m_pSkinnedMesh->SetAnimationIndexBlend(3);
		}
		//애니 카운트 더해주기
		if (!m_isHidden)m_nCountAnim += g_pTimeManager->GetElapsedTime();
	}

	cUIObject::Update();
}

void cUIMesh::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	//메쉬 타입에 따른 렌더
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
