#include "Direct3DInitializationFailedException.h"

// zwrócenie komunikatu
const std::string Direct3DInitializationFailedException::ToString() const
{
	return "Direct3D initialization failed.";
};


// pokazanie message boxa
void Direct3DInitializationFailedException::ToMessageBox()
{
	MessageBox(NULL, this->ToString().c_str(), "Error!", MB_OK | MB_ICONERROR);
};