#pragma once
#include "GameInitializationFailedException.h"

/// <summary>
/// Wyj�tek zwi�zany z nieprawid�owym utworzenie bonusu
/// </summary>
class BonusInitializationFailedException: public GameInitializationFailedException
{
public:
	// zwr�cenie komunikatu
	std::string ToString() const override;
};
