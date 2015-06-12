#include "StageCreationFailed.h"

/// <summary>
/// Zwrócenie komunikatu.
/// </summary>
/// <returns></returns>
std::string StageCreationFailed::ToString() const
{
	return "XML file containing Stage is invalid.\nUnable to start a new game.";
};


/// <summary>
/// Pokazanie message boxa.
/// </summary>
/// <returns></returns>
void StageCreationFailed::ToMessageBox()
{
	MessageBox(NULL, this->ToString().c_str(), "Error!", MB_OK | MB_ICONERROR);
};
