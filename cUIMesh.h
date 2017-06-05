#pragma once
#include "cUIObject.h"

class cUIMesh : public cUIObject
{
public:
	enum eMESHTYPE
	{
		BOX,
		SPHERE,
		OTHER,
	};

	cUIMesh();
	cUIMesh(eMESHTYPE meshType, D3DXVECTOR3 pos);
	virtual~cUIMesh();

private:
	LPD3DXMESH			m_pMesh;
	D3DMATERIAL9		m_stMtl;
public:
	virtual void Render(LPD3DXSPRITE pSprite) override;
};

