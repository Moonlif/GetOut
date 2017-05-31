#include "stdafx.h"
#include "cStuff.h"

#include "cMtlTex.h"

cStuff::cStuff()
	: m_eCode(ITEM_KEY1)
	, m_fSize(0.0f)
	, m_vPosition(0, 0, 0)
	, m_sName("NONE")
	, m_pMesh(NULL)
	, m_IsOnMap(true)
{
}


cStuff::~cStuff()
{
	SAFE_RELEASE(m_pMesh);
	for each (auto it in m_vecMtlTex)
	{
		SAFE_RELEASE(it);
	}
}

void cStuff::Setup(ItemCode code, D3DXVECTOR3 position, bool isOnMap)
{
	m_eCode = code;
	m_vPosition = position;
	m_IsOnMap = isOnMap;

	m_sName = g_pData->m_mapItemName[m_eCode];
	m_fSize = g_pData->m_mapItemSize[m_eCode];
	m_pMesh = g_pData->m_mapItemMesh[m_eCode];
	g_pData->m_mapItemMesh[m_eCode]->AddRef();
	m_vecMtlTex = g_pData->m_mapItemVecMtlTex[m_eCode];
	for (int i = 0; i < m_vecMtlTex.size(); ++i)
	{
		m_vecMtlTex[i]->AddRef();
	}
}

void cStuff::Update()
{
}

void cStuff::Render()
{
	if (m_IsOnMap == false) return;

	D3DXMATRIXA16 matWorld, matS, matT;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	matWorld = matS * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	for (int i = 0; i < m_vecMtlTex.size(); ++i)
	{
		g_pD3DDevice->SetMaterial(&m_vecMtlTex[i]->GetMaterial());
		g_pD3DDevice->SetTexture(0, m_vecMtlTex[i]->GetTexture());
		m_pMesh->DrawSubset(i);
	}

}
