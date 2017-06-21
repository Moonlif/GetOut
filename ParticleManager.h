#pragma once
#include "Particle_Rain.h"

class ParticleManager
{
public:
	ParticleManager();
	~ParticleManager();

	Particle_Rain* rain;

	void Update();
	void Render();
	void CreateParticle();
};

