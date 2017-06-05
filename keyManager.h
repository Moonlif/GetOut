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

	//Ű�� �ѹ��� ���ȳ�?
	bool isOnceKeyDown(int key);
	//Ű�� �ѹ� ������ �����?
	bool isOnceKeyUp(int key);
	//Ű�� ��� ������ �ֳ�?
	bool isStayKeyDown(int key);
	//���Ű(�ѹ���, ĸ����, ����ġ)
	bool isToggleKey(int key);

	//����
	bitset<KEYMAX> getKeyUp() { return _keyUp; }
	bitset<KEYMAX> getKeyDown() { return _keyDown; }
	//����
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }
	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }

	/*keyManager();
	~keyManager();*/
};

