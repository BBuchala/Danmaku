#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class Input
{
	unsigned char chr_KeybState[256];
	unsigned char chr_KeybArray[256];

public:
	LPDIRECTINPUTDEVICE8 InitializeKeyboard(HWND han_Window)
	{
		for (int i = 0; i < 256; i++)
		{
			chr_KeybArray[i] = 0;
		}

		LPDIRECTINPUT8 p_dx_KeybObject;
		LPDIRECTINPUTDEVICE8 p_dx_KeybDevice;
 
		DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&p_dx_KeybObject, NULL);
		p_dx_KeybObject->CreateDevice(GUID_SysKeyboard, &p_dx_KeybDevice, NULL);
 
		p_dx_KeybDevice->SetDataFormat(&c_dfDIKeyboard);
		p_dx_KeybDevice->SetCooperativeLevel(han_Window, DISCL_FOREGROUND|DISCL_NONEXCLUSIVE);
		p_dx_KeybDevice->Acquire();
 
		return p_dx_KeybDevice;
	}
 
	void ReadKeyboard(LPDIRECTINPUTDEVICE8 p_Keyb)
	{
		p_Keyb->GetDeviceState(sizeof(chr_KeybState),(LPVOID)&chr_KeybState);
	}

	inline bool KeyDown(UCHAR key)
	{
		if (chr_KeybState[key] & 0x80) 
		{
			chr_KeybArray[key] = 1;
			return true;
		} 
		else
		{
			chr_KeybArray[key] = 0;
			return false;
		}
	}

	inline bool KeyUp(UCHAR key)
	{
		if (chr_KeybState[key] & 0x80) 
		{
			chr_KeybArray[key] = 0;
			return false;
		} 
		else
		{
			chr_KeybArray[key] = 1;
			return true;
		}
	}

	inline bool KeyDownOne(UCHAR key)
	{
		if (chr_KeybState[key] & 0x80)
		{
			if (chr_KeybArray[key] == 1)
			{
				return false;
			} 
			else
			{
				chr_KeybArray[key] = 1;
				return true;
			}
		} 
		else
		{
			chr_KeybArray[key] = 0;
		}
		return false;
	}

	inline bool KeyUpOne(UCHAR key)
	{
		if (!(chr_KeybState[key] & 0x80))
		{
			if (chr_KeybArray[key] == 0)
			{
				return false;
			} 
			else
			{
				chr_KeybArray[key] = 0;
				return true;
			}
		} 
		else
		{
			chr_KeybArray[key] = 1;
		}
		return false;
	}
};
