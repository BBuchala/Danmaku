#pragma once
#include "IException.h"

/// <summary>
/// Wyj�tek zwi�zany z nieprawid�owym uruchomieniem gry
/// </summary>
class GameInitializationFailedException: public IException
{
public:
	// zwr�cenie komunikatu
	virtual std::string ToString() const override;

	// pokazanie message boxa
	virtual void ToMessageBox() override;
};
