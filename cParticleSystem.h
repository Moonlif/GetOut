#pragma once
class cParticleSystem
{
public:
	cParticleSystem();
	~cParticleSystem();

	//파티클 종류를 나타내는 열거형
	enum eParticleType
	{
		E_PARTICLE_TYPE_SPEHRE,		//구체형
		E_PARTICLE_TYPE_SPREAD,		//납작한 형태
	};

private:
	eParticleType					m_eType;				//파티클 타입
	D3DXVECTOR3*					m_pPosition;			//파티클 위치
	int								m_nAlpha;				//렌더용 알파 값
	int								m_nDelta;				//업데이트시 알파 값 변화량
	int								m_nAlphaCount;			//현재 깜빡인 횟수
	int								m_nRepaetCount;			//깜빡임이 반복되는 횟수 (반복이 완료되면 파티클 위치 변경)

	std::vector<ST_PC_VERTEX>		m_vecParticleVertex;	//파티클 입자 버텍스
	float							m_fRadius;				//파티클 입자 반경
	D3DXCOLOR						m_stColor;				//파티클 입자 색깔
	float							m_fMinSize;				//파티클 최소 사이즈
	float							m_fMaxSize;				//파티클 최대 사이즈
	LPDIRECT3DTEXTURE9				m_pTexture;				//파티클 텍스쳐

public:
	void Setup(eParticleType type, D3DXVECTOR3* position, int delta, int repeat, int vertexNum, float radius, D3DXCOLOR vertexColor, float minSize, float maxSize, char* textureFile);
	void Update();
	void Render();
};

