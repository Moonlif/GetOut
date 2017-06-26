#include "stdafx.h"
#include "cStuff.h"

#include "cMtlTex.h"

cStuff::cStuff()
	: m_eStuffCode(STUFF_NONE)
	, m_vPosition(0, 0, 0)
	, m_vRotation(0, 0, 0)
	, m_fRadius(0.0f)
	, m_IsOnMap(true)

	, m_vAdjust(0, 0, 0)
	, m_fScaling(0.0f)
	, m_vRenderPosition(0, 0, 0)
	, m_vRenderRotation(0, 0, 0)
	, m_fSwitchValue(0.0f)
	, m_fSwitchValueIntensity(0.0f)
	, m_bSwitch(false)
	, m_vRePosition(0, 0, 0)
	, m_vReRotation(0, 0, 0)

	, m_pMesh(NULL)
	, m_pMeshSphere(NULL)
	, m_pParticle(NULL)
{
}


cStuff::~cStuff()
{
	SAFE_RELEASE(m_pMesh);
	for each (auto it in m_vecMtlTex)
	{
		SAFE_RELEASE(it);
	}

	SAFE_RELEASE(m_pMeshSphere);
}

void cStuff::Setup(StuffCode code, D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 adjust, float radius, float scaling, bool isOnMap)
{
	m_eStuffCode = code;
	m_vPosition = m_vRenderPosition = m_vRePosition = position;
	m_vRotation = m_vRenderRotation = m_vReRotation = rotation;
	m_vAdjust = adjust;
	m_fRadius = radius;
	m_fScaling = scaling;
	m_IsOnMap = isOnMap;

	//g_pData에 있는 맵에 오브젝트코드에 맞는 메쉬가 존재하면
	if (g_pData->m_mapStuffMesh.find(m_eStuffCode)->second != NULL)
	{
		m_pMesh = g_pData->m_mapStuffMesh[m_eStuffCode];			//g_pData에 있는 맵에서 메쉬를 사용한다.
		g_pData->m_mapStuffMesh[m_eStuffCode]->AddRef();			//레퍼런스 값 증가
	}

	//g_pData에 있는 맵에 오브젝트코드에 맞는 머터리얼&텍스쳐가 존재하면
	if (g_pData->m_mapStuffVecMtlTex.find(m_eStuffCode) != g_pData->m_mapStuffVecMtlTex.end())
	{
		m_vecMtlTex = g_pData->m_mapStuffVecMtlTex[m_eStuffCode];	//g_pData에 있는 맵에서 머터리얼&텍스쳐를 사용한다.
		for (int i = 0; i < m_vecMtlTex.size(); ++i)
		{
			m_vecMtlTex[i]->AddRef();								//레퍼런스 값 증가
		}
	}

	D3DXCreateSphere(g_pD3DDevice, m_fRadius, 10, 10, &m_pMeshSphere, NULL);	//디버그용 구체를 생성한다.

	//오브젝트가 아이템인 경우
	if (m_eStuffCode >= STUFF_CROWBAR && m_eStuffCode <= STUFF_BRICK5)
	{
		D3DXCOLOR stColor;
		stColor.a = 255;
		stColor.r = 255;
		stColor.g = 255;
		stColor.b = 255;

		//파티클을 생성한다.
		m_pParticle = new cParticleSystem;
		m_pParticle->Setup(cParticleSystem::eParticleType::E_PARTICLE_TYPE_SPEHRE, &m_vPosition, 8, 2, 10, 1.0f, stColor, 0.0f, 20.0f, "Texture/alpha_item_tex.tga");
	}
}

//인자로 받은 위치값, 회전값, 변화정도를 세팅한다.
void cStuff::Reposition(D3DXVECTOR3 position, D3DXVECTOR3 rotation, float switchIntensity)
{
	//현재 위치와 회전값이 같으면 리턴
	if (m_vRePosition == position && m_vReRotation == rotation) return;

	m_bSwitch = true;			//작동중으로 설정
	m_fSwitchValue = 0.0f;		//작동 초기값 설정 (0.0f ~ 1.0f로 변화)
	m_vRePosition = position;	//바뀔 위치값 입력
	m_vReRotation = rotation;	//바뀔 회전값 입력

	m_fSwitchValueIntensity = switchIntensity;	//작동시 얼마나 빨리 변화되는지를 나타내는 값 설정

	//각 오브젝트에 맞는 사운드 출력
	if (m_eStuffCode == STUFF_DOOR_PRISON || m_eStuffCode == STUFF_DOOR_1STTOILET) g_pSoundManager->Play("door_prison", 0.5f);
	else if (m_eStuffCode == STUFF_DOOR_1STROOM) g_pSoundManager->Play("door_1stRoom", 0.5f);
	else if (m_eStuffCode == STUFF_DOOR_2NDROOM1) g_pSoundManager->Play("door_2ndRoom1", 0.5f);
	else if (m_eStuffCode == STUFF_DOOR_2NDROOM2) g_pSoundManager->Play("door_2ndRoom2", 0.5f);
	else if (m_eStuffCode == STUFF_DOOR_FINAL) g_pSoundManager->Play("door_final", 0.5f);

	else if (m_eStuffCode == STUFF_BOX1) g_pSoundManager->Play("base_box", 0.5f);
	else if (m_eStuffCode == STUFF_CHEST3) g_pSoundManager->Play("base_chest", 0.5f);
	else if (m_eStuffCode == STUFF_WOODBOARD1) g_pSoundManager->Play("1st_wood1", 0.5f);
	else if (m_eStuffCode == STUFF_WOODBOARD2) g_pSoundManager->Play("1st_wood2", 0.5f);
	else if (m_eStuffCode == STUFF_BOARDBLOCK) g_pSoundManager->Play("1st_wood1", 0.5f);

	else if (m_eStuffCode == STUFF_BUTTON1) g_pSoundManager->Play("2nd_button", 0.5f);
	else if (m_eStuffCode == STUFF_BUTTON3) g_pSoundManager->Play("2nd_button", 0.5f);
	else if (m_eStuffCode == STUFF_VALVE1) g_pSoundManager->Play("2nd_valve", 0.5f);
	else if (m_eStuffCode == STUFF_VALVE2) g_pSoundManager->Play("2nd_valve", 0.5f);
}

void cStuff::Update()
{
	//아이템일시 g_pData에 값(서버에서 받는 값)과 연동
	if (m_eStuffCode >= STUFF_CROWBAR && m_eStuffCode <= STUFF_BRICK5)
	{
		m_IsOnMap = g_pData->m_bStuffSwitch[m_eStuffCode];
		m_vPosition = m_vRenderPosition = g_pData->m_vStuffPosition[m_eStuffCode];
		m_vRotation = m_vRenderRotation = g_pData->m_vStuffRotation[m_eStuffCode];
	}

	//작동중이라면
	if (m_bSwitch)
	{
		//현재 작동값(0.0f~1.0f범위)에 변화정도를 나타내는 변수를 더해준다.
		m_fSwitchValue += m_fSwitchValueIntensity;	
		
		//위치와 회전값을 보간하여 실제로 렌더되는 위치와 회전값에 적용시킨다.
		m_vRenderPosition = m_vPosition + (m_vRePosition - m_vPosition) * m_fSwitchValue;
		m_vRenderRotation = m_vRotation + (m_vReRotation - m_vRotation) * m_fSwitchValue;
		
		//작동이 완료되면 변수들을 재설정해준다.
		if (m_fSwitchValue > 1.0f)	
		{
			m_fSwitchValue = 0.0f;
			m_bSwitch = false;

			m_vPosition = m_vRenderPosition;
			m_vRotation = m_vRenderRotation;
		}
	}

	//파티클이 존재하고(아이템만 존재) 맵에 있을 때 파티클 업데이트 실행
	if (m_pParticle && m_IsOnMap == true) m_pParticle->Update();
}

void cStuff::Render()
{
	//맵에 없으면 리턴
	if (m_IsOnMap == false) return;

	//디버그용 렌더스테이트 변경
	if (g_bDebug)
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}

	//월드매트릭스를 만들어 출력하는데 사용한다.
	D3DXMATRIXA16 matWorld, matS, matR, matT;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS, m_fScaling, m_fScaling, m_fScaling);
	D3DXMATRIXA16 matRx, matRy, matRz;
	D3DXMatrixRotationX(&matRx, m_vRenderRotation.x);
	D3DXMatrixRotationY(&matRy, m_vRenderRotation.y);
	D3DXMatrixRotationZ(&matRz, m_vRenderRotation.z);
	matR =  matRy * matRz * matRx;

	D3DXMatrixTranslation(&matT, m_vRenderPosition.x - m_vAdjust.x, m_vRenderPosition.y - m_vAdjust.y, m_vRenderPosition.z - m_vAdjust.z);

	matWorld = matS * matR * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	//메쉬 정보를 각 머터리얼&텍스쳐의 갯수 인덱스에 따라 메쉬를 그린다.
	for (int i = 0; i < m_vecMtlTex.size(); ++i)
	{
		g_pD3DDevice->SetMaterial(&m_vecMtlTex[i]->GetMaterial());
		g_pD3DDevice->SetTexture(0, m_vecMtlTex[i]->GetTexture());
		m_pMesh->DrawSubset(i);
	}

	//파티클이 존재하고 맵에 있으면 파티클을 렌더한다.
	if (m_pParticle && m_IsOnMap == true) m_pParticle->Render();

	//디버그시 구체 렌더
	if (g_bDebug)
	{
		//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		D3DXMATRIXA16 matDebug;
		D3DXMatrixTranslation(&matDebug, m_vPosition.x, m_vPosition.y, m_vPosition.z);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matDebug);
		if (m_pMeshSphere != NULL) m_pMeshSphere->DrawSubset(0);
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}
