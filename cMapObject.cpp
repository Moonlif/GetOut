#include "stdafx.h"
#include "cMapObject.h"


cMapObject::cMapObject()
{
	m_vecGroup.clear();
}


cMapObject::~cMapObject()
{
	//17.05.30 ����ȣ
	for each(auto p in m_vecGroup)
	{
		SAFE_DELETE(p);
	}
}


/*==========================================================================
Summary: object�� �ҷ� ���� ���� �Լ�
Parameters:
[in] *folder - �ҷ��� ������Ʈ ��� ����
[in] *fileName - �ҷ��� ������Ʈ ���� �̸�
Returns:
Worker: ����ȣ
==========================================================================*/
void cMapObject::Setup(char* folder, char* fileName)
{
	cObjLoader loadMesh;
	loadMesh.Load(m_vecGroup, folder, fileName);
}



/*==========================================================================
Summary: object�� �׸��� ���� �Լ�
Parameters:
[in] size - object ũ�� ����
[in] x - object x ��ǥ
[in] y - object y ��ǥ
[in] z - object z ��ǥ
[in] rotY - object y�� ȸ�� ��
Returns:
Worker: ����ȣ
==========================================================================*/
void cMapObject::Render(float size, float x, float y, float z , float rotY)
{
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x80);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	D3DXMATRIXA16 matWorld, matS, matR, matT;
	D3DXMatrixScaling(&matS, size, size, size);
	D3DXMatrixRotationY(&matR, D3DX_PI * rotY);
	D3DXMatrixTranslation(&matT, x, y, z);
	matWorld = matS * matT * matR;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	for each(auto p in m_vecGroup)
	{
		p->Render();
	}
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
}

