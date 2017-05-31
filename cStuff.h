#pragma once
class cMtlTex;

class cStuff
{
public:
	cStuff();
	~cStuff();

private:
	ItemCode m_eCode;
	float m_fSize;
	D3DXVECTOR3 m_vPosition;

	string m_sName;
	LPD3DXMESH m_pMesh;
	std::vector<cMtlTex*> m_vecMtlTex;

	bool m_IsOnMap;

public:
	void Setup(ItemCode code, D3DXVECTOR3 position, bool isOnMap);
	void Update();
	void Render();

};

