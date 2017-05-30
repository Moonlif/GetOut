#pragma once
class cCamera;
class cGroup;			//17.05.30 ����ȣ �߰�


class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	cCamera*		m_pCamera;
	//map
	std::vector<cGroup*> m_vecGroup;	//17.05.30 �߰� ����ȣ
	//character
	



public:
	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	

	//>>: �� ������Ʈ ���� �ۼ���:����ȣ 	�ۼ���: 17_05_30
	void Setup_Obj();
	void Render_Obj();


	//light
	void Set_Light();
};

