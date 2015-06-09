#ifndef EX_GAMEWINDOW_INIT_FAILED_H
#define EX_GAMEWINDOW_INIT_FAILED_H

#include "IException.h"

class GameWindowInitializationFailedException: public IException
{
public:
	// zwr�cenie komunikatu
	std::string ToString() const override;

	// pokazanie message boxa
	void ToMessageBox() override;
};


#endif