#pragma once
#include "GameInitializationFailedException.h"

/// <summary>
/// Wyj¹tek zwi¹zany z nieprawid³owym utworzenie bonusu
/// </summary>
class BonusInitializationFailedException: public GameInitializationFailedException
{
public:
	// zwrócenie komunikatu
	std::string ToString() const override;
};
