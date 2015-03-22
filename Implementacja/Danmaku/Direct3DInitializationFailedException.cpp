#include "Direct3DInitializationFailedException.h"

// zwr�cenie komunikatu
const char * Direct3DInitializationFailedException::ToString()
{
	return "Direct3D initialization failed.";
};


// pokazanie message boxa
void Direct3DInitializationFailedException::ToMessageBox()
{
	MessageBox(NULL, this->ToString(), "Error!", MB_OK | MB_ICONERROR);
};