#include "stdafx.h"
#include "ParticleManager.h"

ParticleManager::ParticleManager()
	: rain(NULL)
{
}
ParticleManager::~ParticleManager()
{
	SAFE_DELETE(rain);
}

void ParticleManager::Update()
{
	if(rain) rain->Update();
}

void ParticleManager::Render()
{
	if(rain) rain->Render();
}

void ParticleManager::CreateParticle()
{
	g_pSoundManager->AddSound("rain", "Sound/Background/rain.mp3", true, true);

	BoundingBox rainBox;
	rainBox.min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rainBox.max = D3DXVECTOR3(30.0f, 20.0f, 30.0f);

	rain = new Particle_Rain(rainBox, 800);
	rain->Initialize("Texture/particle_rain.png");

	g_pSoundManager->Play("rain", 0.4f);
}