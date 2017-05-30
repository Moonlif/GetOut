#pragma once
class cGroup;			//17.05.30 최진호 추가

class cMapObject
{
private:
	std::vector<cGroup*> m_vecGroup;	//17.05.30 추가 최진호
public:
	cMapObject();
	~cMapObject();
public:
	void Setup();
	void Render();
};

