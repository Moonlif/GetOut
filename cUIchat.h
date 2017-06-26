#pragma once
#include "cUIObject.h"

class cUIchat : public cUIObject
{
public:
	cUIchat();
	cUIchat(D3DXVECTOR3 pos);
	virtual~cUIchat();

private:
	SYNTHESIZE(vector<CHATINFO>, m_vChat, Chat)				//벡터에 채팅 저장
	LPD3DXFONT					 m_pFont;					//폰트
				
	LPDIRECT3DTEXTURE9			 m_pTexture;				//텍스쳐
public:
	virtual void Update() override;
	virtual void Render(LPD3DXSPRITE pSprite) override;
	void PushChat(string str, int Gender);					//채팅푸쉬(채팅내용, 누가쳤는지 성별or player)
};

