/*
graphics.cpp

(c) 2018 Saragai Takanori
*/

#include "define.h"

Graphics::Graphics()
{
	direct3d = NULL;
	device3d = NULL;
	isFullscreen = false;
	width = constant::WIDTH;
	height = constant::HEIGHT;
}

Graphics::~Graphics()
{
	ReleaseAll();
}

void Graphics::ReleaseAll()
{
	SAFE_RELEASE(device3d);
	SAFE_RELEASE(direct3d);
}

void Graphics::Initialize(HWND _hwnd, int _width, int _height, bool _isFullscreen)
{
	hWnd = _hwnd;
	width = _width;
	height = _height;
	isFullscreen = _isFullscreen;

	if (NULL == (direct3d = Direct3DCreate9(D3D_SDK_VERSION)))
		throw(GameError(FATAL_ERROR, "Fail in initializing Direct3D"));

	_InitD3Dpp();
	hResult = direct3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&device3d
	);

	if (FAILED(hResult))
		throw(GameError(FATAL_ERROR, "Fail in creating direct3d device"));

}

HRESULT Graphics::ShowBackbuffer()
{
	hResult = -1;
	device3d->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0, 255, 0),
		0.0f,
		0
	);
	hResult = device3d->Present(NULL, NULL, NULL, NULL);
	return hResult;
}

void Graphics::_InitD3Dpp()
{
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferCount = 1;

	if(isFullscreen)
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	else
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = NULL;
	d3dpp.Windowed = (!isFullscreen);
	d3dpp.EnableAutoDepthStencil = false;
	d3dpp.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
}