#include "BombInitializationFailedException.h"

/// <summary>
/// Zwrócenie komunikatu.
/// </summary>
/// <returns></returns>
std::string BombInitializationFailedException::ToString() const
{
	return "Bomb initialization failed.";
};
