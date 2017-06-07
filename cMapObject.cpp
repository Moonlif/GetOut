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

void cMapObject::Setup(char* folder, char* fileName)
{
	cObjLoader loadMesh;
	loadMesh.Load(m_vecGroup, folder, fileName);
}



void cMapObject::Render(float size, float x, float y, float z)
{
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//�����׽�Ʈ�� ���ذ��� 0x80(10����128)�� ����
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x80);
	//�����׽�Ʈ�� ���(D3DRS_ALPHAFUNC)��
	//D3DCMP_GREATEREQUAL(���İ��� ���ذ����� ũ�ų� ������ �ؽ��� ���)���� ����
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	D3DXMATRIXA16 matWorld, matS, matR, matT;
	D3DXMatrixScaling(&matS, size, size, size);
	D3DXMatrixRotationY(&matR, -D3DX_PI); 
	D3DXMatrixTranslation(&matT, x, y, z);
	matWorld = matS * matT * matR;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	for each(auto p in m_vecGroup)
	{
		p->Render();
	}
}
