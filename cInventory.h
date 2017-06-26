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
	cUIObject*				m_pUIBase;				//전체 인벤토리 베이스 부모
	cUIInvenItem*			m_pInven;				//아이템 올려놓는 곳만 가지고 있는 부모

	LPD3DXSPRITE			m_pSprite;				//스프라이트
	
	//인벤 내에서 아이템 이동시
	bool					m_IsPick;				//픽했냐? 안했냐?
	StuffCode				FirstCode, SecondCode;	//첫픽한 아이템 코드와 자리바뀔 부분의 아이템코드

	//마우스 포인터에 옮길 아이템 렌더
	LPDIRECT3DTEXTURE9		m_pTexture;				//텍스쳐
	RECT					m_rcItem;				//렉트

public:
	void Setup();
	void Update();
	void Render();

	void SetInventoryBase();					//첫 인벤토리 세팅
	void SetItem(StuffCode ItemName);			//아이템 습득시 부르는 함수

	void MoveItem();							//아이템 클릭 후 이동시
	void PickedRender();						//아이템 클릭 후 마우스포인터에 렌더
	eUITAG CarcCuruntPtInven();					//현재 클릭한 곳이 몇 번 인벤토리인지 계산하는 함수
	StuffCode GetPreparedUsingItem();			//현재 사용할 아이템이 어떤아이템인가?

	void SaveInvenInfo();						//인벤토리 세이브
	void LoadInvenInfo();						//인벤토리 로드

	virtual void OnClick(cUIButton* pSender);	//조합클릭시
};

