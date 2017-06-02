#include "stdafx.h"
#include "cStuff.h"

#include "cMtlTex.h"

cStuff::cStuff()
	: m_eCode(ITEM_NONE)
	, m_fRadius(0.0f)
	, m_fScaling(0.0f)
	, m_vPosition(0, 0, 0)
	, m_sName("NONE")
	, m_pMesh(NULL)
	, m_IsOnMap(true)
	, m_pMeshSphere(NULL)
{
}


cStuff::~cStuff()
{
	SAFE_RELEASE(m_pMesh);
	for each (auto it in m_vecMtlTex)
	{
		SAFE_RELEASE(it);
	}

	SAFE_RELEASE(m_pMeshSphere);
}

void cStuff::Setup(ItemCode code, D3DXVECTOR3 position, bool isOnMap)
{
	m_eCode = code;
	m_vPosition = position;
	m_IsOnMap = isOnMap;

	m_sName = g_pData->m_mapItemName[m_eCode];
	m_fRadius = g_pData->m_mapItemRadius[m_eCode];
	m_fScaling = g_pData->m_mapItemScaling[m_eCode];
	if (g_pData->m_mapItemMesh.find(m_eCode)->second != NULL)
	{
		m_pMesh = g_pData->m_mapItemMesh[m_eCode];
		g_pData->m_mapItemMesh[m_eCode]->AddRef();
	}
	if (g_pData->m_mapItemVecMtlTex.find(m_eCode) != g_pData->m_mapItemVecMtlTex.end())
	{
		m_vecMtlTex = g_pData->m_mapItemVecMtlTex[m_eCode];
		for (int i = 0; i < m_vecMtlTex.size(); ++i)
		{
			m_vecMtlTex[i]->AddRef();
		}
	}

	D3DXCreateSphere(g_pD3DDevice, m_fRadius, 10, 10, &m_pMeshSphere, NULL);
}

void cStuff::Update()
{
}

void cStuff::Render()
{
	if (m_IsOnMap == false) return;

	if (g_bDebug)
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}

	D3DXMATRIXA16 matWorld, matS, matT;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS, m_fScaling, m_fScaling, m_fScaling);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	matWorld = matS * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	for (int i = 0; i < m_vecMtlTex.size(); ++i)
	{
		g_pD3DDevice->SetMaterial(&m_vecMtlTex[i]->GetMaterial());
		g_pD3DDevice->SetTexture(0, m_vecMtlTex[i]->GetTexture());
		m_pMesh->DrawSubset(i);
	}

	if (g_bDebug)
	{
		//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		D3DXMATRIXA16 matDebug;
		D3DXMatrixTranslation(&matDebug, m_vPosition.x, m_vPosition.y, m_vPosition.z);

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matDebug);
		m_pMeshSphere->DrawSubset(0);

		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}
