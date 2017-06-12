#pragma once

struct FVF_PositionTexture
{
	D3DXVECTOR3 pos = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR2 tex = D3DXVECTOR2(0, 0);

	FVF_PositionTexture()
	{
	}
	FVF_PositionTexture(D3DXVECTOR3 _pos, D3DXVECTOR2 _tex)
		: pos(_pos), tex(_tex)
	{
	}

	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1, };
};

struct TextureTriangle
{
	TextureTriangle()
	{
		vertex[0] = FVF_PositionTexture();
		vertex[1] = FVF_PositionTexture();
		vertex[2] = FVF_PositionTexture();
	}
	TextureTriangle(const FVF_PositionTexture& v1, const FVF_PositionTexture& v2, const FVF_PositionTexture& v3)
	{
		vertex[0] = v1;
		vertex[1] = v2;
		vertex[2] = v3;
	}
	TextureTriangle(const D3DXVECTOR3& v1, const D3DXVECTOR3& v2, const D3DXVECTOR3& v3,
		const D3DXVECTOR2& uv1, const D3DXVECTOR2& uv2, const D3DXVECTOR2& uv3)
	{
		vertex[0] = FVF_PositionTexture(v1, uv1);
		vertex[1] = FVF_PositionTexture(v2, uv2);
		vertex[2] = FVF_PositionTexture(v3, uv3);
	}
	FVF_PositionTexture vertex[3];
};

class Sky
{
public:
	Sky();
	~Sky();

	void Initialize(LPCSTR textureName, D3DXVECTOR3 s, D3DXVECTOR3 p);
	void Destroy();
	void Render();

protected:
	static const int TRIANGLE_COUNT = 12;

	TextureTriangle triangles[TRIANGLE_COUNT];

	D3DXMATRIXA16 world;

	LPDIRECT3DTEXTURE9 skyTexture = nullptr;

	D3DXVECTOR3 position;
	D3DXVECTOR3 size;

	LPDIRECT3DVERTEXBUFFER9	vertexBuffer = nullptr;
	LPDIRECT3DINDEXBUFFER9 indexBuffer = nullptr;
	bool drawVertexBuffer = false;
};

