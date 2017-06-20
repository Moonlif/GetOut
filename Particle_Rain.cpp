#include "stdafx.h"
#include "Particle_Rain.h"

Particle_Rain::Particle_Rain(BoundingBox& _boundingBox, int numParticles)
{
	rainBox = _boundingBox;
	size = 0.1f;

	for (int i = 0; i < numParticles; i++)
	{
		AddParticle();
	}
}
Particle_Rain::~Particle_Rain()
{
}

void Particle_Rain::Update()
{
	for (auto iter = particles.begin(); iter != particles.end(); ++iter)
	{
		iter->position += (iter->velocity * g_pTimeManager->GetElapsedTime());

		if (rainBox.IsPointIn(iter->position) == false)
		{
			ResetParticle(*iter);
		}
	}
}

void Particle_Rain::ResetParticle(ParticleAttribute& attribute)
{
	attribute.isAlive = true;

	RND->GetVector(attribute.position, rainBox.max, rainBox.min);
	attribute.position.y = rainBox.max.y;

	attribute.velocity.x = 0.0f;
	attribute.velocity.y = RND->getFloatFromTo(10.0f, 15.0f) * -1.0f;
	attribute.velocity.z = 0.0f;

	attribute.color = D3DCOLOR_XRGB(255, 255, 255);
}
