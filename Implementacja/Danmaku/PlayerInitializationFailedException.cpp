#include "PlayerInitializationFailedException.h"

/// <summary>
/// Zwrócenie komunikatu.
/// </summary>
/// <returns></returns>
std::string PlayerInitializationFailedException::ToString() const
{
	return "Player initialization failed.";
};
