#ifndef EX_GAMEWINDOW_INIT_FAILED_H
#define EX_GAMEWINDOW_INIT_FAILED_H

#include <Windows.h>
#include "IException.h"

class GameWindowInitializationFailedException : IException
{
public:
	// zwrócenie komunikatu
	const std::string ToString() const override;

	// pokazanie message boxa
	void ToMessageBox() override;
};


#endif