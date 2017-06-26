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
	LPD3DXFONT				m_fontName;								//폰트
	HWND					m_hWndNaming;							//이름입력핸들
	string					m_strChat;								//이름입력 스트링

	cUIObject*				m_pRoot;								//부모클래스
	LPD3DXSPRITE			m_pSprite;								//스프라이트
	int						m_nMyChat;								//챗넘버
public:
	void Setup();
	void Update();
	void Render();
	void SetChildWindow();						//차일드 윈도우 생성
	void ChatOnOff();							//챗 온오프시 행동
	void RenderChat();							//챗 렌더
	void SetBackground();						//채팅 UI세팅
	void PushChat();							//조건에 맞는 채팅 푸쉬

	//소켓용
	void Setup(int nHandle, int startX, int startY, int Width, int Height);
	void Update_ForSocket();
	void Render(int startX, int startY, int Width, int Height);
	void SetChildWindow(int nHandle, int startX, int startY, int Width, int Height);	
	void RenderChat(int startX, int startY, int Width, int Height);


};

