#include "stdafx.h"
#include "cCharacterSelectScene.h"

#include "cUIImageView.h"
#include "cUIObject.h"


#include "cSkinnedMesh.h"
cCharacterSelectScene::cCharacterSelectScene()
	:m_pSprite(NULL)
	, m_pBlackImage(NULL)
	,m_pRoot(NULL)
{
}


cCharacterSelectScene::~cCharacterSelectScene()
{
	m_pRoot->Destroy();
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pBox1);
	SAFE_RELEASE(m_pBox2);
}

void cCharacterSelectScene::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	//라이트 셋업
	{
		D3DXCOLOR commonColor(0.8f, 0.8f, 0.8f, 1.0f);
		float commonRange = 3.3f;

		//오른쪽 아래 라이트
		g_pLightManager->SetSpotLight(eLIGHT::E_sCHASLECT_RDIGHT, commonColor, commonColor, commonColor, 
			D3DXVECTOR3(2, 4.9f, -800), commonRange, D3DX_PI, D3DX_PI / 6, D3DXVECTOR3(0, -1, 0));
		g_pD3DDevice->LightEnable(eLIGHT::E_sCHASLECT_RDIGHT, true);

		//오른쪽 위 라이트
		g_pLightManager->SetSpotLight(eLIGHT::E_sCHASLECT_RULIGHT, commonColor, commonColor, commonColor,
			D3DXVECTOR3(2, 5.1f, -800), commonRange, D3DX_PI, D3DX_PI / 6, D3DXVECTOR3(0, 1, 0));
		g_pD3DDevice->LightEnable(eLIGHT::E_sCHASLECT_RULIGHT, false);
		
		//왼쪽 아래 라이트
		g_pLightManager->SetSpotLight(eLIGHT::E_sCHASLECT_LDIGHT, commonColor, commonColor, commonColor,
			D3DXVECTOR3(-2, 4.9f, -800), commonRange, D3DX_PI, D3DX_PI / 6, D3DXVECTOR3(0, -1, 0));
		g_pD3DDevice->LightEnable(eLIGHT::E_sCHASLECT_LDIGHT, true);

		//왼쪽 위 라이트
		g_pLightManager->SetSpotLight(eLIGHT::E_sCHASLECT_LULIGHT, commonColor, commonColor, commonColor,
			D3DXVECTOR3(-2, 5.1f, -800), commonRange, D3DX_PI, D3DX_PI / 6, D3DXVECTOR3(0, 1, 0));
		g_pD3DDevice->LightEnable(eLIGHT::E_sCHASLECT_LULIGHT, false);
	}

	m_pBlackImage = new cUIImageView("UI/BlackBackground.png", D3DXVECTOR3(0, 0, 1.0f), 200);
	m_pRoot = m_pBlackImage;


	//테스트
	TestCharacSetup();
}

void cCharacterSelectScene::Update()
{
	m_pRoot->Update();

}

void cCharacterSelectScene::Render()
{
	m_pRoot->Render(m_pSprite);

	TestCharacRender();
}

void cCharacterSelectScene::TestCharacSetup()
{
	D3DXCreateSphere(g_pD3DDevice, 0.5f, 50, 50, &m_pBox1, NULL);
	D3DXCreateSphere(g_pD3DDevice, 0.5f, 50, 50, &m_pBox2, NULL);

	ZeroMemory(&m_stMtlBox, sizeof(D3DMATERIAL9));
	m_stMtlBox.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlBox.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlBox.Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
}

void cCharacterSelectScene::TestCharacRender()
{

	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);

	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
	matWorld = matS * matR;

	//1번캐릭
	D3DXMatrixTranslation(&matWorld, 2, 5, -800);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetMaterial(&m_stMtlBox);
	m_pBox1->DrawSubset(0);

	//2번캐릭
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixTranslation(&matWorld, -2, 5, -800);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pBox2->DrawSubset(0);
}
