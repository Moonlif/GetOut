#pragma once
#include "cUIObject.h"
class cUIImageView : public cUIObject
{
public:
	cUIImageView();
	cUIImageView(char* szFullPath, D3DXVECTOR3 pos, int alpha);
	virtual ~cUIImageView();

protected:
	LPDIRECT3DTEXTURE9		m_pTexture;

	SYNTHESIZE(D3DCOLOR,	m_dwImageColor, ImageColor);		//알파값 주기 위한 변수
public:
	virtual void Render(LPD3DXSPRITE pSprite) override;

};

