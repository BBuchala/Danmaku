#include "BonusInitializationFailedException.h"

/// <summary>
/// Zwrócenie komunikatu.
/// </summary>
/// <returns></returns>
std::string BonusInitializationFailedException::ToString() const
{
	return "Bar initialization failed.";
};
