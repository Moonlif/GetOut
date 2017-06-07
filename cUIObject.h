#pragma once
#include "cObject.h"

class cUIObject : public cObject
{
public:
	cUIObject();
	virtual ~cUIObject();

protected:
	D3DXMATRIXA16							m_matWorld;
	SYNTHESIZE(vector<cUIObject*>,			m_vecChild, Child)
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3,		m_vPosition, Position)
	SYNTHESIZE(cUIObject*,					m_pParent, Parent)
	SYNTHESIZE(ST_SIZEN,					m_stSize, Size)
	SYNTHESIZE(RECT,						m_rc, rc)
	SYNTHESIZE(bool,						m_isHidden, IsHidden)
	SYNTHESIZE(D3DXVECTOR3,					m_vScaling, Scaling)

	//tag
	SYNTHESIZE(int,							m_nTag, Tag)

public:
	virtual void AddChild(cUIObject* pChild);
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();

	//tag
	virtual cUIObject* FindChildByTag(int nTag);

	void SetupRect(cUIObject* pParents);
};

