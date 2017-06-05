#pragma once
#include <bitset>
using namespace std;

#define g_pKeyManager keyManager::GetInstance()

//==================================================================
//		## keyManager ## ()
//==================================================================

#define KEYMAX 256

class keyManager
{
private:
	SINGLETONE(keyManager);

	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;

public:
	HRESULT init(void);
	void release(void);

	//키가 한번만 눌렸냐?
	bool isOnceKeyDown(int key);
	//키가 한번 눌렀다 띄었냐?
	bool isOnceKeyUp(int key);
	//키가 계속 눌려져 있냐?
	bool isStayKeyDown(int key);
	//토글키(넘버락, 캡스락, 스위치)
	bool isToggleKey(int key);

	//겟터
	bitset<KEYMAX> getKeyUp() { return _keyUp; }
	bitset<KEYMAX> getKeyDown() { return _keyDown; }
	//셋터
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }
	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }

	/*keyManager();
	~keyManager();*/
};

