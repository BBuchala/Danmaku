#ifndef EX_GAMEWINDOW_INIT_FAILED_H
#define EX_GAMEWINDOW_INIT_FAILED_H

#include <Windows.h>
#include "IException.h"

class GameWindowInitializationFailedException : IException
{
public:
	// zwr�cenie komunikatu
	const char * ToString() override;

	// pokazanie message boxa
	void ToMessageBox() override;
};


#endif