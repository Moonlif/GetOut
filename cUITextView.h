#pragma once
#include "cUIObject.h"



class cUITextView : public cUIObject
{
public:
	cUITextView();
	cUITextView(string str, D3DXVECTOR3 pos, D3DCOLOR color, ST_SIZEN size,
		int wordWidth, int wordHeight, UINT wordWeight, char* fontName = "����ü");
	virtual ~cUITextView();

protected:

	SYNTHESIZE(string, m_sText, Text);								//�ؽ�Ʈ���� ��Ʈ������
	SYNTHESIZE(DWORD, m_dwDrawTextFormat, DrawTextFormat);			//DT_LEFT, DT_TOP �� �ؽ�Ʈ ����
	SYNTHESIZE(D3DCOLOR, m_dwTextColor, TextColor);					//�ؽ�Ʈ �÷�
	SYNTHESIZE(LPD3DXFONT, m_pFont, Font);							//��Ʈ

	
public:
	virtual void Render(LPD3DXSPRITE pSprite) override;
};

