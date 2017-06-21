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

	SYNTHESIZE(int, 		m_nAlpha, Alpha)
public:
	virtual void Render(LPD3DXSPRITE pSprite) override;

};

