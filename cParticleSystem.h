#pragma once
class cParticleSystem
{
public:
	cParticleSystem();
	~cParticleSystem();

private:
	std::vector<ST_PC_VERTEX>		m_vecParticleVertex;
	D3DXCOLOR						m_stColor;
	LPDIRECT3DTEXTURE9				m_pTexture;
	D3DXVECTOR3*					m_pPosition;
	float							m_fRadius;
	float							m_fMinSize;
	float							m_fMaxSize;

public:
	void Setup(int vertexSize, float radius, D3DXCOLOR vertexColor, float minSize, float maxSize, char* textureFile, D3DXVECTOR3* position);
	void Update();
	void Render();
};

