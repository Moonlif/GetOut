#pragma once
#include "cObject.h"

class cUIObject : public cObject
{
public:
	cUIObject();
	virtual ~cUIObject();

protected:
	D3DXMATRIXA16							m_matWorld;						//������Ʈ ����
	SYNTHESIZE(vector<cUIObject*>,			m_vecChild, Child)				//���ϵ�
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3,		m_vPosition, Position)			//������
	SYNTHESIZE(cUIObject*,					m_pParent, Parent)				//�θ�
	SYNTHESIZE(ST_SIZEN,					m_stSize, Size)					//����, ����
	SYNTHESIZE(RECT,						m_rc, rc)						//��Ʈ
	SYNTHESIZE(bool,						m_isHidden, IsHidden)			//����� ������Ʈ, ��������
	SYNTHESIZE(D3DXVECTOR3,					m_vScaling, Scaling)			//�����ϸ���

	//tag
	SYNTHESIZE(int,							m_nTag, Tag)					//�±�

public:
	virtual void SetPosition(float x, float y, float z = 0);				//������ float�� ����
	virtual void AddChild(cUIObject* pChild);								//���ϵ� ����
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();

	//tag
	virtual cUIObject* FindChildByTag(int nTag);							//���ϵ峻���� �±׷� ã��

	void SetupRect(cUIObject* pParents);									//��Ʈ ����
};

