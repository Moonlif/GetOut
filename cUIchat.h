#pragma once
#include "cUIObject.h"

class cUIchat : public cUIObject
{
public:
	cUIchat();
	cUIchat(D3DXVECTOR3 pos);
	virtual~cUIchat();

private:
	SYNTHESIZE(vector<CHATINFO>, m_vChat, Chat)				//���Ϳ� ä�� ����
	LPD3DXFONT					 m_pFont;					//��Ʈ
				
	LPDIRECT3DTEXTURE9			 m_pTexture;				//�ؽ���
public:
	virtual void Update() override;
	virtual void Render(LPD3DXSPRITE pSprite) override;
	void PushChat(string str, int Gender);					//ä��Ǫ��(ä�ó���, �����ƴ��� ����or player)
};

