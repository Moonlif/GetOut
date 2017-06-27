#pragma once

class cUIObject;
class cCamera;

#define IMAGECHANGESPEED 12
#define CAMERASHAKESPEED 5
#define CAMERASHAKERANGE 0.5f
#define DELETEBACKGROUNDSPEED 4
#define SETBACKGROUNDSPEED 4

class cCharacterSelectScene
{
public:
	cCharacterSelectScene();
	~cCharacterSelectScene();

private:
	//������
	cUIObject*							m_pRoot;							//����â ĳ���Ϳ� ���õ� ������Ʈ�� ������ ��� ���ϵ带 ���� ����

	//�÷��̾� ����
	cUIObject*							m_pPlayer1;							//1�� ĳ���� UI(ĳ����, ���� ��)
	cUIObject*							m_pPlayer2;							//2�� ĳ���� UI

	//��������Ʈ
	LPD3DXSPRITE						m_pSprite;							//��������Ʈ

	//ī�޶� �̵� ����
	cUIObject*							m_pGameStart;						//���ӽ�ŸƮ ������ �ε��� �̹����� ���� ����
	bool								m_isDeleteBackground;				//���ӽ��� ��ư ���� Ÿ�ֺ̹���
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vRetargetPos, mRetargetPos)		//ī�޶� ��Ÿ�� ������
	cCamera*							m_pCamera;							//ī�޶�

	//� ĳ�� �����߳�?
	bool								m_isSelect;							//� ĳ���͵� Ŭ���߳� ���߳�?		
public:
	void Setup();
	void Update(cCamera* camera);
	void Render();

	void SetBackground();									//��׶��� ����
	void SetMesh();											//ĳ���� �޽�, ����Ʈ ����
	
	void UpdateSetFirstBackground();						//ù ������ �ε��� ���İ� ������ �����ϰ� ��
	void UpdateCharacterSelect();							//ĳ���� ���ÿ� ���� �����Ұ� ����
	void UpdateBeforGameStart();							//���� ������ �̹��� ��ü �Լ�
	void DeleteBackground();								//�ɸ��� ������ UI ���İ����� ������ ������.

};

