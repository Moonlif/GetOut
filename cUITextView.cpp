#include "stdafx.h"
#include "cUITextView.h"


cUITextView::cUITextView()
	: m_dwDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK)
	, m_dwTextColor(D3DCOLOR_ARGB(0,0,0,0))
	, m_pFont(NULL)
{
}

cUITextView::cUITextView(string str, D3DXVECTOR3 pos, D3DCOLOR color, ST_SIZEN size, int wordWidth, int wordHeight, UINT wordWeight, char * fontName)
	:m_dwDrawTextFormat(DT_LEFT | DT_TOP | DT_WORDBREAK)
{
	m_sText = str;
	m_vPosition = pos;
	m_dwTextColor = color;
	m_stSize = size;

	g_pFontManager->CreateFont2D(m_pFont, wordWidth, wordHeight, wordWeight, fontName);
}


cUITextView::~cUITextView()
{
	SAFE_RELEASE(m_pFont);
}

void cUITextView::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	if (m_pFont) m_pFont->DrawTextA(NULL, m_sText.c_str(), m_sText.length(), &m_rc, m_dwDrawTextFormat, m_dwTextColor);
	
	cUIObject::Render(pSprite);

	//cout << m_rc.left << " " << m_rc.top << endl;
}
