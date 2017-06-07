#include "stdafx.h"
#include "cUIObject.h"


cUIObject::cUIObject()
	: m_vPosition(0, 0, 0)
	, m_pParent(NULL)
	, m_stSize(0, 0)
	, m_isHidden(false)
	, m_nTag(0)
	, m_vScaling(1.0f, 1.0f, 1.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cUIObject::~cUIObject()
{
	//Destroy();
}

void cUIObject::AddChild(cUIObject * pChild)
{
	pChild->SetParent(this);
	m_vecChild.push_back(pChild);

	
	pChild->SetupRect(this);
}

void cUIObject::Update()
{
	if (m_isHidden) return;

	D3DXMATRIXA16 matT, matS;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matS);

	//스케일링
	D3DXMatrixScaling(&matS, m_vScaling.x, m_vScaling.y, m_vScaling.z);

	//트랜지션
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = matS * matT;

	//부모있으면 월드 곱해주기
	if (m_pParent)
	{
		D3DXMATRIXA16 matParentWorld;
		D3DXMatrixIdentity(&matParentWorld);

		D3DXMatrixTranslation(&matParentWorld, m_pParent->GetPosition().x,
			m_pParent->GetPosition().y, m_pParent->GetPosition().z);

		m_matWorld *= matParentWorld;
	}

	//렉트 지정
	SetRect(&m_rc, m_matWorld._41, m_matWorld._42,
		m_matWorld._41 + (m_stSize.nWidth * m_vScaling.x),
		m_matWorld._42 + (m_stSize.nHeight * m_vScaling.y));

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


void cUIObject::SetupRect(cUIObject* pParents)
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

	SetRect(&m_rc, m_matWorld._41, m_matWorld._42, m_matWorld._41 + (m_stSize.nWidth * m_vScaling.x),
		m_matWorld._42 + (m_stSize.nHeight* m_vScaling.y));
}
