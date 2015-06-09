#include "Input.h"

/* ---- Initialize Keyboard
   ------------------------------------------------------------------------------------------- */
LPDIRECTINPUTDEVICE8 Input::InitializeKeyboard(HWND han_Window)
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

	this->CreateDictionary();
 
	return p_dx_KeybDevice;
};

 /* ---- Read Keyboard
   ------------------------------------------------------------------------------------------- */
void Input::ReadKeyboard(LPDIRECTINPUTDEVICE8 p_Keyb)
{
	p_Keyb->GetDeviceState(sizeof(chr_KeybState),(LPVOID)&chr_KeybState);
};

 /* ---- Get Key Down
   ------------------------------------------------------------------------------------------- */
unsigned char Input::GetKeyDown()
{
	for (int i = 0; i < 256; ++i)
	{
		if (KeyDownOne(i))
		{
			return i;
		}
	}
	return 0;	// zero nie ma przydzielonego klawisza
};

 /* ---- Key Number
   ------------------------------------------------------------------------------------------- */
unsigned char Input::KeyNumber(std::string const & name)
{
	
	
	for(Dictionary::const_iterator it = dictionary.begin(); it != dictionary.end(); ++it)
	{
		if ((*it).second.compare(name) == 0)
		{
			return (*it).first;
		}

		
		
		
	}
	return 0;
};

 /* ---- Create Dictionary
   ------------------------------------------------------------------------------------------- */
void Input::CreateDictionary()
{
	this->dictionary[1]   = "ESC";
	this->dictionary[2]   = "1";
	this->dictionary[3]   = "2";
	this->dictionary[4]   = "3";
	this->dictionary[5]   = "4";
	this->dictionary[6]   = "5";
	this->dictionary[7]   = "6";
	this->dictionary[8]   = "7";
	this->dictionary[9]   = "8";
	this->dictionary[10]  = "9";
	this->dictionary[11]  = "0";
	this->dictionary[12]  = "-";
	this->dictionary[13]  = "=";
	this->dictionary[14]  = "BACKSPACE";
	this->dictionary[15]  = "TAB";
	this->dictionary[16]  = "Q";
	this->dictionary[17]  = "W";
	this->dictionary[18]  = "E";
	this->dictionary[19]  = "R";
	this->dictionary[20]  = "T";
	this->dictionary[21]  = "Y";
	this->dictionary[22]  = "U";
	this->dictionary[23]  = "I";
	this->dictionary[24]  = "O";
	this->dictionary[25]  = "P";
	this->dictionary[26]  = "[";
	this->dictionary[27]  = "]";
	this->dictionary[28]  = "ENTER";
	this->dictionary[29]  = "LCTRL";
	this->dictionary[30]  = "A";
	this->dictionary[31]  = "S";
	this->dictionary[32]  = "D";
	this->dictionary[33]  = "F";
	this->dictionary[34]  = "G";
	this->dictionary[35]  = "H";
	this->dictionary[36]  = "J";
	this->dictionary[37]  = "K";
	this->dictionary[38]  = "L";
	this->dictionary[39]  = ";";
	this->dictionary[40]  = "'";
	this->dictionary[41]  = "`";
	this->dictionary[42]  = "LSHIFT";
	this->dictionary[43]  = "\\";
	this->dictionary[44]  = "Z";
	this->dictionary[45]  = "X";
	this->dictionary[46]  = "C";
	this->dictionary[47]  = "V";
	this->dictionary[48]  = "B";
	this->dictionary[49]  = "N";
	this->dictionary[50]  = "M";
	this->dictionary[51]  = ",";
	this->dictionary[52]  = ".";
	this->dictionary[53]  = "/";
	this->dictionary[54]  = "RSHIFT";
	this->dictionary[55]  = "NUMEPAD*";
	this->dictionary[56]  = "LALT";
	this->dictionary[57]  = "SPACE";
	this->dictionary[58]  = "CAPSLOCK";
	this->dictionary[59]  = "F1";
	this->dictionary[60]  = "F2";
	this->dictionary[61]  = "F3";
	this->dictionary[62]  = "F4";
	this->dictionary[63]  = "F5";
	this->dictionary[64]  = "F6";
	this->dictionary[65]  = "F7";
	this->dictionary[66]  = "F8";
	this->dictionary[67]  = "F9";
	this->dictionary[68]  = "F10";
	this->dictionary[69]  = "NUMLOCK";
	this->dictionary[70]  = "SCROLLLOCK";
	this->dictionary[71]  = "NUMEPAD7";
	this->dictionary[72]  = "NUMEPAD8";
	this->dictionary[73]  = "NUMEPAD9";
	this->dictionary[74]  = "NUMEPAD-";
	this->dictionary[75]  = "NUMEPAD4";
	this->dictionary[76]  = "NUMEPAD5";
	this->dictionary[77]  = "NUMEPAD6";
	this->dictionary[78]  = "NUMEPAD+";
	this->dictionary[79]  = "NUMEPAD1";
	this->dictionary[80]  = "NUMEPAD2";
	this->dictionary[81]  = "NUMEPAD3";
	this->dictionary[82]  = "NUMEPAD0";
	this->dictionary[83]  = "NUMEPAD.";
	this->dictionary[87]  = "F11";
	this->dictionary[88]  = "F12";
	this->dictionary[100] = "F13";
	this->dictionary[101] = "F14";
	this->dictionary[102] = "F15";
	this->dictionary[112] = "KANA";
	this->dictionary[121] = "CONVERT";
	this->dictionary[123] = "NOCONVERT";
	this->dictionary[125] = "YEN";
	this->dictionary[141] = "=";
	this->dictionary[144] = "^";
	this->dictionary[145] = "@";
	this->dictionary[146] = ":";
	this->dictionary[147] = "_";
	this->dictionary[148] = "KANJI";
	this->dictionary[149] = "STOP";
	this->dictionary[150] = "JAPANAX";
	this->dictionary[151] = "J3100";
	this->dictionary[156] = "NUMEPADENTER";
	this->dictionary[157] = "RCTRL";
	this->dictionary[179] = "NUMEPAD,";
	this->dictionary[181] = "NUMEPAD/";
	this->dictionary[183] = "PRINTSCREEN";
	this->dictionary[184] = "RALT";
	this->dictionary[197] = "PAUSE";
	this->dictionary[199] = "HOME";
	this->dictionary[200] = "UPARROW";
	this->dictionary[201] = "PAGEUP";
	this->dictionary[203] = "LEFTARROW";
	this->dictionary[205] = "RIGHTARROW";
	this->dictionary[207] = "END";
	this->dictionary[208] = "DOWNARROW";
	this->dictionary[209] = "PAGEDOWN";
	this->dictionary[210] = "INSERT";
	this->dictionary[211] = "DELETE";
	this->dictionary[219] = "WINDOWS";
	this->dictionary[220] = "WINDOWS";
	this->dictionary[221] = "MENU";
	this->dictionary[222] = "POWER";
	this->dictionary[223] = "WINDOWS";
};

 /* ---- Set Game Controls
   ------------------------------------------------------------------------------------------- */
void Input::SetGameControls(GameInput gInput)
{
	this->gameInput = gInput;
};
