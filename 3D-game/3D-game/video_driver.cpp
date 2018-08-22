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
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool CreateMainWindow(HINSTANCE hInstance, int nCmdShow) 
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
		wcx.lpszClassName = "WinMain";
		wcx.hIconSm = NULL;
	if (RegisterClassEx(&wcx) == 0)
		return false;

	HWND hwnd;
	hwnd = CreateWindow(
		"WinMain",
		"WinMain",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		400,
		400,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hwnd)
		return false;

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	return true;
}

