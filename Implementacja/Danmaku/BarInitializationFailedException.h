#pragma once
#include "GameInitializationFailedException.h"

/// <summary>
/// Wyj�tek zwi�zany z nieprawid�ow� inicjalizacj� paska element�w
/// </summary>
class BarInitializationFailedException: public GameInitializationFailedException
{
public:
	// zwr�cenie komunikatu
	std::string ToString() const override;
};
