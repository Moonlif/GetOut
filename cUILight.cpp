#include "stdafx.h"
#include "cUILight.h"


cUILight::cUILight()
{
}

cUILight::cUILight(D3DLIGHTTYPE type, D3DXCOLOR Ambient, D3DXCOLOR Diffuse, D3DXCOLOR Specular,
	D3DXVECTOR3 dir, DWORD nIndex)
{
	D3DLIGHT9 stLight;
	{
		ZeroMemory(&stLight, sizeof(D3DLIGHT9));
		stLight.Type = type;
		stLight.Ambient = Ambient;
		stLight.Diffuse = Diffuse;
		stLight.Specular = Specular;
		D3DXVECTOR3 vDir(1.0f, 1.0f, 1.0f);
		D3DXVec3Normalize(&vDir, &vDir);
		stLight.Direction = vDir;
		g_pD3DDevice->SetLight(nIndex, &stLight);
	}

	g_pD3DDevice->LightEnable(nIndex, true);
}


cUILight::~cUILight()
{
}
