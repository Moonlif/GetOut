#include "stdafx.h"
#include "cDataManager.h"


cDataManager::cDataManager()
{
}


cDataManager::~cDataManager()
{
}

D3DXVECTOR3 cDataManager::GetPosition(int nIndex)
{
	if (m_vecPosition.size() - 1 < nIndex)
		return D3DXVECTOR3(0, 0, 0);

	return m_vecPosition[nIndex];
}
