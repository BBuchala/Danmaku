#pragma once
#include "GameInitializationFailedException.h"

/// <summary>
/// Wyj�tek zwi�zany z nieprawid�owym uruchomieniem gry
/// </summary>
class PlayerBulletInitializationFailedException: public GameInitializationFailedException
{
public:
	// zwr�cenie komunikatu
	std::string ToString() const override;
};
