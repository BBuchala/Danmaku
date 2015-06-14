#pragma once
#include "GameInitializationFailedException.h"

/// <summary>
/// Wyj�tek zwi�zany z nieprawid�owym utworzeniem gracza
/// </summary>
class PlayerInitializationFailedException: public GameInitializationFailedException
{
public:
	// zwr�cenie komunikatu
	std::string ToString() const override;
};
