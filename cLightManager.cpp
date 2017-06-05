#include "stdafx.h"
#include "cLightManager.h"


cLightManager::cLightManager()
{
}


cLightManager::~cLightManager()
{
}

void cLightManager::SetSpotLight(DWORD nIndex, D3DXCOLOR Ambient, D3DXCOLOR Diffuse, D3DXCOLOR Specular, D3DXVECTOR3 pos,
	float range, float phi, float theta, D3DXVECTOR3 dir)
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

void cLightManager::SetDirectionLight(DWORD nIndex, D3DXCOLOR Ambient, D3DXCOLOR Diffuse, D3DXCOLOR Specular, D3DXVECTOR3 dir)
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

void cLightManager::SetPointLight(DWORD nIndex, D3DXCOLOR Ambient, D3DXCOLOR Diffuse, D3DXCOLOR Specular,
	D3DXVECTOR3 pos, float range)
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