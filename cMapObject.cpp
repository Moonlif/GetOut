#include "stdafx.h"
#include "cMapObject.h"


cMapObject::cMapObject()
{
	m_vecGroup.clear();
}


cMapObject::~cMapObject()
{
	//17.05.30 최진호
	for each(auto p in m_vecGroup)
	{
		SAFE_DELETE(p);
	}
}


/*==========================================================================
Summary: object를 불러 오기 위한 함수
Parameters:
[in] *folder - 불러올 오브젝트 경로 폴도
[in] *fileName - 불러올 오브젝트 파일 이름
Returns:
Worker: 최진호
==========================================================================*/
void cMapObject::Setup(char* folder, char* fileName)
{
	cObjLoader loadMesh;
	loadMesh.Load(m_vecGroup, folder, fileName);
}



/*==========================================================================
Summary: object를 그리기 위한 함수
Parameters:
[in] size - object 크기 지정
[in] x - object x 좌표
[in] y - object y 좌표
[in] z - object z 좌표
[in] rotY - object y축 회전 값
Returns:
Worker: 최진호
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

