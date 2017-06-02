#pragma once

class cRectMake
{
private:
	std::vector<ST_PNT_VERTEX>	 m_vecBottomVertex;
	LPDIRECT3DTEXTURE9			 m_pTexture;
	D3DMATERIAL9				 m_stMtl;
public:
	cRectMake();
	~cRectMake();
	void Setup(D3DXVECTOR3 v, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, char * szFile);
	void Render();
};

