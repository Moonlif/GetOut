#pragma once
#include "cUIObject.h"

class cUILight : public cUIObject
{
public:
	cUILight();
	cUILight(D3DLIGHTTYPE type, D3DXCOLOR Ambient, D3DXCOLOR Diffuse, D3DXCOLOR Specular,
		D3DXVECTOR3 dir, DWORD nIndex);
	~cUILight();
private:
	LPD3DXMESH		m_pGizmo;
public:
	void SetSpotLight(DWORD nIndex, D3DXCOLOR Ambient, D3DXCOLOR Diffuse, D3DXCOLOR Specular, D3DXVECTOR3 pos,
		float range, float phi, float theta, D3DXVECTOR3 dir);
	void SetDirectionLight(DWORD nIndex, D3DXCOLOR Ambient, D3DXCOLOR Diffuse, D3DXCOLOR Specular, D3DXVECTOR3 dir);
	void SetPointLight(DWORD nIndex, D3DXCOLOR Ambient, D3DXCOLOR Diffuse, D3DXCOLOR Specular,
		D3DXVECTOR3 pos, float range);


	virtual void Render(LPD3DXSPRITE pSprite) override;
};

