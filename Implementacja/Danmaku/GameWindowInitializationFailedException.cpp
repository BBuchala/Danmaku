#include "GameWindowInitializationFailedException.h"

/// <summary>
/// Zwrócenie komunikatu.
/// </summary>
/// <returns></returns>
std::string GameWindowInitializationFailedException::ToString() const
{
	return "Unable to create new window. Gomen :(";
};

/// <summary>
/// Pokazanie message boxa.
/// </summary>
/// <returns></returns>
void GameWindowInitializationFailedException::ToMessageBox()
{
	MessageBox(NULL, this->ToString().c_str(), "Error!", MB_OK | MB_ICONERROR);
};