#include "Direct3DInitializationFailedException.h"

/// <summary>
/// Zwrócenie komunikatu.
/// </summary>
/// <returns></returns>
std::string Direct3DInitializationFailedException::ToString() const
{
	return "Direct3D initialization failed.";
};


/// <summary>
/// Pokazanie message boxa.
/// </summary>
/// <returns></returns>
void Direct3DInitializationFailedException::ToMessageBox()
{
	MessageBox(NULL, this->ToString().c_str(), "Error!", MB_OK | MB_ICONERROR);
};