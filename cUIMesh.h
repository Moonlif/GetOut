#pragma once
#include "cUIObject.h"
class SkinnedMesh;

class cUIMesh : public cUIObject
{
public:
	//�޽� Ÿ��
	enum eMESHTYPE
	{
		BOX,
		SPHERE,
		MALE,
		FEMALE,
		OTHER,
	};

	cUIMesh();
	cUIMesh(eMESHTYPE meshType, D3DXVECTOR3 pos);
	virtual~cUIMesh();

private:
	eMESHTYPE			m_eType;						//�޽� Ÿ�� ����
	SkinnedMesh*		m_pSkinnedMesh;					//ĳ������ �� �޽������� ����
	LPD3DXMESH			m_pMesh;						//�ڽ�, ���Ǿ�� ������ ����
	D3DMATERIAL9		m_stMtl;						//���͸���

	float				m_nCountAnim;					//�ִϸ��̼� ���� ���ϰ��� ī��Ʈ��
public:
	virtual void Update() override;
	virtual void Render(LPD3DXSPRITE pSprite) override;
};

