#pragma once
#include "cUIObject.h"



class cUITextView : public cUIObject
{
public:
	cUITextView();
	cUITextView(string str, D3DXVECTOR3 pos, D3DCOLOR color, ST_SIZEN size,
		int wordWidth, int wordHeight, UINT wordWeight, char* fontName = "±¼¸²Ã¼");
	virtual ~cUITextView();

protected:

	SYNTHESIZE(string, m_sText, Text);
	SYNTHESIZE(DWORD, m_dwDrawTextFormat, DrawTextFormat);
	SYNTHESIZE(D3DCOLOR, m_dwTextColor, TextColor);
	SYNTHESIZE(LPD3DXFONT, m_pFont, Font);

	
public:
	virtual void Render(LPD3DXSPRITE pSprite) override;

	virtual cUITextView* FindEmptyInvene();
};

