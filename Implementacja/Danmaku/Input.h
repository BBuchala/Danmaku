#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <map>
#include "GameControls.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class Input
{
	// stan klawiszy oraz info, czy by�y ju� wci�ni�te
	unsigned char chr_KeybState[256];
	unsigned char chr_KeybArray[256];
	// s�ownik numer klawisza - jego nazwa
	typedef std::map<unsigned char, std::string> Dictionary;
	Dictionary dictionary;
	// input dla klawiszy obs�uguj�cych gr�
	typedef std::map<GameControl, unsigned char>	GameInput;
	GameInput gameInput;

public:
	// inicjalizacja obs�ugi klawiszy
	LPDIRECTINPUTDEVICE8 InitializeKeyboard(HWND han_Window);
	// odczytanie stanu klawiatury
	void ReadKeyboard(LPDIRECTINPUTDEVICE8 p_Keyb);

	// zapisanie kontrolek gry
	void SetGameControls(GameInput gInput);

	/* ==== Zwr�cenie informacji o stanie klawiatury ================================= */
	// zwraca nazw� klawisza o podanym ID
	inline std::string KeyName(UCHAR key)
	{
		return this->dictionary[key];
	}
	// zwraca ID klawisza o podanej nazwie
	unsigned char KeyNumber(std::string const & name);
	// ze wszystkich wci�ni�tych klawiszy zwraca pierwszy z nich
	unsigned char GetKeyDown();

	// czy klawisz jest wci�ni�ty
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
	};
	// czy klawisz nie jest wci�ni�ty
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
	};
	// czy klawisz zosta� wci�ni�ty RAZ
	// je�li tak, to w czasie jednego updatu zwraca raz true, a nast�pnie je blokuje
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
	};

	// czy klawisz gry o podanym ID zosta� wci�ni�ty
	inline bool GameKey(GameControl const gKey)
	{
		return KeyDown(this->gameInput[gKey]);
	};
	// czy klawisz gry o podanym ID zosta� wci�ni�ty RAZ
	inline bool GameKeyOne(GameControl const gKey)
	{
		return KeyDownOne(this->gameInput[gKey]);
	};

private:
	// utworzenie s�ownika
	void CreateDictionary();

};
