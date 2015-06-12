#pragma once
#include "IException.h"

/// <summary>
/// Wyj�tek wyrzucany, gdy njie uda�o si� utworzy� element�w planszy
/// </summary>
class StageCreationFailedException: public IException
{
public:
	// zwr�cenie komunikatu
	std::string ToString() const override;

	// pokazanie message boxa
	void ToMessageBox() override;
};
