#pragma once


#define g_pUIvarius cUI_globalVarius::GetInstance() // <<

class cUI_globalVarius
{
//public:
//	cUI_globalVarius();
//	~cUI_globalVarius();
	
private:
	SINGLETONE(cUI_globalVarius);	
	SYNTHESIZE(eITEMTYPE,			m_CurClickItemType, CurClickItemType)
	

public:
	map<StuffCode, ITEMINFO>	m_mapItemInfo;
	D3DXMATRIXA16				m_matCameraRot;

	ITEMINFO GetItemInfo(StuffCode ItemName);
	void SetItemInfo();

	void SetItem(eITEMTYPE itemType, StuffCode itemCode, char* fullPath);

};

