#pragma once
#include "cCamera.h"

#include "cChat.h"
#include "cMap.h"
#include "cTotalUIRender.h"
#include "cUIButton.h"
#include "cInteract.h"
#include "CharacterManager.h"
#include "MonsterManager.h"
#include "SkyBox.h"

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	cCamera*			m_pCamera;

	//map
	cMap* m_pMap;

	//character
	CharacterManager* m_pCharacter;
	MonsterManager* m_pMonsterManager;
	SkyBox* m_pSkybox;

	//ui
	cTotalUIRender*		m_pTotalUIRender;

	//interact
	cInteract* m_pInteract;

public:
	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

