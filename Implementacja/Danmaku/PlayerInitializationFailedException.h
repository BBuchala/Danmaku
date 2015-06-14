#pragma once
#include "GameInitializationFailedException.h"

/// <summary>
/// Wyj¹tek zwi¹zany z nieprawid³owym utworzeniem gracza
/// </summary>
class PlayerInitializationFailedException: public GameInitializationFailedException
{
public:
	// zwrócenie komunikatu
	std::string ToString() const override;
};
