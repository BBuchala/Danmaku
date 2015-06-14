#pragma once
#include "GameInitializationFailedException.h"

/// <summary>
/// Wyj¹tek zwi¹zany z nieprawid³ow¹ inicjalizacj¹ paska elementów
/// </summary>
class BossDataInitializationFailedException: public GameInitializationFailedException
{
public:
	// zwrócenie komunikatu
	std::string ToString() const override;
};
