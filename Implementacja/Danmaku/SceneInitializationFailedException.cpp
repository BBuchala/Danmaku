#include "SceneInitializationFailedException.h"

// zwrócenie komunikatu
const char * SceneInitializationFailedException::ToString()
{
	return "Unable to initialize the scene. Gomen :(";
};


// pokazanie message boxa
void SceneInitializationFailedException::ToMessageBox()
{
	MessageBox(NULL, this->ToString(), "Error!", MB_OK | MB_ICONERROR);
};