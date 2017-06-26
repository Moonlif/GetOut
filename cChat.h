#pragma once
#include "cObject.h"
class cUIObject;
class cUIButton;

class cChat : public cObject
{
public:
	cChat();
	~cChat();

private:
	LPD3DXFONT				m_fontName;								//��Ʈ
	HWND					m_hWndNaming;							//�̸��Է��ڵ�
	string					m_strChat;								//�̸��Է� ��Ʈ��

	cUIObject*				m_pRoot;								//�θ�Ŭ����
	LPD3DXSPRITE			m_pSprite;								//��������Ʈ
	int						m_nMyChat;								//ê�ѹ�
public:
	void Setup();
	void Update();
	void Render();
	void SetChildWindow();						//���ϵ� ������ ����
	void ChatOnOff();							//ê �¿����� �ൿ
	void RenderChat();							//ê ����
	void SetBackground();						//ä�� UI����
	void PushChat();							//���ǿ� �´� ä�� Ǫ��

	//���Ͽ�
	void Setup(int nHandle, int startX, int startY, int Width, int Height);
	void Update_ForSocket();
	void Render(int startX, int startY, int Width, int Height);
	void SetChildWindow(int nHandle, int startX, int startY, int Width, int Height);	
	void RenderChat(int startX, int startY, int Width, int Height);


};

