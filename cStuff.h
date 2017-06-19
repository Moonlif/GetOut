#pragma once
class cMtlTex;
#include "cParticleSystem.h"

class cStuff
{
public:
	cStuff();
	~cStuff();

private:
	SYNTHESIZE(StuffCode, m_eStuffCode, StuffCode);		//오브젝트 고유번호
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);		//물체의 현재 위치값
	SYNTHESIZE(D3DXVECTOR3, m_vRotation, Rotation);		//물체의 현재 회전값
	SYNTHESIZE(float, m_fRadius, Radius);				//충돌 판정용 반지름
	SYNTHESIZE(bool, m_IsOnMap, IsOnMap);				//맵에 있는지 인벤토리에 있는지
	SYNTHESIZE(bool, m_bSwitch, Switch);				//작동중인지 확인

private:
	D3DXVECTOR3 m_vAdjust;								//렌더시 위치보정 값
	float m_fScaling;									//렌더시 스케일 변화값

	D3DXVECTOR3 m_vRenderPosition;						//실제로 렌더시 사용되는 위치값
	D3DXVECTOR3 m_vRenderRotation;						//실제로 렌더시 사용되는 회전값

	float m_fSwitchValue;								//작동시 변화된 정도를 나타내는 값 (범위: 0~1.0f)
	float m_fSwitchValueIntensity;						//작동시 얼마나 빨리 변화되는지를 나타내는 값
	D3DXVECTOR3 m_vRePosition;							//작동시 최종변화될 위치값
	D3DXVECTOR3 m_vReRotation;							//작동시 최종변화될 회전값

	LPD3DXMESH m_pMesh;									//오브젝트 메쉬정보
	std::vector<cMtlTex*> m_vecMtlTex;					//오브젝트 머터리얼&텍스쳐 정보
	LPD3DXMESH m_pMeshSphere;							//디버그용 반지름 시각화하기 위한 구체

	cParticleSystem* m_pParticle;

public:
	void Setup(StuffCode code, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 adjust, float radius, float scaling, bool isOnMap);
	void Reposition(D3DXVECTOR3 position, D3DXVECTOR3 rotation, float switchIntensity = 0.05f);
	void Update();
	void Render();
};

