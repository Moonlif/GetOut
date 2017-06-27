#pragma once
#include "cUIObject.h"
class SkinnedMesh;

class cUIMesh : public cUIObject
{
public:
	//메쉬 타입
	enum eMESHTYPE
	{
		BOX,
		SPHERE,
		MALE,
		FEMALE,
		OTHER,
	};

	cUIMesh();
	cUIMesh(eMESHTYPE meshType, D3DXVECTOR3 pos);
	virtual~cUIMesh();

private:
	eMESHTYPE			m_eType;						//메쉬 타입 변수
	SkinnedMesh*		m_pSkinnedMesh;					//캐릭터일 시 메쉬렌더할 변수
	LPD3DXMESH			m_pMesh;						//박스, 스피어시 렌더할 변수
	D3DMATERIAL9		m_stMtl;						//머터리얼

	float				m_nCountAnim;					//애니메이션 상태 변하게할 카운트값
public:
	virtual void Update() override;
	virtual void Render(LPD3DXSPRITE pSprite) override;
};

