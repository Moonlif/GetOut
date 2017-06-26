#pragma once
#include "cUIObject.h"

class cUILight : public cUIObject
{
public:
	cUILight();
	virtual~cUILight();
private:
	LPD3DXMESH		m_pGizmo;						//����� �޽�(���� ��Ȱ��ȭ)
	DWORD			m_nName;						//����Ʈ �̸�
public:

	//���̶���Ʈ ����
	void SetSpotLight(DWORD nIndex, D3DXCOLOR color, D3DXVECTOR3 pos,
		float range, float phi, float theta, D3DXVECTOR3 dir);

	//�𷺼Ƕ���Ʈ ����
	void SetDirectionLight(DWORD nIndex, D3DXCOLOR color, D3DXVECTOR3 dir);

	//����Ʈ ����Ʈ ����
	void SetPointLight(DWORD nIndex, D3DXCOLOR color, D3DXVECTOR3 pos, float range);


	virtual void Render(LPD3DXSPRITE pSprite) override;
};

