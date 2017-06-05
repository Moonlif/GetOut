#pragma once
#include "cUIObject.h"

class cUILight : public cUIObject
{
public:
	cUILight();
	virtual~cUILight();
private:
	LPD3DXMESH		m_pGizmo;
	DWORD			m_nName;
public:
	void SetSpotLight(DWORD nIndex, D3DXCOLOR color, D3DXVECTOR3 pos,
		float range, float phi, float theta, D3DXVECTOR3 dir);
	void SetDirectionLight(DWORD nIndex, D3DXCOLOR color, D3DXVECTOR3 dir);
	void SetPointLight(DWORD nIndex, D3DXCOLOR color, D3DXVECTOR3 pos, float range);


	virtual void Render(LPD3DXSPRITE pSprite) override;
};

