#pragma once
#include "GameInitializationFailedException.h"

/// <summary>
/// Wyjątek związany z nieprawidłowym utworzeniem gracza
/// </summary>
class PlayerInitializationFailedException: public GameInitializationFailedException
{
public:
	// zwrócenie komunikatu
	std::string ToString() const override;
};
