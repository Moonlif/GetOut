#include "stdafx.h"
#include "cUILight.h"


cUILight::cUILight()
{
	D3DXCreateBox(g_pD3DDevice, 0.1f, 0.1f, 0.1f, &m_pGizmo, NULL);
}

cUILight::~cUILight()
{
}


void cUILight::SetSpotLight(DWORD nIndex, D3DXCOLOR Ambient, D3DXCOLOR Diffuse, D3DXCOLOR Specular, D3DXVECTOR3 pos, float range, float phi, float theta, D3DXVECTOR3 dir)
{
	D3DLIGHT9 stLight;

	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_SPOT;
	stLight.Ambient = Ambient;
	stLight.Diffuse = Diffuse;
	stLight.Specular = Specular;
	stLight.Range = range;
	stLight.Phi = phi;
	stLight.Theta = theta;
	stLight.Position = pos;
	D3DXVec3Normalize(&dir, &dir);
	stLight.Direction = dir;

	stLight.Attenuation0 = 0.1f;
	stLight.Attenuation1 = 0.1f;
	stLight.Attenuation2 = 0.1f;
	stLight.Falloff = 1.0f;

	g_pD3DDevice->SetLight(nIndex, &stLight);
	g_pD3DDevice->LightEnable(nIndex, false);
}

void cUILight::SetDirectionLight(DWORD nIndex, D3DXCOLOR Ambient, D3DXCOLOR Diffuse, D3DXCOLOR Specular, D3DXVECTOR3 dir)
{
	D3DLIGHT9 stLight;

	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = Ambient;
	stLight.Diffuse = Diffuse;
	stLight.Specular = Specular;

	D3DXVec3Normalize(&dir, &dir);
	stLight.Direction = dir;

	g_pD3DDevice->SetLight(nIndex, &stLight);
	g_pD3DDevice->LightEnable(nIndex, false);
}

void cUILight::SetPointLight(DWORD nIndex, D3DXCOLOR Ambient, D3DXCOLOR Diffuse, D3DXCOLOR Specular, D3DXVECTOR3 pos, float range)
{
	D3DLIGHT9 stLight;

	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_POINT;
	stLight.Ambient = Ambient;
	stLight.Diffuse = Diffuse;
	stLight.Specular = Specular;
	stLight.Position = pos;
	stLight.Range = range;

	stLight.Attenuation0 = 0.1f;
	stLight.Attenuation1 = 0.1f;
	stLight.Attenuation2 = 0.1f;

	g_pD3DDevice->SetLight(nIndex, &stLight);
	g_pD3DDevice->LightEnable(nIndex, false);
}

void cUILight::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pGizmo->DrawSubset(0);

	cUIObject::Render(pSprite);
}
