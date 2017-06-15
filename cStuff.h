#pragma once
class cMtlTex;
#include "cParticleSystem.h"

class cStuff
{
public:
	cStuff();
	~cStuff();

private:
	SYNTHESIZE(StuffCode, m_eStuffCode, StuffCode);		//������Ʈ ������ȣ
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);		//��ü�� ���� ��ġ��
	SYNTHESIZE(D3DXVECTOR3, m_vRotation, Rotation);		//��ü�� ���� ȸ����
	SYNTHESIZE(float, m_fRadius, Radius);				//�浹 ������ ������
	SYNTHESIZE(bool, m_IsOnMap, IsOnMap);				//�ʿ� �ִ��� �κ��丮�� �ִ���
	SYNTHESIZE(bool, m_bSwitch, Switch);				//�۵������� Ȯ��

private:
	D3DXVECTOR3 m_vAdjust;								//������ ��ġ���� ��
	float m_fScaling;									//������ ������ ��ȭ��

	D3DXVECTOR3 m_vRenderPosition;						//������ ������ ���Ǵ� ��ġ��
	D3DXVECTOR3 m_vRenderRotation;						//������ ������ ���Ǵ� ȸ����

	float m_fSwitchValue;								//�۵��� ��ȭ�� ������ ��Ÿ���� �� (����: 0~1.0f)
	float m_fSwitchValueIntensity;						//�۵��� �󸶳� ���� ��ȭ�Ǵ����� ��Ÿ���� ��
	D3DXVECTOR3 m_vRePosition;							//�۵��� ������ȭ�� ��ġ��
	D3DXVECTOR3 m_vReRotation;							//�۵��� ������ȭ�� ȸ����

	LPD3DXMESH m_pMesh;									//������Ʈ �޽�����
	std::vector<cMtlTex*> m_vecMtlTex;					//������Ʈ ���͸���&�ؽ��� ����
	LPD3DXMESH m_pMeshSphere;							//����׿� ������ �ð�ȭ�ϱ� ���� ��ü

	cParticleSystem* m_pParticle;

public:
	void Setup(StuffCode code, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 adjust, float radius, float scaling, bool isOnMap);
	void Reposition(D3DXVECTOR3 position, D3DXVECTOR3 rotation, float switchIntensity = 0.05f);
	void Reposition(D3DXVECTOR3 deltaPosition);
	void Update();
	void Render();
};

