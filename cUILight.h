#pragma once
#include "cUIObject.h"

class cUILight : public cUIObject
{
public:
	cUILight();
	virtual~cUILight();
private:
	LPD3DXMESH		m_pGizmo;						//기즈모 메쉬(현재 비활성화)
	DWORD			m_nName;						//라이트 이름
public:

	//스팟라이트 셋팅
	void SetSpotLight(DWORD nIndex, D3DXCOLOR color, D3DXVECTOR3 pos,
		float range, float phi, float theta, D3DXVECTOR3 dir);

	//디렉션라이트 셋팅
	void SetDirectionLight(DWORD nIndex, D3DXCOLOR color, D3DXVECTOR3 dir);

	//포인트 라이트 셋팅
	void SetPointLight(DWORD nIndex, D3DXCOLOR color, D3DXVECTOR3 pos, float range);


	virtual void Render(LPD3DXSPRITE pSprite) override;
};

