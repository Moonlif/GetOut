#include "stdafx.h"
#include "cParticleSystem.h"


cParticleSystem::cParticleSystem()
	: m_pPosition(NULL)
	, m_nAlpha(0)
	, m_nDelta(0)
	, m_nAlphaCount(0)
	, m_nRepaetCount(0)
	, m_fRadius(0.0f)
	, m_fMinSize(0.0f)
	, m_fMaxSize(0.0f)
	, m_pTexture(NULL)
{
}


cParticleSystem::~cParticleSystem()
{
}

//float을 DWORD로 변경하는 함수
DWORD FtoDw(float f)
{
	return *((DWORD*)&f);
}

void cParticleSystem::Setup(eParticleType type, D3DXVECTOR3* position, int delta, int repeat, int vertexNum, float radius, D3DXCOLOR vertexColor, float minSize, float maxSize, char* textureFile)
{
	//인자로 받은 변수들을 멤버변수에 적용
	m_eType = type;
	m_pPosition = position;
	m_nDelta = delta;
	m_nRepaetCount = repeat;

	m_vecParticleVertex.resize(vertexNum);	//파티클 최대 갯수
	m_fRadius = radius;
	m_stColor = vertexColor;
	m_fMinSize = minSize;
	m_fMaxSize = maxSize;
	m_pTexture = g_pTextureManager->GetTexture(textureFile);

	//make vertex
	for (int i = 0; i < m_vecParticleVertex.size(); ++i)
	{
		float fRadius = RND->getFloatFromTo(0.0f, m_fRadius);	//파티클이 중심으로부터 얼마나 떨어져있는지 랜덤 값 구함
		m_vecParticleVertex[i].p = D3DXVECTOR3(0, 0, fRadius);	//파티클 위치 설정

		D3DXVECTOR3 vAngle; //중심으로부터 어느 방향으로 떨어져있는지
		switch (m_eType)	//파티클 종류에 따라 방향각도 설정
		{
		case cParticleSystem::E_PARTICLE_TYPE_SPEHRE:
			vAngle = D3DXVECTOR3(D3DXToRadian(rand() % 3600 / 10.0f), D3DXToRadian(rand() % 3600 / 10.0f), D3DXToRadian(rand() % 3600 / 10.0f));
			break;
		case cParticleSystem::E_PARTICLE_TYPE_SPREAD:
			vAngle = D3DXVECTOR3(0, D3DXToRadian(rand() % 3600 / 10.0f), 0);
			break;
		default:
			break;
		}
		
		//월드매트릭스 생성
		D3DXMATRIX matRX, matRY, matRZ, matWorld;
		D3DXMatrixRotationX(&matRX, vAngle.x);
		D3DXMatrixRotationY(&matRY, vAngle.y);
		D3DXMatrixRotationZ(&matRZ, vAngle.z);
		matWorld = matRX * matRY * matRZ;

		//위치 및 색깔 설정
		D3DXVec3TransformCoord(&m_vecParticleVertex[i].p, &m_vecParticleVertex[i].p, &matWorld);
		m_vecParticleVertex[i].c = vertexColor;
	}

	//파티클 사용시 사용되는 렌더스테이트 설정
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
	//렌더 될 알파값 변경
	m_nAlpha += m_nDelta;
	if (m_nAlpha > 255)
	{
		m_nAlpha = 255;
		m_nDelta *= -1;
	}

	if (m_nAlpha < 0)
	{
		m_nAlpha = 0;
		m_nDelta *= -1;
	}

	//한번 깜빡이면 깜빡인 횟수 증가
	if (m_nAlpha == 0)
	{
		m_nAlphaCount++;

		//깜빡인 횟수가 목표 반복횟수에 도달하면 위치값을 재설정한다.
		if (m_nAlphaCount > m_nRepaetCount - 1)
		{
			m_nAlphaCount = 0;

			for (int i = 0; i < m_vecParticleVertex.size(); ++i)
			{
				float fRadius = RND->getFloatFromTo(0.0f, m_fRadius);
				m_vecParticleVertex[i].p = D3DXVECTOR3(0, 0, fRadius);

				D3DXVECTOR3 vAngle;
				switch (m_eType)
				{
				case cParticleSystem::E_PARTICLE_TYPE_SPEHRE:
					vAngle = D3DXVECTOR3(D3DXToRadian(rand() % 3600 / 10.0f), D3DXToRadian(rand() % 3600 / 10.0f), D3DXToRadian(rand() % 3600 / 10.0f));
					break;
				case cParticleSystem::E_PARTICLE_TYPE_SPREAD:
					vAngle = D3DXVECTOR3(0, D3DXToRadian(rand() % 3600 / 10.0f), 0);
					break;
				default:
					break;
				}
				
				D3DXMATRIX matRX, matRY, matRZ, matWorld;
				D3DXMatrixRotationX(&matRX, vAngle.x);
				D3DXMatrixRotationY(&matRY, vAngle.y);
				D3DXMatrixRotationZ(&matRZ, vAngle.z);
				matWorld = matRX * matRY * matRZ;

				D3DXVec3TransformCoord(&m_vecParticleVertex[i].p, &m_vecParticleVertex[i].p, &matWorld);
			}
		}
	}

	//파티클 색깔의 알파값 변화를 적용시킨다.
	m_stColor.a = m_nAlpha;
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

	//월드 매트릭스 생성
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&matWorld, m_pPosition->x, m_pPosition->y, m_pPosition->z);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, m_pTexture);

	//파티클 렌더
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_POINTLIST, m_vecParticleVertex.size(), &m_vecParticleVertex[0], sizeof(ST_PC_VERTEX));

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}
