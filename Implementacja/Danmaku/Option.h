#pragma once

/// <summary>
/// Mo¿liwe opcja konfiguracji.
/// </summary>
enum class OPTION {
	LIFE_NUMBER		= 0x00,
	BOMB_NUMBER		= 0x01,
	UP				= 0x02,
	DOWN			= 0x03,
	LEFT			= 0x04,
	RIGHT			= 0x05,
	SHOOT			= 0x06,
	BOMB			= 0x07,
	FOCUS			= 0x08,
	RESET			= 0x09,
	ER				= 0x10
};

/// <summary>
/// Zwiêksza opcjê odpoednio o 1, wg listy.
/// </summary>
/// <param name="option">Opcja.</param>
/// <returns></returns>
inline OPTION operator++(OPTION & option)
{
	switch(option)
    {
    case OPTION::LIFE_NUMBER:	return option = OPTION::BOMB_NUMBER;
    case OPTION::BOMB_NUMBER:	return option = OPTION::UP;
    case OPTION::UP:			return option = OPTION::DOWN;
    case OPTION::DOWN:			return option = OPTION::LEFT;
    case OPTION::LEFT:			return option = OPTION::RIGHT;
	case OPTION::RIGHT:			return option = OPTION::SHOOT;
	case OPTION::SHOOT:			return option = OPTION::BOMB;
	case OPTION::BOMB:			return option = OPTION::FOCUS;
	case OPTION::FOCUS:			return option = OPTION::RESET;
	case OPTION::RESET:			return option = OPTION::LIFE_NUMBER;
	default:
		return OPTION::ER;
    }
};
/// <summary>
/// Zmniejsza opcjê odpoednio o 1, wg listy.
/// </summary>
/// <param name="option">Opcja.</param>
/// <returns></returns>
inline OPTION operator--(OPTION & option)
{
	switch(option)
    {
    case OPTION::LIFE_NUMBER:	return option = OPTION::RESET;
    case OPTION::BOMB_NUMBER:	return option = OPTION::LIFE_NUMBER;
    case OPTION::UP:			return option = OPTION::BOMB_NUMBER;
    case OPTION::DOWN:			return option = OPTION::UP;
    case OPTION::LEFT:			return option = OPTION::DOWN;
	case OPTION::RIGHT:			return option = OPTION::LEFT;
	case OPTION::SHOOT:			return option = OPTION::RIGHT;
	case OPTION::BOMB:			return option = OPTION::SHOOT;
	case OPTION::FOCUS:			return option = OPTION::BOMB;
	case OPTION::RESET:			return option = OPTION::FOCUS;
	default:
		return OPTION::ER;
    }
};
/// <summary>
/// Konwersja rodzaju opcji na jej reprezentacjê w postaci stringu.
/// </summary>
/// <param name="option">Opcja.</param>
/// <returns>Napis, jeœli opcja nie istnieje, to komunikat o b³êdzie.</returns>
inline std::string Option2String(OPTION option)
{
	switch(option)
    {
    case OPTION::LIFE_NUMBER:	return "LIFE_NUMBER";
    case OPTION::BOMB_NUMBER:	return "BOMB_NUMBER";
    case OPTION::UP:			return "UP";
    case OPTION::DOWN:			return "DOWN";
    case OPTION::LEFT:			return "LEFT";
	case OPTION::RIGHT:			return "RIGHT";
	case OPTION::SHOOT:			return "SHOOT";
	case OPTION::BOMB:			return "BOMB";
	case OPTION::FOCUS:			return "FOCUS";
	case OPTION::RESET:			return "RESET";
	default:  return "ERROR";

    }
};
/// <summary>
/// Konwersja stringu na rodzaj opcji.
/// </summary>
/// <param name="option">Opcja.</param>
/// <returns>Odpowiedni enum, jeœli nie istnieje, to komunikat o b³êdzie.</returns>
inline OPTION String2Option(std::string const & str)
{
	if (str.compare("LIFE_NUMBER") == 0)
		return OPTION::LIFE_NUMBER;
	else if (str.compare("BOMB_NUMBER") == 0)
		return OPTION::BOMB_NUMBER;
	else if (str.compare("UP") == 0)
		return OPTION::UP;
	else if (str.compare("DOWN") == 0)
		return OPTION::DOWN;
	else if (str.compare("LEFT") == 0)
		return OPTION::LEFT;
	else if (str.compare("RIGHT") == 0)
		return OPTION::RIGHT;
	else if (str.compare("SHOOT") == 0)
		return OPTION::SHOOT;
	else if (str.compare("BOMB") == 0)
		return OPTION::BOMB;
	else if (str.compare("FOCUS") == 0)
		return OPTION::FOCUS;
	else if (str.compare("RESET") == 0)
		return OPTION::RESET;
	else
	{
		return OPTION::ER;
	}
};