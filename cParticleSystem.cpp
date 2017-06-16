#include "stdafx.h"
#include "cParticleSystem.h"


cParticleSystem::cParticleSystem()
	: m_pTexture(NULL)
	, m_pPosition(NULL)
{
}


cParticleSystem::~cParticleSystem()
{
	SAFE_DELETE(m_pPosition);
}

DWORD FtoDw(float f)
{
	return *((DWORD*)&f);
}

void cParticleSystem::Setup(int vertexSize, float radius, D3DXCOLOR vertexColor, float minSize, float maxSize, char* textureFile, D3DXVECTOR3* position)
{
	m_vecParticleVertex.resize(vertexSize);
	m_fRadius = radius;
	m_stColor = vertexColor;
	m_fMinSize = minSize;
	m_fMaxSize = maxSize;

	for (int i = 0; i < m_vecParticleVertex.size(); ++i)
	{
		float fRadius = RND->getFloatFromTo(0.0f, m_fRadius);
		m_vecParticleVertex[i].p = D3DXVECTOR3(0, 0, fRadius);

		D3DXVECTOR3 vAngle = D3DXVECTOR3(D3DXToRadian(rand() % 3600 / 10.0f), D3DXToRadian(rand() % 3600 / 10.0f), D3DXToRadian(rand() % 3600 / 10.0f));
		D3DXMATRIX matRX, matRY, matRZ, matWorld;
		D3DXMatrixRotationX(&matRX, vAngle.x);
		D3DXMatrixRotationY(&matRY, vAngle.y);
		D3DXMatrixRotationZ(&matRZ, vAngle.z);
		matWorld = matRX * matRY * matRZ;

		D3DXVec3TransformCoord(&m_vecParticleVertex[i].p, &m_vecParticleVertex[i].p, &matWorld);
		m_vecParticleVertex[i].c = vertexColor;
	}
	m_pTexture = g_pTextureManager->GetTexture(textureFile);
	m_pPosition = position;

	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, FtoDw(5.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.0f));

	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);	//can use texture
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(minSize));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MAX, FtoDw(maxSize));

	//alpha option
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
}

void cParticleSystem::Update()
{
	static int nAlpha = 0;
	static int nDelta = 2;

	nAlpha += nDelta;
	if (nAlpha > 255)
	{
		nAlpha = 255;
		nDelta *= -1;
	}

	if (nAlpha < 0)
	{
		nAlpha = 0;
		nDelta *= -1;
	}

	if (nAlpha == 0)
	{
		for (int i = 0; i < m_vecParticleVertex.size(); ++i)
		{
			float fRadius = RND->getFloatFromTo(0.0f, m_fRadius);
			m_vecParticleVertex[i].p = D3DXVECTOR3(0, 0, fRadius);

			D3DXVECTOR3 vAngle = D3DXVECTOR3(D3DXToRadian(rand() % 3600 / 10.0f), D3DXToRadian(rand() % 3600 / 10.0f), D3DXToRadian(rand() % 3600 / 10.0f));
			D3DXMATRIX matRX, matRY, matRZ, matWorld;
			D3DXMatrixRotationX(&matRX, vAngle.x);
			D3DXMatrixRotationY(&matRY, vAngle.y);
			D3DXMatrixRotationZ(&matRZ, vAngle.z);
			matWorld = matRX * matRY * matRZ;

			D3DXVec3TransformCoord(&m_vecParticleVertex[i].p, &m_vecParticleVertex[i].p, &matWorld);
		}
	}

	m_stColor.a = nAlpha;
	int a, r, g, b;
	a = (int)m_stColor.a;
	r = (int)m_stColor.r;
	g = (int)m_stColor.g;
	b = (int)m_stColor.b;
	for (int i = 0; i < m_vecParticleVertex.size(); ++i)
	{
		if (i % 2 == 0)
		{
			m_vecParticleVertex[i].c = D3DCOLOR_ARGB(255 - a, r, g, b);
		}
		else m_vecParticleVertex[i].c = D3DCOLOR_ARGB(a, r, g, b);
	}
}

void cParticleSystem::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(m_fMinSize));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MAX, FtoDw(m_fMaxSize));

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&matWorld, m_pPosition->x, m_pPosition->y, m_pPosition->z);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, m_pTexture);

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_POINTLIST, m_vecParticleVertex.size(), &m_vecParticleVertex[0], sizeof(ST_PC_VERTEX));

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}
