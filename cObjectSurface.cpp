#include "stdafx.h"
#include "cObjectSurface.h"


cObjectSurface::cObjectSurface()
{
}


cObjectSurface::~cObjectSurface()
{
	
}
/*==========================================================================
Summary: 오브젝트들에 따른 이동제한을 걸기 위한 바닥을 벡터에 넣는 함수 
Parameters:
[in] v - 바닥이 만들어지는 벡터
[in] v1 - 바닥이 만들어지는 벡터
[in] v2 - 바닥이 만들어지는 벡터
[in] floor - 사각형이 만들어지는 층
Returns:
Worker: 최진호
==========================================================================*/
void cObjectSurface::AddSurface(D3DXVECTOR3 v, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, int floor)
{
	ObjectSurface vertex;
	vertex.floor = floor;
	vertex.point = v;
	vecVertex.push_back(vertex);
	vertex.point = v1;
	vecVertex.push_back(vertex);

	vertex.point = v2;
	vecVertex.push_back(vertex);
	vertex.point = v;
	vecVertex.push_back(vertex);

	vertex.point = v2;
	vecVertex.push_back(vertex);
	vertex.point = v3;
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
		&vecVertex[0].point,
		sizeof(ST_PC_VERTEX));
}