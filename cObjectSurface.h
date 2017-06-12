#pragma once
#include "cRectMake.h"

class cObjectSurface
{
private:
	SYNTHESIZE(std::vector<ST_PC_VERTEX>, vecVertex, VecVertex);
public:
	cObjectSurface();
	~cObjectSurface();

	void AddSurface(D3DXVECTOR3 v, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3);
	void RenderSurface();
};

