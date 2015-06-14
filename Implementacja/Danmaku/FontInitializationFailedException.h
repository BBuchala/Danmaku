#pragma once
#include "GameInitializationFailedException.h"

/// <summary>
/// Wyj¹tek zwi¹zany z nieprawid³owym utworzenie pola z czcionk¹
/// </summary>
class FontInitializationFailedException: public GameInitializationFailedException
{
public:
	// zwrócenie komunikatu
	std::string ToString() const override;
};
