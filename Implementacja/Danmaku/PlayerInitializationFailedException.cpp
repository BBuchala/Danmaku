#include "PlayerInitializationFailedException.h"

/// <summary>
/// Zwr�cenie komunikatu.
/// </summary>
/// <returns></returns>
std::string PlayerInitializationFailedException::ToString() const
{
	return "Player initialization failed.";
};
