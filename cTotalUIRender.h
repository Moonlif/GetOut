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
	cStartScene*						m_pStartScene;						//스타트씬 클래스
	cCharacterSelectScene*				m_pChaSelectScene;					//캐릭터 셀렉씬 클래스
	cInventory*							m_pInventory;						//인벤토리 클래스
	cChat*								m_pChat;							//채팅 클래스
	cGamePlay_UI*						m_pGamePlay;						//게임플레이UI 클래스
	cEnding*							m_pEnding;							//엔딩씬 클래스
	
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_pCamraStartPos, CamraStartPos);	//첫 카메라 포지션 잡아주는 변수

	LPD3DXFONT							m_pFontWarning;						//경고문구 띄울 폰트
public:
	void Setup();
	void Update(cCamera* camera);
	void Render();

	//Press Any Key 받아오기 위한 함수
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	//아이템 습득시 부르는 함수
	void SetItem(StuffCode ItemName);

	//현재 사용아이템에 어떤 아이템이 올라와 있는지 판단하는 함수
	StuffCode GetPreparedUsingItem();
	
	//경고문구 제한시간 카운트
	void LimitWarningTextCount();
};

