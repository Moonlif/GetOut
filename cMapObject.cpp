#include "stdafx.h"
#include "cMapObject.h"


cMapObject::cMapObject()
{
	m_vecGroup.clear();
}


cMapObject::~cMapObject()
{
	//17.05.30 최진호
	for each(auto p in m_vecGroup)
	{
		SAFE_DELETE(p);
	}
}

void cMapObject::Setup(char* folder, char* fileName)
{
	cObjLoader loadMesh;
	loadMesh.Load(m_vecGroup, folder, fileName);
}



void cMapObject::Render(float size, float x, float y, float z)
{
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//알파테스트의 기준값을 0x80(10진수128)로 설정
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x80);
	//알파테스트의 기능(D3DRS_ALPHAFUNC)를
	//D3DCMP_GREATEREQUAL(알파값이 기준값보다 크거나 같으면 텍스쳐 출력)으로 설정
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	D3DXMATRIXA16 matWorld, matS, matR, matT;
	D3DXMatrixScaling(&matS, size, size, size);
	D3DXMatrixRotationY(&matR, -D3DX_PI); 
	D3DXMatrixTranslation(&matT, x, y, z);
	matWorld = matS * matT * matR;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	for each(auto p in m_vecGroup)
	{
		p->Render();
	}
}
