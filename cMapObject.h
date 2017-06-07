#pragma once
#include "cObjLoader.h"
#include "cGroup.h"						//17.05.30 ����ȣ �߰�
#include "cObject.h"

class cMapObject
{
private:
	std::vector<cGroup*> m_vecGroup;	//17.05.30 �߰� ����ȣ
public:
	cMapObject();
	~cMapObject();
public:
	void Setup(char* folder ,char* fileName);
	void Render(float size, float x, float y, float z);
};

