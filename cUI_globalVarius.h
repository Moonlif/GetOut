#pragma once


#define g_pUIvarius cUI_globalVarius::GetInstance() // <<

class cUI_globalVarius
{
//public:
//	cUI_globalVarius();
//	~cUI_globalVarius();

private:
	SINGLETONE(cUI_globalVarius);

	//map<StuffCode, ITEMINFO>	m_mapItemInfo;
	SYNTHESIZE(bool, m_IsStartedGame, IsStartedGame)
	SYNTHESIZE(bool, m_IsInvenOpen, IsInvenOpen)

public:


	void SetItemInfo();
};

