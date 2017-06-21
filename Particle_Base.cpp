#include "stdafx.h"
#include "Particle_Base.h"


Particle_Base::Particle_Base()
{
}

Particle_Base::~Particle_Base()
{
	Destroy();
}

bool Particle_Base::Initialize(char* textureFileName)
{
	HRESULT hr = 0;

	hr = g_pD3DDevice->CreateVertexBuffer(
		vbSize * sizeof(Particle),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,	
		Particle::FVF,
		D3DPOOL_DEFAULT,
		&vertexBuffer,
		0);

	if (FAILED(hr))
	{
		::MessageBoxA(0, "CreateVertexBuffer() - FAILED", "Particle_Base", 0);
		return false;
	}

	texture = g_pTextureManager->GetTexture(textureFileName);

	D3DXMatrixIdentity(&world);
	return true;
}

void Particle_Base::Destroy()
{
	texture = nullptr;
	SAFE_RELEASE(vertexBuffer);
	particles.clear();
}

void Particle_Base::PreRender()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, FloatToDword(size));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FloatToDword(0.0f));

	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A, FloatToDword(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B, FloatToDword(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C, FloatToDword(1.0f));

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void Particle_Base::Render()
{
	if (!particles.empty())
	{
		PreRender();

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &world);
		g_pD3DDevice->SetTexture(0, texture);
		g_pD3DDevice->SetFVF(Particle::FVF);
		g_pD3DDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(Particle));

		if (vbOffset >= vbSize)
		{
			vbOffset = 0;
		}

		Particle* v = 0;

		vertexBuffer->Lock(
			vbOffset * sizeof(Particle),
			vbBatchSize * sizeof(Particle),
			(void**)&v,
			vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);	//offset이 0이면 D3DLOCK_DISCARD로 다 지우고 처음부터 쓰기, 아니면 D3DLOCK_NOOVERWRITE로 이전것은 그대로 두고 뒤에 덧붙이기

		DWORD numParticlesInBatch = 0;

		for (auto iter = particles.begin(); iter != particles.end(); ++iter)
		{
			if (iter->isAlive)
			{
				v->position = iter->position;
				v->color = (D3DCOLOR)iter->color;
				v++;

				numParticlesInBatch++;

				if (numParticlesInBatch == vbBatchSize)
				{
					vertexBuffer->Unlock();

					g_pD3DDevice->DrawPrimitive(
						D3DPT_POINTLIST,
						vbOffset,
						vbBatchSize);
				
					vbOffset += vbBatchSize;

						vbOffset = 0;

					vertexBuffer->Lock(
						vbOffset    * sizeof(Particle),
						vbBatchSize * sizeof(Particle),
						(void**)&v,
						vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

					numParticlesInBatch = 0;
				}
			}
		}
		vertexBuffer->Unlock();

		if (numParticlesInBatch)
		{
			g_pD3DDevice->DrawPrimitive(
				D3DPT_POINTLIST,
				vbOffset,
				numParticlesInBatch);
		}
		vbOffset += vbBatchSize;

		PostRender();
	}
}

void Particle_Base::PostRender()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void Particle_Base::AddParticle()
{
	ParticleAttribute attribute;

	ResetParticle(attribute);

	particles.push_back(attribute);
}

void Particle_Base::Reset()
{
	for (auto iter = particles.begin(); iter != particles.end(); ++iter)
	{
		ResetParticle(*iter);
	}
}

bool Particle_Base::IsEmpty()
{
	return particles.empty();
}

bool Particle_Base::IsDead()
{
	for (auto iter = particles.begin(); iter != particles.end(); ++iter)
	{
		if (iter->isAlive)
			return false;
	}
	return true;
}
