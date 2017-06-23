#include "stdafx.h"
#include "cCamera.h"


cCamera::cCamera()
	: m_vEye(0, 5, -5)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_pvTarget(NULL)
	, m_fCameraDistance(5.0f)
	, m_isLButtonDown(false)
	, m_vCamRotAngle(0, 0, 0)
	, m_fCameraHeight(0)
	, isMouseView(false)
	, isMouseInit(false)
{
	m_ptPrevMouse.x = 0;
	m_ptPrevMouse.y = 0;
}


cCamera::~cCamera()
{
}

void cCamera::Setup(D3DXVECTOR3 * pvTarget)
{
	m_pvTarget = pvTarget;

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	{
		// 마우스를 윈도우의 중앙으로 초기화
		POINT   setMouse;
		setMouse.x = (rc.right - rc.left) / 2;
		setMouse.y = (rc.bottom - rc.top) / 2;
		ClientToScreen(g_hWnd, &setMouse);
		SetCursorPos(setMouse.x, setMouse.y);
	}
}

void cCamera::Update()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	//인벤(I버튼) 누르면 커서 나타나고 카메라 회전x
	if (g_pData->GetIsInvenOpen())
	{
		isMouseView = true;
	}
	else isMouseView = false;

	//마우스 커서 관련 테스트
	if (g_pData->GetIsStartedGame() && !isMouseView)
	{
		SetCursor(NULL); // 마우스를 나타나지 않게 한다.
						 //ClipCursor(&rc); //마우스 가두기
	}

	//벽충돌시 카메라 이동(현재 필요x)
	/*if (g_pData->GetIsCollisionWall() && g_pData->GetIsStartedGame())
	{
		m_fCameraDistance += (10.0f * g_pTimeManager->GetElapsedTime());
		if (m_fCameraDistance > 2.0f)
		{
			m_fCameraDistance = 2.0f;
		}
	}
	else if(!g_pData->GetIsCollisionWall() && g_pData->GetIsStartedGame())
	{
		m_fCameraDistance -= (10.0f * g_pTimeManager->GetElapsedTime());
		if (m_fCameraDistance < 0.0001f)
		{
			m_fCameraDistance = 0.0001f;
		}
	}*/

	D3DXMATRIXA16 matR, matRX, matRY;
	D3DXMatrixRotationX(&matRX, m_vCamRotAngle.x);
	D3DXMatrixRotationY(&matRY, m_vCamRotAngle.y);
	matR = matRX * matRY;

	g_pUIvarius->m_matCameraRot = matR;

	if (g_pData->GetIsStartedGame()) m_vEye = D3DXVECTOR3(0, m_fCameraHeight, m_fCameraDistance);
	else m_vEye = D3DXVECTOR3(0, m_fCameraHeight, -m_fCameraDistance);

	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matR);

	if (m_pvTarget)
	{
		m_vLookAt = *m_pvTarget;
		m_vEye = m_vEye + *m_pvTarget;
	}

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);

	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	//마우스가 화면밖으로 나가면 && 게임시작 && 마우스커서 꺼진상태
	if ((g_ptMouse.x <= (rc.left + 50) || (rc.right - 50) <= g_ptMouse.x ||
		g_ptMouse.y <= (rc.top + 50) || (rc.bottom - 50) <= g_ptMouse.y) &&
		g_pData->GetIsStartedGame() && !isMouseView)
	{
		// 마우스를 윈도우의 중앙으로 초기화
		POINT   setMouse;
		setMouse.x = (rc.right - rc.left) / 2;
		setMouse.y = (rc.bottom - rc.top) / 2;
		ClientToScreen(g_hWnd, &setMouse);
		SetCursorPos(setMouse.x, setMouse.y);

		//마우스 위치 초기화시 회전방지
		g_ptMouse = setMouse;
		m_ptPrevMouse = setMouse;
		isMouseInit = true;
	}
}

void cCamera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (!isMouseView)
	{
		m_isLButtonDown = true;
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
	}
	else
	{
		m_isLButtonDown = false;
	}

	switch (message)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_RBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		if (!g_pData->GetIsStartedGame()) return;
		if (isMouseInit)
		{
			isMouseInit = false;
			return;
		}

		if (m_isLButtonDown)
		{
			float fDeltaX = (float)g_ptMouse.x - m_ptPrevMouse.x;
			float fDeltaY = (float)g_ptMouse.y - m_ptPrevMouse.y;

			m_vCamRotAngle.y -= (fDeltaX / 140.f);
			m_vCamRotAngle.x += (fDeltaY / 140.f);

			if (m_vCamRotAngle.x > D3DX_PI / 2.8f)  m_vCamRotAngle.x = D3DX_PI / 2.8f;
			if (m_vCamRotAngle.x < -D3DX_PI / 3.2f)  m_vCamRotAngle.x = -D3DX_PI / 3.2f;

			m_ptPrevMouse = g_ptMouse;

			//g_pData->m_vRotation1P = m_vCamRotAngle.y;
			g_pData->Set1PRotation(m_vCamRotAngle.y);
		}
		break;
	case WM_MOUSEWHEEL:
		if (!g_pData->GetIsStartedGame()) return;

		//카메라 줌 인아웃
		m_fCameraDistance -= (GET_WHEEL_DELTA_WPARAM(wParam) / 120.f);
		if (m_fCameraDistance < 0.0001f)
			m_fCameraDistance = 0.0001f;
		if (m_fCameraDistance > 100.0f)
			m_fCameraDistance = 100.0f;
		break;
	}
}

void cCamera::ReTarget(D3DXVECTOR3 * pvTarget)
{
	m_pvTarget = pvTarget;
}