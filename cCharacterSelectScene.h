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
	//배경관련
	cUIObject*							m_pRoot;							//셀렉창 캐릭터와 관련된 오브젝트를 제외한 모든 차일드를 담을 변수

	//플레이어 관련
	cUIObject*							m_pPlayer1;							//1번 캐릭터 UI(캐릭터, 조명 등)
	cUIObject*							m_pPlayer2;							//2번 캐릭터 UI

	//스프라이트
	LPD3DXSPRITE						m_pSprite;							//스프라이트

	//카메라 이동 관련
	cUIObject*							m_pGameStart;						//게임스타트 누를시 로딩씬 이미지를 담은 변수
	bool								m_isDeleteBackground;				//게임시작 버튼 누른 타이밍변수
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vRetargetPos, mRetargetPos)		//카메라 리타겟 포지션
	cCamera*							m_pCamera;							//카메라

	//어떤 캐릭 선택했나?
	bool								m_isSelect;							//어떤 캐릭터든 클릭했냐 안했냐?		
public:
	void Setup();
	void Update(cCamera* camera);
	void Render();

	void SetBackground();									//백그라운드 세팅
	void SetMesh();											//캐릭터 메쉬, 라이트 세팅
	
	void UpdateSetFirstBackground();						//첫 셀렉씬 로딩시 알파값 서서히 선명하게 됨
	void UpdateCharacterSelect();							//캐릭터 선택에 따른 렌더할값 변경
	void UpdateBeforGameStart();							//게임 시작전 이미지 교체 함수
	void DeleteBackground();								//케릭터 셀렉씬 UI 알파값으로 서서히 없어짐.

};

