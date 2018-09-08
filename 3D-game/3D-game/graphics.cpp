/*
graphics.cpp

(c) 2018 Saragai Takanori
*/

#include "graphics.h"

Graphics::Graphics()
{
	m_Direct3d = NULL;
	m_D3DDevice = NULL;
	m_IsFullscreen = false;
	m_Width = constant::WIDTH;
	m_Height = constant::HEIGHT;
}

Graphics::~Graphics()
{
	ReleaseAll();
}

void Graphics::ReleaseAll()
{
	SAFE_RELEASE(m_D3DDevice);
	SAFE_RELEASE(m_Direct3d);
}

void Graphics::Initialize(HWND hwnd, int width, int height, bool isFullscreen)
{
	m_HWnd = hwnd;
	m_Width = width;
	m_Height = height;
	m_IsFullscreen = isFullscreen;

	m_Direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_Direct3d == NULL)
		throw(GameError(FATAL_ERROR, "Fail in initializing Direct3D"));

	_InitD3Dpp();

	if (m_IsFullscreen)
	{
		if (IsAdapterCompatible())
			m_D3DPresentParameters.FullScreen_RefreshRateInHz = m_D3DDisPlayMode.RefreshRate;
		else
			throw(GameError(FATAL_ERROR,
				"This Graphic Device does not support the specified resolution and/or format."));
	}

	D3DCAPS9 caps;
	DWORD VertexBehavior;
	m_Direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	if ((caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0
		or caps.VertexShaderVersion < D3DVS_VERSION(1, 1))
		VertexBehavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	else
		VertexBehavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;


	HRESULT hResult = m_Direct3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_HWnd,
		VertexBehavior,
		&m_D3DPresentParameters,
		&m_D3DDevice
	);

	if (FAILED(hResult))
		throw(GameError(FATAL_ERROR, "Fail in creating direct3d device"));

}

HRESULT Graphics::ShowBackbuffer()
{
	m_D3DDevice->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0, 255, 0),
		0.0f,
		0
	);
	HRESULT hResult = m_D3DDevice->Present(NULL, NULL, NULL, NULL);
	return hResult;
}

void Graphics::_InitD3Dpp()
{
	ZeroMemory(&m_D3DPresentParameters, sizeof(m_D3DPresentParameters));

	m_D3DPresentParameters.BackBufferWidth = m_Width;
	m_D3DPresentParameters.BackBufferHeight = m_Height;
	m_D3DPresentParameters.BackBufferCount = 1;

	if(m_IsFullscreen)
		m_D3DPresentParameters.BackBufferFormat = D3DFMT_X8R8G8B8;
	else
		m_D3DPresentParameters.BackBufferFormat = D3DFMT_UNKNOWN;

	m_D3DPresentParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_D3DPresentParameters.MultiSampleQuality = 0;

	m_D3DPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3DPresentParameters.hDeviceWindow = NULL;
	m_D3DPresentParameters.Windowed = (!m_IsFullscreen);
	m_D3DPresentParameters.EnableAutoDepthStencil = false;
	m_D3DPresentParameters.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
	m_D3DPresentParameters.Flags = 0;
	m_D3DPresentParameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_D3DPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
}

HRESULT Graphics::GetDeviceState()
{
	if (m_D3DDevice == NULL)
		return E_FAIL;

	return m_D3DDevice->TestCooperativeLevel();
}

bool Graphics::IsAdapterCompatible()
{
	UINT modes = m_Direct3d->GetAdapterModeCount(
		D3DADAPTER_DEFAULT,
		m_D3DPresentParameters.BackBufferFormat);

	for (UINT i = 0; i < modes; i++)
	{
		D3DDISPLAYMODE pMode;
		m_Direct3d->EnumAdapterModes(
			D3DADAPTER_DEFAULT,
			m_D3DPresentParameters.BackBufferFormat,
			i,
			&pMode);

		if (pMode.Height == m_D3DPresentParameters.BackBufferHeight
			and pMode.Width == m_D3DPresentParameters.BackBufferWidth
			and pMode.RefreshRate >= m_D3DPresentParameters.FullScreen_RefreshRateInHz)
		{
			m_D3DDisPlayMode = pMode;
			return true;
		}
	}
	return false;
}

HRESULT Graphics::ResetGraphicDevice()
{
	_InitD3Dpp();
	return m_D3DDevice->Reset(&m_D3DPresentParameters);
}

