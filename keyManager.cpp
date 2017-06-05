#include "stdafx.h"
#include "keyManager.h"
keyManager::keyManager()
{
}
keyManager::~keyManager()
{
}

//키매니져 초기화
HRESULT keyManager::init(void)
{
	//키값을 전부 눌려있지 않은 상태로 초기화 한다
	for (int i = 0; i < KEYMAX; i++)
	{
		this->getKeyUp().set(i, false);
		this->getKeyDown().set(i, false);
	}
	return S_OK;
}

//키매니져 해제
void keyManager::release(void)
{
}

//키가 한번만 눌렸냐?
bool keyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->getKeyDown()[key])
		{
			this->setKeyDown(key, true);
			return true;
		}
	}
	else
	{
		this->setKeyDown(key, false);
	}

	return false;
}

//키가 한번 눌렀다 띄었냐?
bool keyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		this->setKeyUp(key, true);

	}
	else
	{
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, false);
			return true;
		}
	}

	return false;
}

//키가 계속 눌려져 있냐?
bool keyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}

//토글키(넘버락, 캡스락, 스위치)
bool keyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}
