#pragma once

#include "cStuff.h"

class cInteract
{
public:
	cInteract();
	~cInteract();

private:
	std::vector<cStuff*> m_vecStuff;

	int m_n1FBlockCount;
	int m_n2FValve1Count;
	int m_n2FValve2Count;

public:
	void Setup();
	void Update();
	void Render();
};

