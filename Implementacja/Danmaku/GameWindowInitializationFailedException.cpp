#include "GameWindowInitializationFailedException.h"

// zwrócenie komunikatu
const char * GameWindowInitializationFailedException::ToString()
{
	return "Unable to create new window. Gomen :(";
};


// pokazanie message boxa
void GameWindowInitializationFailedException::ToMessageBox()
{
	MessageBox(NULL, this->ToString(), "Error!", MB_OK | MB_ICONERROR);
};