/*
winmain.cpp

(c) 2018 Saragai Takanori
*/
#define STRICT
#define WIN32_LEAN_AND_MEAN

#include "video-driver.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	MSG msg;
	if (!CreateMainWindow(hInstance, nCmdShow))
		return false;

	bool done = true;
	while (done)
	{
		if (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				done = false;

			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}
	return msg.wParam;
}
