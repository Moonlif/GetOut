#pragma once
class cGroup;			//17.05.30 ����ȣ �߰�

class cMapObject
{
private:
	std::vector<cGroup*> m_vecGroup;	//17.05.30 �߰� ����ȣ
public:
	cMapObject();
	~cMapObject();
public:
	void Setup();
	void Render();
};

