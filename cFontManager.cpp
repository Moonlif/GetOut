#include "stdafx.h"
#include "cFontManager.h"


cFontManager::cFontManager()
{
}


cFontManager::~cFontManager()
{
}

void cFontManager::CreateFont2D(OUT LPD3DXFONT & font, IN int width, IN int height, IN UINT weight, IN char * fontName)
{
	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = height;
	fd.Width = width;
	fd.Weight = CarcWeight(weight);
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	strcpy_s(fd.FaceName, fontName);

	D3DXCreateFontIndirect(g_pD3DDevice, &fd, &font);
}

void cFontManager::CreateFont3D(OUT ID3DXMesh *& font, IN string str, IN int width, IN int height, IN UINT weight, IN char * fontName)
{
	HDC hdc = CreateCompatibleDC(0);
	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = height;
	lf.lfWidth = width;
	lf.lfWeight = CarcWeight(weight);
	lf.lfItalic = false;
	lf.lfUnderline = false;
	lf.lfStrikeOut = false;
	lf.lfCharSet = HANGEUL_CHARSET;
	strcpy_s(lf.lfFaceName, fontName);

	HFONT hFont;
	HFONT hFontOld;

	hFont = CreateFontIndirect(&lf);
	hFontOld = (HFONT)SelectObject(hdc, hFont);
	D3DXCreateText(g_pD3DDevice, hdc, str.c_str(), 0.0001f, 0.01f, &font, 0, 0);

	SelectObject(hdc, hFontOld);
	DeleteObject(hFont);
	DeleteDC(hdc);
}

void cFontManager::TextOut3D(IN ID3DXMesh * font, IN D3DXVECTOR3 scailing, IN D3DXVECTOR3 rotation, IN D3DXVECTOR3 position)
{
	D3DXMATRIXA16 matWorld, matS, matR, matT;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS, scailing.x, scailing.y, scailing.z);

	D3DXMatrixRotationX(&matR, rotation.x);
	D3DXMatrixRotationY(&matR, rotation.y);
	D3DXMatrixRotationZ(&matR, rotation.z);

	D3DXMatrixTranslation(&matT, position.x, position.y, position.z);

	matWorld = matS * matR * matT;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	font->DrawSubset(0);
}

void cFontManager::TextOut2D(IN LPD3DXFONT font, IN string str, IN int ptLeft, IN int ptTop, IN int ptRight, IN int ptBottom)
{
	string sText(str);
	RECT rc;
	SetRect(&rc, ptLeft, ptTop, ptRight, ptBottom);
	font->DrawTextA(NULL, sText.c_str(), sText.length(), &rc, DT_LEFT | DT_TOP | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 0));
}

UINT cFontManager::CarcWeight(UINT weight)
{
	if (weight < 100)	   weight = FW_DONTCARE;
	else if (weight < 200) weight = FW_THIN;
	else if (weight < 300) weight = FW_EXTRALIGHT;
	else if (weight < 400) weight = FW_LIGHT;
	else if (weight < 500) weight = FW_NORMAL;
	else if (weight < 600) weight = FW_MEDIUM;
	else if (weight < 700) weight = FW_SEMIBOLD;
	else if (weight < 800) weight = FW_BOLD;
	else if (weight < 900) weight = FW_EXTRABOLD;
	else				   weight = FW_HEAVY;

	return weight;
}
