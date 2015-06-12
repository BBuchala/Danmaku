#ifndef EX_GAMEWINDOW_INIT_FAILED_H
#define EX_GAMEWINDOW_INIT_FAILED_H

#include "IException.h"

/// <summary>
/// Wyj¹tek zwi¹zany z b³êdn¹ inicjalizacj¹ okna
/// </summary>
class GameWindowInitializationFailedException: public IException
{
public:
	// zwrócenie komunikatu
	std::string ToString() const override;

	// pokazanie message boxa
	void ToMessageBox() override;
};


#endif