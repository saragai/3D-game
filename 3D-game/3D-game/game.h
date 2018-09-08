/*
game.h

(c) 2018 Saragai Takanori
*/
#pragma once

#include "graphics.h"
#include "input.h"

#include "constant.h"
#include "game_error.h"
#include "safe.h"

class Game
{
private:
	virtual void _HandleLostGraphicDevice();

protected:
	Graphics *m_Graphics;
	Input *m_Input;
	HWND m_HWnd;
	HRESULT m_HResult;

	// for performance counter
	LARGE_INTEGER m_TimeStart;
	LARGE_INTEGER m_TimeEnd;
	LARGE_INTEGER m_TimerFreq;

	float m_FrameTime;
	float m_Fps;
	DWORD m_SleepTime;
	bool m_IsPaused;
	bool m_IsInitialized;

public:
	Game();
	virtual ~Game();

	LRESULT HandleWindowsMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	virtual void Initialize(HWND hWnd);
	virtual void Run();
	virtual void ReleaseAll();
	virtual void ResetAll();
	virtual void DeleteAll();
	virtual void RenderGame();

	// Accessor
	Graphics* getGraphics() { return m_Graphics; }
	Input* getInput() { return m_Input; }
	
	void Exit() { PostMessage(m_HWnd, WM_DESTROY, 0, 0); }

	// Pure virtual function
	virtual void Update() = 0;
	virtual void Ai() = 0;
	virtual void Collide() = 0;
	virtual void Render() = 0;
};