#include "StageCreationFailed.h"

// zwrócenie komunikatu
std::string StageCreationFailed::ToString() const
{
	return "XML file containing Stage is invalid.\nUnable to start a new game.";
};


// pokazanie message boxa
void StageCreationFailed::ToMessageBox()
{
	MessageBox(NULL, this->ToString().c_str(), "Error!", MB_OK | MB_ICONERROR);
};
