#pragma once
#include "stdafx.h"

#define g_pDataManager cDataManager::GetInstance()

class cDataManager
{
private:
	SINGLETONE(cDataManager);

	std::vector<D3DXVECTOR3> m_vecPosition;
public:
	D3DXVECTOR3 GetPosition(int nIndex);
};

