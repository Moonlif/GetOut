#include "stdafx.h"
#include "cUIObject.h"


cUIObject::cUIObject()
	: m_vPosition(0, 0, 0)
	, m_pParent(NULL)
	, m_stSize(0, 0)
	, m_isHidden(false)
	, m_nTag(0)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cUIObject::~cUIObject()
{
	for each(auto c in m_vecChild)
	{
		SAFE_RELEASE(c);
	}


	SAFE_RELEASE(m_pParent);
}

void cUIObject::AddChild(cUIObject * pChild)
{
	pChild->SetParent(this);
	m_vecChild.push_back(pChild);

	pChild->SetupRect();
}

void cUIObject::Update()
{
	if (m_isHidden) return;

	D3DXMatrixIdentity(&m_matWorld);
	m_matWorld._41 = m_vPosition.x;
	m_matWorld._42 = m_vPosition.y;
	m_matWorld._43 = m_vPosition.z;

	if (m_pParent)
	{
		m_matWorld._41 += m_pParent->m_matWorld._41;
		m_matWorld._42 += m_pParent->m_matWorld._42;
		m_matWorld._43 += m_pParent->m_matWorld._43;
	}

	for each (auto c in m_vecChild)
		c->Update();
}

void cUIObject::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	for each (auto c in m_vecChild)
		c->Render(pSprite);
}

void cUIObject::Destroy()
{
	m_isHidden = true;
	for each (auto c in m_vecChild)
		c->Destroy();

	this->Release();
}

cUIObject * cUIObject::FindChildByTag(int nTag)
{
	if (m_nTag == nTag) return this;
	for each (auto c in m_vecChild)
	{
		cUIObject* p = c->FindChildByTag(nTag);
		if (p) return p;
	}
	return NULL;
}

void cUIObject::SetupRect()
{
	//버튼이나, 텍스트나 모두 렌더링 할 때마다 셋렉트를 하는 것이 아닌 한번만 렉트를 초기화 하는게 더 나아 보여서
	//아래작업을 부모와 포지션을 먼제 셋업 후에 한번만 함.

	D3DXMatrixIdentity(&m_matWorld);
	m_matWorld._41 = m_vPosition.x;
	m_matWorld._42 = m_vPosition.y;
	m_matWorld._43 = m_vPosition.z;

	if (m_pParent)
	{
		m_matWorld._41 += m_pParent->m_matWorld._41;
		m_matWorld._42 += m_pParent->m_matWorld._42;
		m_matWorld._43 += m_pParent->m_matWorld._43;
	}

	SetRect(&m_rc, m_matWorld._41, m_matWorld._42, m_matWorld._41 + m_stSize.nWidth,
		m_matWorld._42 + m_stSize.nHeight);
}
