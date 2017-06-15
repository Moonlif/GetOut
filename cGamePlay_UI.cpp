#include "stdafx.h"
#include "cGamePlay_UI.h"
#include "cObjLoader.h"
#include "cMtlTex.h"

cGamePlay_UI::cGamePlay_UI()
{
}


cGamePlay_UI::~cGamePlay_UI()
{
	SAFE_RELEASE(m_MeshHand);
	for (int i = 0; i < m_vecHand.size(); ++i)
	{
		SAFE_DELETE(m_vecHand[i]);
	}

}

void cGamePlay_UI::Setup()
{
	cObjLoader load;
	m_MeshHand = load.LoadMesh(m_vecHand, "UI/GamePlay", "hand.obj", 1);


}

void cGamePlay_UI::Update()
{
}

void cGamePlay_UI::Render()
{
	D3DXMATRIXA16 matWorld, matS, matR, matT;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS, 0.03f, 0.03f, 0.03f);

	//회전
	matR = g_pUIvarius->m_matCameraRot;

	//방향
	D3DXVECTOR3 m_vDirection(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXVec3Normalize(&m_vDirection, &m_vDirection);

	D3DXVECTOR3 vhandPos = g_pData->m_vPosition1P + m_vDirection * 47.95f;

	//이동
	D3DXMatrixTranslation(&matT, vhandPos.x, vhandPos.y,
		vhandPos.z);

	matWorld = matS * matR * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	for (int i = 0; i < m_vecHand.size(); ++i)
	{
		g_pD3DDevice->SetMaterial(&m_vecHand[i]->GetMaterial());
		g_pD3DDevice->SetTexture(0, m_vecHand[i]->GetTexture());
		m_MeshHand->DrawSubset(i);
	}
}
