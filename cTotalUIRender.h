#pragma once

class cStartScene;
class cCharacterSelectScene;
class cCamera;
class cInventory;
class cChat;
class cGamePlay_UI;
class cEnding;

class cTotalUIRender
{
public:
	cTotalUIRender();
	~cTotalUIRender();

private:
	cStartScene*						m_pStartScene;						//��ŸƮ�� Ŭ����
	cCharacterSelectScene*				m_pChaSelectScene;					//ĳ���� ������ Ŭ����
	cInventory*							m_pInventory;						//�κ��丮 Ŭ����
	cChat*								m_pChat;							//ä�� Ŭ����
	cGamePlay_UI*						m_pGamePlay;						//�����÷���UI Ŭ����
	cEnding*							m_pEnding;							//������ Ŭ����
	
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_pCamraStartPos, CamraStartPos);	//ù ī�޶� ������ ����ִ� ����

	LPD3DXFONT							m_pFontWarning;						//����� ��� ��Ʈ
public:
	void Setup();
	void Update(cCamera* camera);
	void Render();

	//Press Any Key �޾ƿ��� ���� �Լ�
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//������ ����� �θ��� �Լ�
	void SetItem(StuffCode ItemName);

	//���� �������ۿ� � �������� �ö�� �ִ��� �Ǵ��ϴ� �Լ�
	StuffCode GetPreparedUsingItem();
	
	//����� ���ѽð� ī��Ʈ
	void LimitWarningTextCount();
};

