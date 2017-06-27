#pragma once
#include "cObject.h"

class cUIObject : public cObject
{
public:
	cUIObject();
	virtual ~cUIObject();

protected:
	D3DXMATRIXA16							m_matWorld;						//오브젝트 월드
	SYNTHESIZE(vector<cUIObject*>,			m_vecChild, Child)				//차일드
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3,		m_vPosition, Position)			//포지션
	SYNTHESIZE(cUIObject*,					m_pParent, Parent)				//부모
	SYNTHESIZE(ST_SIZEN,					m_stSize, Size)					//넓이, 높이
	SYNTHESIZE(RECT,						m_rc, rc)						//렉트
	SYNTHESIZE(bool,						m_isHidden, IsHidden)			//히든시 업데이트, 렌더안함
	SYNTHESIZE(D3DXVECTOR3,					m_vScaling, Scaling)			//스케일링값

	//tag
	SYNTHESIZE(int,							m_nTag, Tag)					//태그

public:
	virtual void SetPosition(float x, float y, float z = 0);				//포지션 float값 세팅
	virtual void AddChild(cUIObject* pChild);								//차일드 설정
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();

	//tag
	virtual cUIObject* FindChildByTag(int nTag);							//차일드내에서 태그로 찾기

	void SetupRect(cUIObject* pParents);									//렉트 세팅
};

