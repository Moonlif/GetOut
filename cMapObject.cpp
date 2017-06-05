#include "stdafx.h"
#include "cMapObject.h"
#include "cObjLoader.h"
#include "cGroup.h"

cMapObject::cMapObject()
{
	m_vecGroup.clear();
}


cMapObject::~cMapObject()
{
	//17.05.30 ÃÖÁøÈ£
	for each(auto p in m_vecGroup)
	{
		SAFE_DELETE(p);
	}
}

void cMapObject::Setup()
{
	cObjLoader loadMesh;
	loadMesh.Load(m_vecGroup, "obj", "cs_office.obj");
}

void cMapObject::Render()
{
	D3DXMATRIXA16 matWorld, matS, matR, matT;
	D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);
	//D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F); 
	D3DXMatrixTranslation(&matT, 0, 0, 0);
	matWorld = matS * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	for each(auto p in m_vecGroup)
	{
		p->Render();
	}
}
