#pragma once
#include "stdafx.h"

#define g_pData cDataManager::GetInstance()

class cDataManager
{
private:
	SINGLETONE(cDataManager);

public:
	//����
	//ex) D3DXVECTOR3 v!p_position;
};

