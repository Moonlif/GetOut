#pragma once
class cMtlTex;

class cStuff
{
public:
	cStuff();
	~cStuff();

private:
	SYNTHESIZE(ItemCode, m_eCode, Code);
	SYNTHESIZE(float, m_fRadius, Radius);
	SYNTHESIZE(float, m_fScaling, Scaling);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);

	SYNTHESIZE(string, m_sName, Name);
	LPD3DXMESH m_pMesh;
	std::vector<cMtlTex*> m_vecMtlTex;

	SYNTHESIZE(bool, m_IsOnMap, IsOnMap);

	LPD3DXMESH m_pMeshSphere;
public:
	void Setup(ItemCode code, D3DXVECTOR3 position, bool isOnMap);
	void Update();
	void Render();
};

