#pragma once
#include "GameInitializationFailedException.h"

/// <summary>
/// Wyjątek związany z nieprawidłową inicjalizacją paska elementów
/// </summary>
class BarInitializationFailedException: public GameInitializationFailedException
{
public:
	// zwrócenie komunikatu
	std::string ToString() const override;
};
