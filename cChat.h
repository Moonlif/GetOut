#pragma once
#include "cObject.h"
class cUIObject;

class cChat : public cObject
{
public:
	cChat();
	~cChat();

private:
	LPD3DXFONT				m_fontName;
	HWND					m_hWndNaming;								//이름입력핸들
	string					m_strChat;								//이름입력 스트링


	cUIObject*				m_pRoot;
	LPD3DXSPRITE			m_pSprite;
public:
	void Setup();
	void Update();
	void Render();

	void SetChildWindow();
	void ChatOnOff();
	void RenderChat();

	void SetBackground();
};

