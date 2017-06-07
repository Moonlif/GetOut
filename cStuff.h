#pragma once
class cMtlTex;

class cStuff
{
public:
	cStuff();
	~cStuff();

private:
	SYNTHESIZE(StuffCode, m_eStuffCode, StuffCode);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(D3DXVECTOR3, m_vRotation, Rotation);
	SYNTHESIZE(float, m_fRadius, Radius);
	SYNTHESIZE(bool, m_IsOnMap, IsOnMap);
	SYNTHESIZE(bool, m_bSwitch, Switch);

private:
	D3DXVECTOR3 m_vAdjust;
	float m_fScaling;

	D3DXVECTOR3 m_vRenderPosition;
	D3DXVECTOR3 m_vRenderRotation;

	float m_fSwitchValue;
	D3DXVECTOR3 m_vRePosition;
	D3DXVECTOR3 m_vReRotation;

	LPD3DXMESH m_pMesh;
	std::vector<cMtlTex*> m_vecMtlTex;
	LPD3DXMESH m_pMeshSphere;

public:
	void Setup(StuffCode code, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 adjust, float radius, float scaling, bool isOnMap);
	void Reposition(D3DXVECTOR3 position, D3DXVECTOR3 rotation);
	void Update();
	void Render();
};

