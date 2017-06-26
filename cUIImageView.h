#pragma once
#include "cUIObject.h"
class cUIImageView : public cUIObject
{
public:
	cUIImageView();
	cUIImageView(char* szFullPath, D3DXVECTOR3 pos, int alpha);
	virtual ~cUIImageView();

protected:
	LPDIRECT3DTEXTURE9		m_pTexture;						//이미지 텍스쳐

	SYNTHESIZE(int, 		m_nAlpha, Alpha)				//알파값
public:
	virtual void Render(LPD3DXSPRITE pSprite) override;

};

