#include "GameInitializationFailedException.h"

/// <summary>
/// Zwrócenie komunikatu.
/// </summary>
/// <returns></returns>
std::string GameInitializationFailedException::ToString() const
{
	return "Game initialization failed.";
};


/// <summary>
/// Pokazanie message boxa.
/// </summary>
/// <returns></returns>
void GameInitializationFailedException::ToMessageBox()
{
	MessageBox(NULL, this->ToString().c_str(), "Error!", MB_OK | MB_ICONERROR);
};
