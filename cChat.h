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
	LPD3DXFONT				m_fontName;
	HWND					m_hWndNaming;							//이름입력핸들
	string					m_strChat;								//이름입력 스트링

	cUIObject*				m_pRoot;
	LPD3DXSPRITE			m_pSprite;
public:
	void Setup();
	void Setup(int nHandle, int startX, int startY, int Width, int Height);
	void Update();
	void Update_ForSocket();
	void Render();
	void Render(int startX, int startY, int Width, int Height);

	void SetChildWindow();
	void SetChildWindow(int nHandle, int startX, int startY, int Width, int Height);
	void ChatOnOff();
	void RenderChat();
	void RenderChat(int startX, int startY, int Width, int Height);

	void CopyToSock();
	void SetBackground();
};

