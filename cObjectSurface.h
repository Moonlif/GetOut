#pragma once
#include "cRectMake.h"
struct ObjectSurface
{
	D3DXVECTOR3 point;
	int floor;
};
class cObjectSurface
{
private:
	SYNTHESIZE(std::vector<ObjectSurface>, vecVertex, VecVertex);
public:
	cObjectSurface();
	~cObjectSurface();

	void AddSurface(D3DXVECTOR3 v, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, int floor);
	void RenderSurface();
};

