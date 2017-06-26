#pragma once
class cParticleSystem
{
public:
	cParticleSystem();
	~cParticleSystem();

	//��ƼŬ ������ ��Ÿ���� ������
	enum eParticleType
	{
		E_PARTICLE_TYPE_SPEHRE,		//��ü��
		E_PARTICLE_TYPE_SPREAD,		//������ ����
	};

private:
	eParticleType					m_eType;				//��ƼŬ Ÿ��
	D3DXVECTOR3*					m_pPosition;			//��ƼŬ ��ġ
	int								m_nAlpha;				//������ ���� ��
	int								m_nDelta;				//������Ʈ�� ���� �� ��ȭ��
	int								m_nAlphaCount;			//���� ������ Ƚ��
	int								m_nRepaetCount;			//�������� �ݺ��Ǵ� Ƚ�� (�ݺ��� �Ϸ�Ǹ� ��ƼŬ ��ġ ����)

	std::vector<ST_PC_VERTEX>		m_vecParticleVertex;	//��ƼŬ ���� ���ؽ�
	float							m_fRadius;				//��ƼŬ ���� �ݰ�
	D3DXCOLOR						m_stColor;				//��ƼŬ ���� ����
	float							m_fMinSize;				//��ƼŬ �ּ� ������
	float							m_fMaxSize;				//��ƼŬ �ִ� ������
	LPDIRECT3DTEXTURE9				m_pTexture;				//��ƼŬ �ؽ���

public:
	void Setup(eParticleType type, D3DXVECTOR3* position, int delta, int repeat, int vertexNum, float radius, D3DXCOLOR vertexColor, float minSize, float maxSize, char* textureFile);
	void Update();
	void Render();
};

