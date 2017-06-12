#pragma once
#include "Sky.h"

class SkyBox
{
public:
	SkyBox();
	~SkyBox();

	void Initialize(D3DXVECTOR3 center);
	void Destroy();
	void Render();

protected:
	static const int SKY_COUNT = 6;

	Sky* sky[SKY_COUNT];
};

