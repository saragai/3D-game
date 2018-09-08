/*
graphics.h

(c) 2018 Saragai Takanori
*/

#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "constant.h"
#include "game_error.h"
#include "safe.h"

#define COLOR DWORD
#define SET_COLOR(a,r,g,b) ((COLOR)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define SET_COLOR(a,r,g) SET_COLOR(0,r,g,b)

class Graphics 
{
private:
	LPDIRECT3D9 m_Direct3d;
	LPDIRECT3DDEVICE9 m_D3DDevice;
	D3DPRESENT_PARAMETERS m_D3DPresentParameters;
	D3DDISPLAYMODE m_D3DDisPlayMode;

	HWND m_HWnd;
	bool m_IsFullscreen;
	int m_Width;
	int m_Height;
	COLOR m_BackColor;
	
	void _InitD3Dpp();

public:
	Graphics();
	virtual ~Graphics();
	void ReleaseAll();

	void Initialize(HWND hwnd, int width, int height, bool isFullscreen);
	HRESULT ShowBackbuffer();

	bool IsAdapterCompatible();
	HRESULT ResetGraphicDevice();
	HRESULT GetDeviceState();


	HRESULT BeginScene()
	{
		if (m_D3DDevice == NULL)
			return E_FAIL;

		m_D3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, m_BackColor, 1.0f, 0);
		return m_D3DDevice->BeginScene();
	}

	HRESULT EndScene()
	{
		if (m_D3DDevice == NULL)
			return E_FAIL;

		return m_D3DDevice->EndScene();
	}
};