#pragma once
#include "cUIObject.h"



class cUITextView : public cUIObject
{
public:
	cUITextView();
	cUITextView(string str, D3DXVECTOR3 pos, D3DCOLOR color, ST_SIZEN size,
		int wordWidth, int wordHeight, UINT wordWeight, char* fontName = "굴림체");
	virtual ~cUITextView();

protected:

	SYNTHESIZE(string, m_sText, Text);								//텍스트담을 스트링변수
	SYNTHESIZE(DWORD, m_dwDrawTextFormat, DrawTextFormat);			//DT_LEFT, DT_TOP 등 텍스트 포맷
	SYNTHESIZE(D3DCOLOR, m_dwTextColor, TextColor);					//텍스트 컬러
	SYNTHESIZE(LPD3DXFONT, m_pFont, Font);							//폰트

	
public:
	virtual void Render(LPD3DXSPRITE pSprite) override;
};

