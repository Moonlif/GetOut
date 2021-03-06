#include "stdafx.h"
#include "cRay.h"


cRay::cRay()
	: m_vOrigin(0, 0, 0), m_vDirection(0, 0, 0), m_eRaySpace(E_NONE)
{
}


cRay::~cRay()
{
}

cRay cRay::RayAtViewSpace(int nScreenX, int nScreenY)
{
	D3DVIEWPORT9 ViewPort;
	g_pD3DDevice->GetViewport(&ViewPort);

	D3DXMATRIXA16 MatProjection;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &MatProjection);

	cRay r;
	r.m_vDirection.x = ((2.0f * nScreenX) / ViewPort.Width - 1.0f) / MatProjection._11;
	r.m_vDirection.y = ((-2.0f * nScreenY) / ViewPort.Height + 1.0f) / MatProjection._22;
	r.m_vDirection.z = 1.0f;
	r.m_eRaySpace = E_VIEW;

	return r;
}

cRay cRay::RayAtWorldSpace(int nScreenX, int nScreenY)
{
	cRay r = cRay::RayAtViewSpace(nScreenX, nScreenY);

	D3DXMATRIXA16 matView, matInvView;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matInvView, 0, &matView);

	D3DXVec3TransformCoord(&r.m_vOrigin, &r.m_vOrigin, &matInvView);
	D3DXVec3TransformNormal(&r.m_vDirection, &r.m_vDirection, &matInvView);
	D3DXVec3Normalize(&r.m_vDirection, &r.m_vDirection);

	r.m_eRaySpace = E_WORLD;

	return r;
}

bool cRay::IntersectTri(IN D3DXVECTOR3 & v0, IN D3DXVECTOR3 & v1, IN D3DXVECTOR3 & v2, OUT D3DXVECTOR3 & vPickedPosition)
{
	float u, v, t;
	bool b = D3DXIntersectTri(&v0, &v1, &v2, &m_vOrigin, &m_vDirection, &u, &v, &t);
	vPickedPosition = m_vOrigin + t * m_vDirection;
	//vPickedPosition = v0 + u *(v1 - v0) + v * (v2 - v0);

	return b;
}

bool cRay::IsPicked(ST_SPHERE * pSphere)
{
	cRay r = (*this);

	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixIdentity(&matInvWorld);
	matInvWorld._41 = -pSphere->vCenter.x;
	matInvWorld._42 = -pSphere->vCenter.y;
	matInvWorld._43 = -pSphere->vCenter.z;

	D3DXVec3TransformCoord(&r.m_vOrigin, &r.m_vOrigin, &matInvWorld);
	D3DXVec3TransformNormal(&r.m_vDirection, &r.m_vDirection, &matInvWorld);

	float vv = D3DXVec3Dot(&r.m_vDirection, &r.m_vDirection);
	float qv = D3DXVec3Dot(&r.m_vOrigin, &r.m_vDirection);
	float qq = D3DXVec3Dot(&r.m_vOrigin, &r.m_vOrigin);
	float rr = pSphere->fRadius * pSphere->fRadius;

	return qv*qv - vv * (qq - rr) >= 0;
}

bool cRay::IsPicked(D3DXVECTOR3 vPosition, float fRadius)
{
	cRay r = (*this);

	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixIdentity(&matInvWorld);
	matInvWorld._41 = -vPosition.x;
	matInvWorld._42 = -vPosition.y;
	matInvWorld._43 = -vPosition.z;

	D3DXVec3TransformCoord(&r.m_vOrigin, &r.m_vOrigin, &matInvWorld);
	D3DXVec3TransformNormal(&r.m_vDirection, &r.m_vDirection, &matInvWorld);

	float vv = D3DXVec3Dot(&r.m_vDirection, &r.m_vDirection);
	float qv = D3DXVec3Dot(&r.m_vOrigin, &r.m_vDirection);
	float qq = D3DXVec3Dot(&r.m_vOrigin, &r.m_vOrigin);
	float rr = fRadius * fRadius;

	return qv*qv - vv * (qq - rr) >= 0;
}

/*
* = DotProduct
X = Multiply

Ray = p0 + tu
||Ray - vCenter|| = r
||p0 + tu - c|| = r
u*u t^2 + 2*u(p0-c)t + (p0-c)*(p0-c) - r*r = 0
-> At^2 + Bt + C = 0
A = u*u
B = 2*u(p0-c)
C = (p0-c)*(p0-c) - r*r

D = B^2 - 4AC
D/4 = (B')^2 - AC	(B' = B/2)
D/4 = u*(p0-c)Xu*(p0-c) - u*uX((p0-c)*(p0-c)-r*r)

p0-c -> q = D3DXVec3TransformCoord(&r.m_vOrigin, &r.m_vOrigin, &matInvWorld);
u -> v = D3DXVec3TransformNormal(&r.m_vDirection, &r.m_vDirection, &matInvWorld);

D/4 = v*(p0-c) X v*(p0-c) - v*v X ((p0-c)*(p0-c)-r*r)
	= v*q X v*q - v*v X (q*q - r*r)
	= qv X qv - vv X (qq - rr)
*/