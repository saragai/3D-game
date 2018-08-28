/*
winmain.cpp

(c) 2018 Saragai Takanori
*/
#define STRICT
#define WIN32_LEAN_AND_MEAN

// for detecting memory leak
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "define.h"

bool ThereIsAnotherInstance()
{
	HANDLE ourMutex;
	ourMutex = CreateMutex(
		NULL,
		true,
		"This_is_a_practice_of_3D_programming");
	
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		return true;
	return false;
}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{

	// for detecting memory leak
#if defined(DEBUG) |defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	if (ThereIsAnotherInstance())
		return 1;

	MSG msg;
	HWND hWnd;
	if (!CreateMainWindow(hWnd, hInstance, nCmdShow))
		return 1;

	Graphics *graphics = new Graphics;
	try {
		graphics->Initialize(hWnd, constant::WIDTH, constant::HEIGHT, constant::IS_FULLSCREEN);

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
			else
			{
				graphics->ShowBackbuffer();
			}
		}
		SAFE_DELETE(graphics);
	}
	catch (GameError &gameError) 
	{
		switch(gameError.getErrorCode())
		{
		case FATAL_ERROR:
			MessageBox(NULL, gameError.getMessage(), "Fatal Error", MB_OK);
			break;
		case WARNING:
			MessageBox(NULL, gameError.getMessage(), "WARNING", MB_OK);
			break;
		}
	}
	catch (...)
	{
		MessageBox(NULL, "Unknown error occured", "Error", MB_OK);
	}

	SAFE_DELETE(graphics);
	return 0;
}
