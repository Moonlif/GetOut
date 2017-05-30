#pragma once
#include "cUIObject.h"

class cUILight : public cUIObject
{
public:
	cUILight();
	cUILight(D3DLIGHTTYPE type, D3DXCOLOR Ambient, D3DXCOLOR Diffuse, D3DXCOLOR Specular,
		D3DXVECTOR3 dir, DWORD nIndex);
	~cUILight();
private:

public:

};

