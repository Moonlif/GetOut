#pragma once
#include "cRectMake.h"



class cSurface
{
private:
	SYNTHESIZE(std::vector<D3DXVECTOR3>, vecVertex, VecVertex);
	//����
	cRectMake* m_pB1StartRoom;
	cRectMake* m_pB1Prison;
	cRectMake* m_pB1StartSpace;
	cRectMake* m_pB1NextRoom;
	cRectMake* m_pB1Stair[10];
	//1��
	cRectMake* m_pFFPassage;
	cRectMake* m_pFFPassage2;
	cRectMake* m_pFFLivingRoom;
	cRectMake* m_pFFLivingRoom2;
	cRectMake* m_pFFRoom;
	cRectMake* m_pFBathRoom;
	cRectMake* m_pB1Stair2[10];
	//2��
	cRectMake* m_pSFPassage;
	cRectMake* m_pSFRoom;
	cRectMake* m_pSFRoom2;

	std::vector<ST_PNT_VERTEX> m_vecBottomVertex;
	LPDIRECT3DTEXTURE9		   m_pTexture;
	D3DMATERIAL9			   m_stMtl;
public:
	cSurface();
	~cSurface();
	void Setup();
	void Render();
	
};
