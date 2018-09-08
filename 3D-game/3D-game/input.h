/*
input.h

(c) 2018 Saragai Takanori
*/
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <windowsx.h>
#include <string>
#include <XInput.h>
#include "vector2int.h"

#include "constant.h"
#include "game_error.h"
#include "safe.h"

#define KEYS_ARRAY_LENGTH 256

#define MAX_NUM_CONTROLLERS 4

// for high-def mouse
#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC ((USHORT) 0x01)
#endif // !HID_USAGE_PAGE_GENERIC

#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE ((USHORT) 0x02)
#endif // !HID_USAGE_GENERIC_MOUSE


struct ControllerState
{
	XINPUT_STATE state;
	XINPUT_VIBRATION vibration;
	float leftVibrationTime;
	float rightVibrationTime;
	bool connected;
};

namespace INPUT_TYPE
{
	const UCHAR KEYS_DOWN = 1 << 0;
	const UCHAR KEYS_PRESSED = 1 << 1;
	const UCHAR MOUSE = 1 << 2;
	const UCHAR TEXT_IN = 1 << 3;
	const UCHAR ALL = KEYS_DOWN + KEYS_PRESSED + MOUSE + TEXT_IN;
}
class Input
{
private:
	bool m_KeysDownArray[KEYS_ARRAY_LENGTH];
	bool m_KeysPressedArray[KEYS_ARRAY_LENGTH];

	std::string m_TextInput;
	char m_CharInput;
	bool m_NewLine;
	Vector2Int *m_MousePosition;
	Vector2Int *m_MouseRawPosition;
	RAWINPUTDEVICE m_RawInputDevice;

	bool m_MouseCaptured;

	bool m_MouseLButton;
	bool m_MouseMButton;
	bool m_MouseRButton;
	bool m_MouseX1Button;
	bool m_MouseX2Button;

	ControllerState m_Controllers[MAX_NUM_CONTROLLERS]; 

public:


	Input();
	virtual ~Input();

	void Initialize(HWND hWnd, bool captured);

	void Clear(int inputType);
	void ClearAll() { Clear(INPUT_TYPE::ALL); }
	void ClearTextInput() { m_TextInput.clear(); }

	void KeyDown(WPARAM wParam);
	void KeyUp(WPARAM wParam);
	void KeyInput(WPARAM wParam);
	void MouseInput(LPARAM lParam);
	void MouseRawInput(LPARAM lParam);

	//Accessor
	Vector2Int GetMousePosition() const { return m_MousePosition; }
	Vector2Int GetMouseRawPosition() const { return m_MouseRawPosition; }

	void SetMouseLButton(const bool down) { m_MouseLButton = down; }
	void SetMouseMButton(const bool down) { m_MouseMButton = down; }
	void SetMouseRButton(const bool down) { m_MouseMButton = down; }
	void SetMouseXButton(const WPARAM wParam)
	{
		m_MouseX1Button = (wParam & MK_XBUTTON1) ? true : false;
		m_MouseX2Button = (wParam & MK_XBUTTON2) ? true : false;
	}
	bool GetMouseLButton() const { return m_MouseLButton; }
	bool GetMouseMButton() const { return m_MouseMButton; }
	bool GetMouseRButton() const { return m_MouseRButton; }
	bool GetMouseX1Button() const { return m_MouseX1Button; }
	bool GetMouseX2Button() const { return m_MouseX2Button; }

	void CheckControllers();
	void ReadControllers();
	void VibrateControllers(float frameTime);
};
