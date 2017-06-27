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
}

//포지션 float 값 세팅
void cUIObject::SetPosition(float x, float y, float z)
{
	m_vPosition.x = x;
	m_vPosition.y = y;
	m_vPosition.z = z;
}

//차일드 생성
void cUIObject::AddChild(cUIObject * pChild)
{
	pChild->SetParent(this);
	m_vecChild.push_back(pChild);

	//차일드 생성시 렉트 설정하는 함수
	pChild->SetupRect(this);
}

void cUIObject::Update()
{
	if (m_isHidden) return;

	//트랜지션, 스케일 초기화
	D3DXMATRIXA16 matT, matS;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matS);

	//스케일링
	D3DXMatrixScaling(&matS, m_vScaling.x, m_vScaling.y, m_vScaling.z);

	//트랜지션
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	//월드 구하기
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

	//재귀적으로 함수 콜
	for each (auto c in m_vecChild)
	{
		cUIObject* p = c->FindChildByTag(nTag);
		if (p) return p;
	}

	return NULL;
}

//버튼이나, 텍스트나 모두 렌더링 할 때마다 셋렉트를 하는 것이 아닌 
//한번만 렉트를 초기화 하는게 더 나아 보여서
//아래작업을 부모와 포지션을 먼제 셋업 후에 한번만 함.
void cUIObject::SetupRect(cUIObject* pParents)
{
	//자신의 포지션값 월드에 저장.
	D3DXMatrixIdentity(&m_matWorld);
	m_matWorld._41 = m_vPosition.x;
	m_matWorld._42 = m_vPosition.y;
	m_matWorld._43 = m_vPosition.z;

	//부모가 있을시 부모의 좌표 더해줌
	if (m_pParent)
	{
		m_matWorld._41 += pParents->m_matWorld._41;
		m_matWorld._42 += pParents->m_matWorld._42;
		m_matWorld._43 += pParents->m_matWorld._43;
	}

	//렉트 설정(스케일링 값을 곱해줌)
	SetRect(&m_rc, m_matWorld._41, m_matWorld._42, 
		m_matWorld._41 + (m_stSize.nWidth * m_vScaling.x),
		m_matWorld._42 + (m_stSize.nHeight* m_vScaling.y));
}
