#pragma once
#include "cUIObject.h"
class SkinnedMesh;

class cUIMesh : public cUIObject
{
public:
	enum eMESHTYPE
	{
		BOX,
		SPHERE,
		MALE,
		FEMALE,
		OTHER,
	};

	cUIMesh();
	cUIMesh(eMESHTYPE meshType, D3DXVECTOR3 pos);
	virtual~cUIMesh();

private:
	eMESHTYPE			m_eType;
	SkinnedMesh*		m_pSkinnedMesh;
	LPD3DXMESH			m_pMesh;
	D3DMATERIAL9		m_stMtl;

	float				m_nCountAnim;
public:
	virtual void Update() override;
	virtual void Render(LPD3DXSPRITE pSprite) override;
};

