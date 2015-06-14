#pragma once
#include "IException.h"

/// <summary>
/// Wyj¹tek zwi¹zany z nieprawid³owym uruchomieniem gry
/// </summary>
class GameInitializationFailedException: public IException
{
public:
	// zwrócenie komunikatu
	virtual std::string ToString() const override;

	// pokazanie message boxa
	virtual void ToMessageBox() override;
};
