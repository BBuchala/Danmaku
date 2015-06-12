#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <map>
#include "GameControls.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

/// <summary>
/// Klasa odpowiadaj¹ca za komunikacjê z klawiatur¹
/// </summary>
class Input
{
	// stan klawiszy oraz info, czy by³y ju¿ wciœniête
	unsigned char chr_KeybState[256];
	unsigned char chr_KeybArray[256];
	// s³ownik numer klawisza - jego nazwa
	typedef std::map<unsigned char, std::string> Dictionary;
	Dictionary dictionary;
	// input dla klawiszy obs³uguj¹cych grê
	typedef std::map<GameControl, unsigned char>	GameInput;
	GameInput gameInput;

public:
	// inicjalizacja obs³ugi klawiszy
	LPDIRECTINPUTDEVICE8 InitializeKeyboard(HWND hwnd);
	// odczytanie stanu klawiatury
	void ReadKeyboard(LPDIRECTINPUTDEVICE8 p_Keyb);

	// wyzerowanie stanu inputu
	void Erase();

	// zapisanie kontrolek gry
	void SetGameControls(GameInput gInput);

	/* ==== Zwrócenie informacji o stanie klawiatury ================================= */
	/// <summary>
	/// Zwraca nazwê klawisza o podanym ID.
	/// </summary>
	/// <param name="key">Klucz.</param>
	/// <returns></returns>
	inline std::string KeyName(UCHAR key)
	{
		return this->dictionary[key];
	}
	// zwraca ID klawisza o podanej nazwie
	unsigned char KeyNumber(std::string const & name);
	// ze wszystkich wciœniêtych klawiszy zwraca pierwszy z nich
	unsigned char GetKeyDown();

	/// <summary>
	/// Czy klawisz jest wciœniêty.
	/// </summary>
	/// <param name="key">Klucz.</param>
	/// <returns></returns>
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
	/// <summary>
	/// Czy klawisz nie jest wciœniêty.
	/// </summary>
	/// <param name="key">Klucz.</param>
	/// <returns></returns>
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
	
	/// <summary>
	/// czy klawisz zosta³ wciœniêty RAZ
	/// jeœli tak, to w czasie jednego updatu zwraca raz true, a nastêpnie je blokuje
	/// </summary>
	/// <param name="key">Klucz.</param>
	/// <returns></returns>
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

	/// <summary>
	/// Czy klawisz gry o podanym ID zosta³ wciœniêty
	/// </summary>
	/// <param name="gKey">Klucz.</param>
	/// <returns></returns>
	inline bool GameKey(GameControl const gKey)
	{
		return KeyDown(this->gameInput[gKey]);
	};
	/// <summary>
	/// Czy klawisz gry o podanym ID zosta³ wciœniêty RAZ.
	/// </summary>
	/// <param name="gKey">Kontrolka dla klucza.</param>
	/// <returns></returns>
	inline bool GameKeyOne(GameControl const gKey)
	{
		return KeyDownOne(this->gameInput[gKey]);
	};

private:
	// utworzenie s³ownika
	void CreateDictionary();

};
