#include "stdafx.h"
#include "cTotalUIRender.h"
#include "cStartScene.h"


cTotalUIRender::cTotalUIRender()
{
}


cTotalUIRender::~cTotalUIRender()
{
	SAFE_DELETE(m_pStartScene);
}

void cTotalUIRender::Setup()
{
	m_pStartScene = new cStartScene;
	m_pStartScene->Setup();
}

void cTotalUIRender::Update()
{
	if (m_pStartScene->GetIsStartSceneOpen()) m_pStartScene->Update();
}

void cTotalUIRender::Render()
{
	if (m_pStartScene->GetIsStartSceneOpen()) m_pStartScene->Render();
}
