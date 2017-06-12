#pragma once
#include "cUIObject.h"

class cUIchat : public cUIObject
{
public:
	cUIchat();
	cUIchat(D3DXVECTOR3 pos);
	virtual~cUIchat();

private:
	SYNTHESIZE(vector<CHATINFO>, m_vChat, Chat)
	LPD3DXFONT					 m_pFont;

public:
	virtual void Update() override;
	virtual void Render(LPD3DXSPRITE pSprite) override;
	void PushChat(string str);
};

