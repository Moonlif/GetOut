#pragma once
#include "cObjLoader.h"
#include "cGroup.h"						//17.05.30 최진호 추가
#include "cObject.h"

class cMapObject
{
private:
	std::vector<cGroup*> m_vecGroup;	//17.05.30 추가 최진호
public:
	cMapObject();
	~cMapObject();
public:
	void Setup(char* folder ,char* fileName);
	void Render(float size, float x, float y, float z);
};

