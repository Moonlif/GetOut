#include "stdafx.h"
#include "Sky.h"

Sky::Sky()
{
}
Sky::~Sky()
{
	Destroy();
}

void Sky::Initialize(LPCSTR textureName, D3DXVECTOR3 s, D3DXVECTOR3 p)
{
	D3DXMatrixIdentity(&world);

	size = s;
	position = p;

	const int VERTEX_COUNT = 8;
	D3DXVECTOR3 vertex[VERTEX_COUNT];
	vertex[0] = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	vertex[1] = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	vertex[2] = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	vertex[3] = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	vertex[4] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vertex[5] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vertex[6] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vertex[7] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	triangles[0] = TextureTriangle(vertex[0], vertex[1], vertex[2], D3DXVECTOR2(0, 1), D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 0));
	triangles[1] = TextureTriangle(vertex[0], vertex[2], vertex[3], D3DXVECTOR2(0, 1), D3DXVECTOR2(1, 0), D3DXVECTOR2(1, 1));

	triangles[2] = TextureTriangle(vertex[4], vertex[5], vertex[1], D3DXVECTOR2(0, 1), D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 0));
	triangles[3] = TextureTriangle(vertex[4], vertex[1], vertex[0], D3DXVECTOR2(0, 1), D3DXVECTOR2(1, 0), D3DXVECTOR2(1, 1));

	triangles[4] = TextureTriangle(vertex[7], vertex[6], vertex[5], D3DXVECTOR2(0, 1), D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 0));
	triangles[5] = TextureTriangle(vertex[7], vertex[5], vertex[4], D3DXVECTOR2(0, 1), D3DXVECTOR2(1, 0), D3DXVECTOR2(1, 1));

	triangles[6] = TextureTriangle(vertex[3], vertex[2], vertex[6], D3DXVECTOR2(0, 1), D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 0));
	triangles[7] = TextureTriangle(vertex[3], vertex[6], vertex[7], D3DXVECTOR2(0, 1), D3DXVECTOR2(1, 0), D3DXVECTOR2(1, 1));

	triangles[8] = TextureTriangle(vertex[1], vertex[5], vertex[6], D3DXVECTOR2(0, 1), D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 0));
	triangles[9] = TextureTriangle(vertex[1], vertex[6], vertex[2], D3DXVECTOR2(0, 1), D3DXVECTOR2(1, 0), D3DXVECTOR2(1, 1));

	triangles[10] = TextureTriangle(vertex[4], vertex[0], vertex[3], D3DXVECTOR2(0, 1), D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 0));
	triangles[11] = TextureTriangle(vertex[4], vertex[3], vertex[7], D3DXVECTOR2(0, 1), D3DXVECTOR2(1, 0), D3DXVECTOR2(1, 1));

	D3DXCreateTextureFromFile(g_pD3DDevice, textureName, &skyTexture);

	//버텍스 버퍼와 인덱스 버퍼 사용
	g_pD3DDevice->CreateVertexBuffer(
		VERTEX_COUNT * sizeof(FVF_PositionTexture),
		0,
		FVF_PositionTexture::FVF,
		D3DPOOL_MANAGED,
		&vertexBuffer,
		nullptr);
	g_pD3DDevice->CreateIndexBuffer(
		36 * sizeof(WORD),
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&indexBuffer,
		nullptr
		);

	FVF_PositionTexture vertexPT[VERTEX_COUNT];
	vertexPT[0] = FVF_PositionTexture(vertex[0], D3DXVECTOR2(0, 1));
	vertexPT[1] = FVF_PositionTexture(vertex[1], D3DXVECTOR2(0, 0));
	vertexPT[2] = FVF_PositionTexture(vertex[2], D3DXVECTOR2(1, 0));
	vertexPT[3] = FVF_PositionTexture(vertex[3], D3DXVECTOR2(1, 1));
	vertexPT[4] = FVF_PositionTexture(vertex[4], D3DXVECTOR2(0, 1));
	vertexPT[5] = FVF_PositionTexture(vertex[5], D3DXVECTOR2(0, 0));
	vertexPT[6] = FVF_PositionTexture(vertex[6], D3DXVECTOR2(1, 0));
	vertexPT[7] = FVF_PositionTexture(vertex[7], D3DXVECTOR2(1, 1));
	LPVOID pV;
	vertexBuffer->Lock(0, 0, &pV, 0);
	memcpy_s(pV, VERTEX_COUNT * sizeof(FVF_PositionTexture), vertexPT, VERTEX_COUNT * sizeof(FVF_PositionTexture));
	vertexBuffer->Unlock();

	WORD index[36];
	index[0] = 0; index[1] = 1; index[2] = 2;
	index[3] = 0; index[4] = 2; index[5] = 3;

	index[6] = 4; index[7] = 5; index[8] = 1;
	index[9] = 4; index[10] = 1; index[11] = 0;

	index[12] = 7; index[13] = 6; index[14] = 5;
	index[15] = 7; index[16] = 5; index[17] = 4;

	index[18] = 3; index[19] = 2; index[20] = 6;
	index[21] = 3; index[22] = 6; index[23] = 7;

	index[24] = 1; index[25] = 5; index[26] = 6;
	index[27] = 1; index[28] = 6; index[29] = 2;

	index[30] = 4; index[31] = 0; index[32] = 3;
	index[33] = 4; index[34] = 3; index[35] = 7;
	LPVOID pI;
	indexBuffer->Lock(0, 0, &pI, 0);
	memcpy_s(pI, 36 * sizeof(WORD), index, 36 * sizeof(WORD));
	indexBuffer->Unlock();

	D3DXMATRIX scaleMatrix, translateMatrix;
	D3DXMatrixIdentity(&scaleMatrix);
	D3DXMatrixIdentity(&translateMatrix);

	D3DXMatrixScaling(&scaleMatrix, size.x, size.y, size.z);
	D3DXMatrixTranslation(&translateMatrix, position.x, position.y, position.z);
	world *= scaleMatrix;
	world *= translateMatrix;
}

void Sky::Destroy()
{
	SAFE_RELEASE(skyTexture);
	SAFE_RELEASE(indexBuffer);
	SAFE_RELEASE(vertexBuffer);
}

void Sky::Render()
{
	//GameManager::GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//GameManager::GetDevice()->SetRenderState(D3DRS_ZENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTexture(0, skyTexture);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &world);
	g_pD3DDevice->SetFVF(FVF_PositionTexture::FVF);

	if (drawVertexBuffer == false)
	{
		g_pD3DDevice->DrawPrimitiveUP(
			D3DPT_TRIANGLELIST,
			TRIANGLE_COUNT,
			&triangles[0],
			sizeof(FVF_PositionTexture));
	}
	else
	{
		g_pD3DDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(FVF_PositionTexture));
		g_pD3DDevice->SetIndices(indexBuffer);
		g_pD3DDevice->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST,
			0, 0, 8, 0, 12
			);
	}
}
