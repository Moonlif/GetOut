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
		POINT	setMouse;
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

	//마우스 커서 관련 테스트
	//if (g_pData->GetIsStartedGame() && !isMouseView) SetCursor(NULL); // 마우스를 나타나지 않게 않다.
	/*if (g_pKeyManager->isStayKeyDown('I'))
	{
		if(isMouseView == true) isMouseView = false;
		else if (isMouseView == false)
		{
			POINT	setMouse;
			setMouse.x = (rc.right - rc.left) / 2;
			setMouse.y = (rc.bottom - rc.top) / 2;
			ClientToScreen(g_hWnd, &setMouse);
			SetCursorPos(setMouse.x, setMouse.y);
			isMouseView = true;
		}
	}*/

	D3DXMATRIXA16 matR, matRX, matRY;
	D3DXMatrixRotationX(&matRX, m_vCamRotAngle.x);
	D3DXMatrixRotationY(&matRY, m_vCamRotAngle.y);
	matR = matRX * matRY;

	m_vEye = D3DXVECTOR3(0, m_fCameraHeight, -m_fCameraDistance);
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matR);

	if (m_pvTarget)
	{
		m_vLookAt = *m_pvTarget;
		m_vEye = m_vEye + *m_pvTarget;
	}

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);

	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
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

		if (m_isLButtonDown)
		{
			float fDeltaX = (float)g_ptMouse.x - m_ptPrevMouse.x;
			float fDeltaY = (float)g_ptMouse.y - m_ptPrevMouse.y;

			m_vCamRotAngle.y -= (fDeltaX / 100.f);
			m_vCamRotAngle.x -= (fDeltaY / 100.f);

			if (m_vCamRotAngle.x > D3DX_PI / 3.0f)  m_vCamRotAngle.x = D3DX_PI / 3.0f;
			if (m_vCamRotAngle.x < -D3DX_PI / 2.0f)  m_vCamRotAngle.x = -D3DX_PI / 2.0f;

			m_ptPrevMouse = g_ptMouse;
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
