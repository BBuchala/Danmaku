#include "FontInitializationFailedException.h"

/// <summary>
/// Zwr�cenie komunikatu.
/// </summary>
/// <returns></returns>
std::string FontInitializationFailedException::ToString() const
{
	return "Font initialization failed.";
};
