#include "BossDataInitializationFailedException.h"

/// <summary>
/// Zwrócenie komunikatu.
/// </summary>
/// <returns></returns>
std::string BossDataInitializationFailedException::ToString() const
{
	return "Boss initialization failed.";
};
