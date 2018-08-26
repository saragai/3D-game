/*
graphics.h

(c) 2018 Saragai Takanori
*/

#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class Graphics 
{
private:
	LPDIRECT3D9 direct3d;
	LPDIRECT3DDEVICE9 device3d;
	D3DPRESENT_PARAMETERS d3dpp;

	HRESULT hResult;
	HWND hWnd;
	bool isFullscreen;
	int width;
	int height;
	
	void _InitD3Dpp();

public:
	Graphics();
	virtual ~Graphics();
	void ReleaseAll();

	void Initialize(HWND hwnd, int width, int height, bool isFullscreen);
	HRESULT ShowBackbuffer();
};