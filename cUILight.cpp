#include "stdafx.h"
#include "cUILight.h"


cUILight::cUILight()
{
	D3DXCreateSphere(g_pD3DDevice, 0.2f, 5, 5, &m_pGizmo, NULL);
}

cUILight::~cUILight()
{
	SAFE_RELEASE(m_pGizmo);
}


void cUILight::SetSpotLight(DWORD nIndex, D3DXCOLOR color, D3DXVECTOR3 pos, float range, float phi, float theta, D3DXVECTOR3 dir)
{
	D3DLIGHT9 stLight;

	m_vPosition = pos;
	m_nName = nIndex;

	g_pLightManager->SetSpotLight(nIndex, color, color, color, pos, range, phi, theta, dir);
}

void cUILight::SetDirectionLight(DWORD nIndex, D3DXCOLOR color, D3DXVECTOR3 dir)
{
	D3DLIGHT9 stLight;
	m_nName = nIndex;

	g_pLightManager->SetDirectionLight(nIndex, color, color, color, dir);
}

void cUILight::SetPointLight(DWORD nIndex, D3DXCOLOR color, D3DXVECTOR3 pos, float range)
{
	D3DLIGHT9 stLight;

	m_vPosition = pos;
	m_nName = nIndex;

	g_pLightManager->SetPointLight(nIndex, color, color, color, pos, range);
}

void cUILight::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden)
	{
		g_pD3DDevice->LightEnable(m_nName, false);
		return;
	}
	//����Ʈ ������ ����
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	g_pD3DDevice->GetLight(m_nName, &stLight);
	stLight.Position.x = m_matWorld._41;
	stLight.Position.y = m_matWorld._42;
	stLight.Position.z = m_matWorld._43;
	g_pD3DDevice->SetLight(m_nName, &stLight);

	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	//m_pGizmo->DrawSubset(0);

	cUIObject::Render(pSprite);
}
