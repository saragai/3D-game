/*
video-driver.h

(c) 2018 Saragai Takanori
*/

#pragma once

#include <Windows.h>

bool CreateMainWindow(HWND &, HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);

