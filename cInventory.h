#pragma once
class cUIObject;
class cUIInvenItem;
#include "cUIButton.h"

class cInventory : public iButtonDelegate
{
public:
	cInventory();
	~cInventory();

private:
	cUIObject*				m_pUIBase;				//��ü �κ��丮 ���̽� �θ�
	cUIInvenItem*			m_pInven;				//������ �÷����� ���� ������ �ִ� �θ�

	LPD3DXSPRITE			m_pSprite;				//��������Ʈ
	
	//�κ� ������ ������ �̵���
	bool					m_IsPick;				//���߳�? ���߳�?
	StuffCode				FirstCode, SecondCode;	//ù���� ������ �ڵ�� �ڸ��ٲ� �κ��� �������ڵ�

	//���콺 �����Ϳ� �ű� ������ ����
	LPDIRECT3DTEXTURE9		m_pTexture;				//�ؽ���
	RECT					m_rcItem;				//��Ʈ

public:
	void Setup();
	void Update();
	void Render();

	void SetInventoryBase();					//ù �κ��丮 ����
	void SetItem(StuffCode ItemName);			//������ ����� �θ��� �Լ�

	void MoveItem();							//������ Ŭ�� �� �̵���
	void PickedRender();						//������ Ŭ�� �� ���콺�����Ϳ� ����
	eUITAG CarcCuruntPtInven();					//���� Ŭ���� ���� �� �� �κ��丮���� ����ϴ� �Լ�
	StuffCode GetPreparedUsingItem();			//���� ����� �������� ��������ΰ�?

	void SaveInvenInfo();						//�κ��丮 ���̺�
	void LoadInvenInfo();						//�κ��丮 �ε�

	virtual void OnClick(cUIButton* pSender);	//����Ŭ����
};

