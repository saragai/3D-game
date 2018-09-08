/*
input.cpp

(c) 2018 Saragai Takanori
*/

#include "input.h"

Input::Input() 
{
	for (bool keyDown : m_KeysDownArray)
	{
		keyDown = false;
	}

	for (bool keyPressed : m_KeysPressedArray)
	{
		keyPressed = false;
	}

	m_TextInput = "";
	m_CharInput = 0;
	m_NewLine = true;

	m_MousePosition = new Vector2Int();
	m_MouseRawPosition = new Vector2Int();

	m_MouseLButton = false;
	m_MouseMButton = false;
	m_MouseRButton = false;
	m_MouseX1Button = false;
	m_MouseX2Button = false;

	for (ControllerState state : m_Controllers)
	{
		state.leftVibrationTime = 0;
		state.rightVibrationTime = 0;
	}
}

Input::~Input()
{
	if(m_MouseCaptured)
		ReleaseCapture(); // Release mouse from the game window
	SAFE_DELETE(m_MousePosition);
	SAFE_DELETE(m_MouseRawPosition);
}

void Input::Initialize(HWND hWnd, bool captured)
{
	try 
	{
		m_MouseCaptured = captured;
		m_RawInputDevice.usUsagePage = HID_USAGE_PAGE_GENERIC;
		m_RawInputDevice.usUsage = HID_USAGE_GENERIC_MOUSE;
		m_RawInputDevice.dwFlags = RIDEV_INPUTSINK;
		m_RawInputDevice.hwndTarget = hWnd;

		RegisterRawInputDevices(&m_RawInputDevice, 1, sizeof(m_RawInputDevice));

		if (m_MouseCaptured)
			SetCapture(hWnd); // Capture mouse in the game window

		ZeroMemory(m_Controllers, sizeof(ControllerState) * MAX_NUM_CONTROLLERS);
		CheckControllers();
	}
	catch (...)
	{
		throw(GameError(FATAL_ERROR, "Fain in initializing input"));
	}

}

void Input::Clear(int inputType)
{
	if (inputType & INPUT_TYPE::KEYS_DOWN)
		for (int i = 0; i < KEYS_ARRAY_LENGTH; i++)
			m_KeysDownArray[i] = false;

	if (inputType & INPUT_TYPE::KEYS_PRESSED)
		for (int i = 0; i < KEYS_ARRAY_LENGTH; i++)
			m_KeysPressedArray[i] = false;

	if (inputType & INPUT_TYPE::MOUSE)
	{
		m_MousePosition->Clear();
		m_MouseRawPosition->Clear();
	}
	
	if (inputType & INPUT_TYPE::TEXT_IN)
		ClearTextInput();
}

void Input::KeyDown(WPARAM wParam)
{
	if (wParam < KEYS_ARRAY_LENGTH)
	{
		m_KeysDownArray[wParam] = true;
		m_KeysPressedArray[wParam] = true;
	}
}
void Input::KeyUp(WPARAM wParam)
{
	if (wParam < KEYS_ARRAY_LENGTH)
	{
		m_KeysDownArray[wParam] = false;
	}
}
void Input::KeyInput(WPARAM wParam)
{
	if (m_NewLine)
	{
		m_TextInput.clear();
		m_NewLine = false;
	}
	if (wParam == '\b')
	{
		if (m_TextInput.length() > 0)
			m_TextInput.erase(m_TextInput.size() - 1);
	}
	else
	{
		m_TextInput += wParam;
		m_CharInput = wParam;
	}
	if ((char)wParam == '\r')
		m_NewLine = true;
}

void Input::MouseInput(LPARAM lParam)
{
	m_MousePosition->x = lParam & 0xffff;
	m_MousePosition->y = (lParam >> 16) & 0xffff;
}

void Input::MouseRawInput(LPARAM lParam)
{
	UINT dwSize = 40;
	static BYTE lpByte[40];
	GetRawInputData(
		(HRAWINPUT)lParam,
		RID_INPUT,
		lpByte,
		&dwSize,
		sizeof(RAWINPUTHEADER));

	RAWINPUT* raw = (RAWINPUT*)lpByte;
	if (raw->header.dwType == RIM_TYPEMOUSE)
	{
		m_MouseRawPosition->x = raw->data.mouse.lLastX;
		m_MouseRawPosition->y = raw->data.mouse.lLastY;
	}
}

void Input::CheckControllers()
{
	for (int i=0; i < MAX_NUM_CONTROLLERS; i++)
	{
		bool connected = (XInputGetState(i, &m_Controllers[i].state) == ERROR_SUCCESS);
		m_Controllers[i].connected = connected;
	}
}

void Input::ReadControllers()
{
	for (int i = 0; i < MAX_NUM_CONTROLLERS; i++)
	{
		if (m_Controllers[i].connected)
		{
			if (XInputGetState(i, &m_Controllers[i].state) == ERROR_DEVICE_NOT_CONNECTED)
				m_Controllers[i].connected = false;
		}
	}
}

void Input::VibrateControllers(float frameTime)
{
	int id = 0;
	for (int ci = 0; ci < MAX_NUM_CONTROLLERS; ci ++) 
	{
		ControllerState controller = m_Controllers[ci];

		if (controller.connected == false)
			continue;

		controller.leftVibrationTime -= frameTime;
		controller.rightVibrationTime -= frameTime;

		if (controller.leftVibrationTime < 0)
		{
			controller.leftVibrationTime = 0;
			controller.vibration.wLeftMotorSpeed= 0;
		}

		if (controller.rightVibrationTime < 0)
		{
			controller.rightVibrationTime = 0;
			controller.vibration.wRightMotorSpeed = 0;
		}
		XInputSetState(ci, &controller.vibration);
	}
}