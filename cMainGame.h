#pragma once
class cCamera;
class cGroup;			//17.05.30 최진호 추가


class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	cCamera*		m_pCamera;
	//map
	std::vector<cGroup*> m_vecGroup;	//17.05.30 추가 최진호
	//character
	



public:
	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	

	//>>: 맵 오브젝트 셋팅 작성자:최진호 	작성일: 17_05_30
	void Setup_Obj();
	void Render_Obj();


	//light
	void Set_Light();
};

