#ifndef EX_DIRECT3D_INIT_FAILED_H
#define EX_DIRECT3D_INIT_FAILED_H

#include <Windows.h>
#include "IException.h"

class Direct3DInitializationFailedException : IException
{
public:
	// zwrócenie komunikatu
	std::string ToString() const override;

	// pokazanie message boxa
	void ToMessageBox() override;
};


#endif