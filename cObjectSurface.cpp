#include "stdafx.h"
#include "cObjectSurface.h"


cObjectSurface::cObjectSurface()
{
}


cObjectSurface::~cObjectSurface()
{

}

void cObjectSurface::AddSurface(D3DXVECTOR3 v, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3)
{

	ST_PC_VERTEX vertex;
	vertex.p = v;
	vecVertex.push_back(vertex);
	vertex.p = v1;
	vecVertex.push_back(vertex);

	vertex.p = v2;
	vecVertex.push_back(vertex);
	vertex.p = v;
	vecVertex.push_back(vertex);

	vertex.p = v2;
	vecVertex.push_back(vertex);
	vertex.p = v3;
	vecVertex.push_back(vertex);

}


void cObjectSurface::RenderSurface()
{

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DXMATRIXA16 matS, matWorld;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matS, 6, 6, 6);
	matWorld = matS;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		vecVertex.size() / 3,
		&vecVertex[0],
		sizeof(ST_PC_VERTEX));


}