#pragma once
class cParticleSystem
{
public:
	cParticleSystem();
	~cParticleSystem();

	enum eParticleType
	{
		E_PARTICLE_TYPE_SPEHRE,
		E_PARTICLE_TYPE_SPREAD,
	};

private:
	eParticleType					m_eType;
	D3DXVECTOR3*					m_pPosition;
	int								m_nAlpha;
	int								m_nDelta;
	int								m_nAlphaCount;
	int								m_nRepaetCount;

	std::vector<ST_PC_VERTEX>		m_vecParticleVertex;
	float							m_fRadius;
	D3DXCOLOR						m_stColor;
	float							m_fMinSize;
	float							m_fMaxSize;
	LPDIRECT3DTEXTURE9				m_pTexture;

public:
	void Setup(eParticleType type, D3DXVECTOR3* position, int delta, int repeat, int vertexNum, float radius, D3DXCOLOR vertexColor, float minSize, float maxSize, char* textureFile);
	void Update();
	void Render();
};

