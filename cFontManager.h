#pragma once
#define g_pFontManager cFontManager::GetInstance()

class cFontManager
{
public:

private:
	SINGLETONE(cFontManager);

public:

	void CreateFont2D(OUT LPD3DXFONT& font, IN int width, IN int height, IN UINT weight, IN char* fontName);
	void CreateFont3D(OUT ID3DXMesh*& font, IN string str, IN int width, IN int height, IN UINT weight,
		IN char* fontName);

	void TextOut3D(IN ID3DXMesh* font, IN D3DXVECTOR3 scailing, IN D3DXVECTOR3 rotation, IN D3DXVECTOR3 position);
	UINT CarcWeight(UINT weight);
};

