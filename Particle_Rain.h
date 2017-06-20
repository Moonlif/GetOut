#pragma once
#include "Particle_Base.h"

class Particle_Rain : public Particle_Base
{
public:
	Particle_Rain(BoundingBox& _boundingBox, int numParticles);
	virtual ~Particle_Rain();

	void Update() override;
	void ResetParticle(ParticleAttribute& attribute) override;

protected:
	BoundingBox rainBox;
};
