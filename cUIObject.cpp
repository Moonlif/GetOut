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

	//�����ϸ�
	D3DXMatrixScaling(&matS, m_vScaling.x, m_vScaling.y, m_vScaling.z);

	//Ʈ������
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = matS * matT;

	//�θ������� ���� �����ֱ�
	if (m_pParent)
	{
		D3DXMATRIXA16 matParentWorld;
		D3DXMatrixIdentity(&matParentWorld);

		D3DXMatrixTranslation(&matParentWorld, m_pParent->GetPosition().x,
			m_pParent->GetPosition().y, m_pParent->GetPosition().z);

		m_matWorld *= matParentWorld;
	}

	//��Ʈ ����
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
	//��ư�̳�, �ؽ�Ʈ�� ��� ������ �� ������ �·�Ʈ�� �ϴ� ���� �ƴ� �ѹ��� ��Ʈ�� �ʱ�ȭ �ϴ°� �� ���� ������
	//�Ʒ��۾��� �θ�� �������� ���� �¾� �Ŀ� �ѹ��� ��.

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
