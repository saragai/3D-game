/*
game.cpp

(c) 2018 Saragai Takanori
*/
#include "game.h"

Game::Game()
{
	m_Input = new Input();
	m_IsPaused = false;
	m_IsInitialized = false;
}

Game::~Game()
{
	DeleteAll();
	ShowCursor(true);
}

LRESULT Game::HandleWindowsMessage(HWND a_hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	if (!m_IsInitialized)
		return DefWindowProc(a_hWnd, msg, wParam, lParam);
	
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		m_Input->KeyDown(wParam);
		return 0;

	case WM_KEYUP:
	case WM_SYSKEYUP:
		m_Input->KeyUp(wParam);
		return 0;

	case WM_MOUSEMOVE:
		m_Input->MouseInput(lParam);
		return 0;

	case WM_INPUT:
		m_Input->MouseRawInput(lParam);
		return 0;

	case WM_LBUTTONDOWN:
		m_Input->SetMouseLButton(true);
		return 0;

	case WM_LBUTTONUP:
		m_Input->SetMouseLButton(false);
		return 0;

	case WM_MBUTTONDOWN:
		m_Input->SetMouseMButton(true);
		return 0;

	case WM_MBUTTONUP:
		m_Input->SetMouseMButton(false);
		return 0;

	case WM_RBUTTONDOWN:
		m_Input->SetMouseRButton(true);
		return 0;

	case WM_RBUTTONUP:
		m_Input->SetMouseRButton(false);
		return 0;

	case WM_XBUTTONDOWN:
		m_Input->SetMouseXButton(true);
		return 0;
		
	case WM_XBUTTONUP:
		m_Input->SetMouseXButton(false);
		return 0;

	default:
		return DefWindowProc(a_hWnd, msg, wParam, lParam);
	}
}

void Game::Initialize(HWND hWnd)
{
	m_HWnd = hWnd;
	m_Graphics = new Graphics();
	m_Graphics->Initialize(
		m_HWnd,
		constant::WIDTH,
		constant::HEIGHT, 
		constant::IS_FULLSCREEN);

	m_Input->Initialize(m_HWnd, false);

	if (QueryPerformanceFrequency(&m_TimerFreq) == false)
	{
		throw(GameError(FATAL_ERROR, "Error initializing high resolution timer"));
	}
	QueryPerformanceCounter(&m_TimeStart);
	m_IsInitialized = true;
}

void Game::Run()
{
	if (m_Graphics == NULL)
	{
		throw(GameError(FATAL_ERROR, "Error graphics is null in Game::Run"));
	}

	QueryPerformanceCounter(&m_TimeEnd);
	m_FrameTime = (float)(m_TimeEnd.QuadPart - m_TimeStart.QuadPart)
		/ (float)m_TimerFreq.QuadPart;

	if (m_FrameTime < constant::MIN_FRAME_TIME)
	{
		m_SleepTime = (DWORD)((constant::MIN_FRAME_TIME - m_FrameTime));
		timeBeginPeriod(1);
		Sleep(m_SleepTime);
		timeEndPeriod(1);
	}

	if (m_FrameTime > 0.0)
		m_Fps = (m_Fps * 0.99f) + (0.01f / m_FrameTime);

	if (!m_IsPaused)
	{
		Update();
		Ai();
		Collide();
	}
	RenderGame();

	
}

void Game::ReleaseAll()
{

}

void Game::ResetAll()
{

}

void Game::DeleteAll()
{
	ReleaseAll();
	SAFE_DELETE(m_Graphics);
	SAFE_DELETE(m_Input);
	m_IsInitialized = false;
}

void Game::RenderGame()
{
	if (SUCCEEDED(m_Graphics->BeginScene()))
	{
		Render();
		m_Graphics->EndScene();
	}
	_HandleLostGraphicDevice();
	m_Graphics->ShowBackbuffer();
}

void Game::_HandleLostGraphicDevice()
{
	HRESULT hResult = m_Graphics->GetDeviceState();
	if (FAILED(hResult))
	{
		switch (hResult)
		{
		case D3DERR_DEVICELOST:
			Sleep(100);
			return;

		case D3DERR_DEVICENOTRESET:
			ReleaseAll();
			hResult = m_Graphics->ResetGraphicDevice();
			if (FAILED(hResult))
				return;
			ResetAll();
			break;
		default:
			return;
		}
	}
}