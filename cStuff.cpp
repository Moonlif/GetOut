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

	//g_pData�� �ִ� �ʿ� ������Ʈ�ڵ忡 �´� �޽��� �����ϸ�
	if (g_pData->m_mapStuffMesh.find(m_eStuffCode)->second != NULL)
	{
		m_pMesh = g_pData->m_mapStuffMesh[m_eStuffCode];			//g_pData�� �ִ� �ʿ��� �޽��� ����Ѵ�.
		g_pData->m_mapStuffMesh[m_eStuffCode]->AddRef();			//���۷��� �� ����
	}

	//g_pData�� �ִ� �ʿ� ������Ʈ�ڵ忡 �´� ���͸���&�ؽ��İ� �����ϸ�
	if (g_pData->m_mapStuffVecMtlTex.find(m_eStuffCode) != g_pData->m_mapStuffVecMtlTex.end())
	{
		m_vecMtlTex = g_pData->m_mapStuffVecMtlTex[m_eStuffCode];	//g_pData�� �ִ� �ʿ��� ���͸���&�ؽ��ĸ� ����Ѵ�.
		for (int i = 0; i < m_vecMtlTex.size(); ++i)
		{
			m_vecMtlTex[i]->AddRef();								//���۷��� �� ����
		}
	}

	D3DXCreateSphere(g_pD3DDevice, m_fRadius, 10, 10, &m_pMeshSphere, NULL);	//����׿� ��ü�� �����Ѵ�.

	//������Ʈ�� �������� ���
	if (m_eStuffCode >= STUFF_CROWBAR && m_eStuffCode <= STUFF_BRICK5)
	{
		D3DXCOLOR stColor;
		stColor.a = 255;
		stColor.r = 255;
		stColor.g = 255;
		stColor.b = 255;

		//��ƼŬ�� �����Ѵ�.
		m_pParticle = new cParticleSystem;
		m_pParticle->Setup(cParticleSystem::eParticleType::E_PARTICLE_TYPE_SPEHRE, &m_vPosition, 8, 2, 10, 1.0f, stColor, 0.0f, 20.0f, "Texture/alpha_item_tex.tga");
	}
}

//���ڷ� ���� ��ġ��, ȸ����, ��ȭ������ �����Ѵ�.
void cStuff::Reposition(D3DXVECTOR3 position, D3DXVECTOR3 rotation, float switchIntensity)
{
	//���� ��ġ�� ȸ������ ������ ����
	if (m_vRePosition == position && m_vReRotation == rotation) return;

	m_bSwitch = true;			//�۵������� ����
	m_fSwitchValue = 0.0f;		//�۵� �ʱⰪ ���� (0.0f ~ 1.0f�� ��ȭ)
	m_vRePosition = position;	//�ٲ� ��ġ�� �Է�
	m_vReRotation = rotation;	//�ٲ� ȸ���� �Է�

	m_fSwitchValueIntensity = switchIntensity;	//�۵��� �󸶳� ���� ��ȭ�Ǵ����� ��Ÿ���� �� ����

	//�� ������Ʈ�� �´� ���� ���
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
	//�������Ͻ� g_pData�� ��(�������� �޴� ��)�� ����
	if (m_eStuffCode >= STUFF_CROWBAR && m_eStuffCode <= STUFF_BRICK5)
	{
		m_IsOnMap = g_pData->m_bStuffSwitch[m_eStuffCode];
		m_vPosition = m_vRenderPosition = g_pData->m_vStuffPosition[m_eStuffCode];
		m_vRotation = m_vRenderRotation = g_pData->m_vStuffRotation[m_eStuffCode];
	}

	//�۵����̶��
	if (m_bSwitch)
	{
		//���� �۵���(0.0f~1.0f����)�� ��ȭ������ ��Ÿ���� ������ �����ش�.
		m_fSwitchValue += m_fSwitchValueIntensity;	
		
		//��ġ�� ȸ������ �����Ͽ� ������ �����Ǵ� ��ġ�� ȸ������ �����Ų��.
		m_vRenderPosition = m_vPosition + (m_vRePosition - m_vPosition) * m_fSwitchValue;
		m_vRenderRotation = m_vRotation + (m_vReRotation - m_vRotation) * m_fSwitchValue;
		
		//�۵��� �Ϸ�Ǹ� �������� �缳�����ش�.
		if (m_fSwitchValue > 1.0f)	
		{
			m_fSwitchValue = 0.0f;
			m_bSwitch = false;

			m_vPosition = m_vRenderPosition;
			m_vRotation = m_vRenderRotation;
		}
	}

	//��ƼŬ�� �����ϰ�(�����۸� ����) �ʿ� ���� �� ��ƼŬ ������Ʈ ����
	if (m_pParticle && m_IsOnMap == true) m_pParticle->Update();
}

void cStuff::Render()
{
	//�ʿ� ������ ����
	if (m_IsOnMap == false) return;

	//����׿� ����������Ʈ ����
	if (g_bDebug)
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}

	//�����Ʈ������ ����� ����ϴµ� ����Ѵ�.
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

	//�޽� ������ �� ���͸���&�ؽ����� ���� �ε����� ���� �޽��� �׸���.
	for (int i = 0; i < m_vecMtlTex.size(); ++i)
	{
		g_pD3DDevice->SetMaterial(&m_vecMtlTex[i]->GetMaterial());
		g_pD3DDevice->SetTexture(0, m_vecMtlTex[i]->GetTexture());
		m_pMesh->DrawSubset(i);
	}

	//��ƼŬ�� �����ϰ� �ʿ� ������ ��ƼŬ�� �����Ѵ�.
	if (m_pParticle && m_IsOnMap == true) m_pParticle->Render();

	//����׽� ��ü ����
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
