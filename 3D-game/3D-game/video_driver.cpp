/*
video_driver.cpp

(c) 2018 Saragai Takanori
*/
#include "define.h"

LRESULT WINAPI WinProc(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool CreateMainWindow(HWND &hWnd, HINSTANCE hInstance, int nCmdShow) 
{
	WNDCLASSEX wcx;
		wcx.cbSize = sizeof(wcx);
		wcx.style = CS_HREDRAW | CS_VREDRAW;
		wcx.lpfnWndProc = WinProc;
		wcx.cbClsExtra = 0;
		wcx.cbWndExtra = 0;
		wcx.hInstance = hInstance;
		wcx.hIcon = NULL;
		wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wcx.lpszMenuName = NULL;
		wcx.lpszClassName = constant::GAME_NAME;
		wcx.hIconSm = NULL;
	if (RegisterClassEx(&wcx) == 0)
		return false;

	hWnd = CreateWindow(
		constant::GAME_NAME,
		constant::GAME_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		constant::WIDTH,
		constant::HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hWnd)
		return false;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return true;
}

