#include "FontInitializationFailedException.h"

/// <summary>
/// Zwrócenie komunikatu.
/// </summary>
/// <returns></returns>
std::string FontInitializationFailedException::ToString() const
{
	return "Font initialization failed.";
};
