#pragma once
class cTrigger
{
public:
	cTrigger();
	~cTrigger();
	
private:
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);

public:
	void Setup();
	void Update();
	void Render();
};

