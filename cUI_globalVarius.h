#pragma once


#define g_pUIvarius cUI_globalVarius::GetInstance() // <<

class cUI_globalVarius
{
//public:
//	cUI_globalVarius();
//	~cUI_globalVarius();

private:
	SINGLETONE(cUI_globalVarius);

	SYNTHESIZE(bool, m_IsStartedGame, IsStartedGame)

public:

};

