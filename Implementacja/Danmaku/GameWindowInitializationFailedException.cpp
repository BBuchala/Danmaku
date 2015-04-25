#include "GameWindowInitializationFailedException.h"

// zwrócenie komunikatu
const std::string GameWindowInitializationFailedException::ToString() const
{
	return "Unable to create new window. Gomen :(";
};


// pokazanie message boxa
void GameWindowInitializationFailedException::ToMessageBox()
{
	MessageBox(NULL, this->ToString().c_str(), "Error!", MB_OK | MB_ICONERROR);
};