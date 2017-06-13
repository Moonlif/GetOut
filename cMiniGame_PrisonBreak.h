#pragma once
#include "cUIObject.h"
class cGroup;

class cMiniGame_PrisonBreak 
{
public:
	cMiniGame_PrisonBreak();
	~cMiniGame_PrisonBreak();

private:
	cUIObject*				m_pRoot;
	vector<cGroup*>			m_pObjLock;
	LPD3DXSPRITE			m_pSprite;
public:
	void Setup();
	void Update();
	void Render();


	
};

