#pragma once
class cMtlTex;

class cGamePlay_UI
{
public:
	cGamePlay_UI();
	~cGamePlay_UI();

private:
	vector<cMtlTex*>	m_vecHand;	
	LPD3DXMESH			m_MeshHand;
public:
	void Setup();
	void Update();
	void Render();
};

