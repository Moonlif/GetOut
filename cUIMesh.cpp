#include "stdafx.h"
#include "cUIMesh.h"


cUIMesh::cUIMesh()
	:m_pMesh(NULL)
{


}

cUIMesh::cUIMesh(eMESHTYPE meshType, D3DXVECTOR3 pos)
{
	switch (meshType)
	{
	case cUIMesh::BOX:
		D3DXCreateBox(g_pD3DDevice, 1, 1, 1, &m_pMesh, NULL);
		break;
	case cUIMesh::SPHERE:
		D3DXCreateSphere(g_pD3DDevice, 0.5f, 10, 10, &m_pMesh, NULL);
		break;
	case cUIMesh::OTHER:
		break;
	}

	m_vPosition = pos;
		

}


cUIMesh::~cUIMesh()
{
	SAFE_RELEASE(m_pMesh);
}

void cUIMesh::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	m_pMesh->DrawSubset(0);

	cUIObject::Render(pSprite);
}
