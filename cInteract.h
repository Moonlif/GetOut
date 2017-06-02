#pragma once
class cStuff;
class cTrigger;

class cInteract
{
public:
	cInteract();
	~cInteract();

private:
	std::vector<cStuff*> m_vecStuff;
	std::vector<cTrigger*> m_vecTrigger;

public:
	void Setup();
	void Update();
	void Render();
};

