#pragma once
#define B1F 0
#define FF 2 + B1F
#define SF 2 + FF
#define TOP 2 + SF
//½ºÅ¸µù ÁÂÇ¥
#define CENTERX -10
#define CENTERZ 0


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
	void Render(int index = 0);
};

