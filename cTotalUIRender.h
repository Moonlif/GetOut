#pragma once

class cStartScene;

class cTotalUIRender
{
public:
	cTotalUIRender();
	~cTotalUIRender();

private:
	cStartScene*		m_pStartScene;


public:
	void Setup();
	void Update();
	void Render();
};

