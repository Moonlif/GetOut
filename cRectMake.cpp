#include "stdafx.h"
#include "cRectMake.h"


cRectMake::cRectMake()
	:m_pTexture(NULL)
{

}


cRectMake::~cRectMake()
{
	SAFE_RELEASE(m_pTexture);
}

void cRectMake::Setup(D3DXVECTOR3 v, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, char * szFile)
{
	// 2 3
	// 0 1
	ST_PNT_VERTEX _verTex;
	D3DXVECTOR3 n;
	D3DXVec3Normalize(&n, &n);
	_verTex.n = n;
	_verTex.t = D3DXVECTOR2(0, 0);
	_verTex.p = v;	m_vecBottomVertex.push_back(_verTex);
	_verTex.t = D3DXVECTOR2(0, 1.0f);
	_verTex.p = v1; m_vecBottomVertex.push_back(_verTex);

	_verTex.t = D3DXVECTOR2(1, 1.0f);
	_verTex.p = v2;	m_vecBottomVertex.push_back(_verTex);
	_verTex.t = D3DXVECTOR2(0, 0);
	_verTex.p = v;	m_vecBottomVertex.push_back(_verTex);

	_verTex.t = D3DXVECTOR2(1, 1.0f);
	_verTex.p = v2;	m_vecBottomVertex.push_back(_verTex);
	_verTex.t = D3DXVECTOR2(1, 0);
	_verTex.p = v3;	m_vecBottomVertex.push_back(_verTex);

	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	if (szFile)
		m_pTexture = g_pTextureManager->GetTexture(szFile);
}

void cRectMake::Render(int index)
{
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//알파테스트의 기준값을 0x80(10진수128)로 설정
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x80);
	//알파테스트의 기능(D3DRS_ALPHAFUNC)를
	//D3DCMP_GREATEREQUAL(알파값이 기준값보다 크거나 같으면 텍스쳐 출력)으로 설정
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DXMATRIXA16 matS, matWorld;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matS, 6, 6, 6);
	matWorld = matS;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTexture(index, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecBottomVertex.size() / 3,
		&m_vecBottomVertex[0],
		sizeof(ST_PNT_VERTEX));

	g_pD3DDevice->SetTexture(index, NULL);
}
