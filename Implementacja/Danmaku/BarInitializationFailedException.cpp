#include "BarInitializationFailedException.h"

/// <summary>
/// Zwrócenie komunikatu.
/// </summary>
/// <returns></returns>
std::string BarInitializationFailedException::ToString() const
{
	return "Bar initialization failed.";
};
