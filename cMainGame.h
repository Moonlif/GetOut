#pragma once
#include "cCamera.h"

#include "cMap.h"
#include "cTotalUIRender.h"
#include "cInteract.h"
#include "CharacterManager.h"

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

