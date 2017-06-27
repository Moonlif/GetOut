#pragma once

class cUIObject;
class cUITextView;
class cUIImageView;

class cStartScene
{
public:
	cStartScene();
	~cStartScene();
private:
	cUIObject*				m_pStartSceneRoot;				//�θ�
	cUIImageView*			m_pStartSceneImage;				//��ŸƮ���̹���
	LPD3DXSPRITE			m_pSprite;						//��������Ʈ

	cUITextView*			m_pStartText;					//�ؽ�Ʈ

	SYNTHESIZE(bool,		m_IsStartSceneOpen, IsStartSceneOpen);
public:
	void Setup();
	void Update();
	void Render();


	void WndProc(UINT message);
};

