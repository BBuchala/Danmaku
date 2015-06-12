#pragma once
#include "IException.h"

/// <summary>
/// Wyj¹tek wyrzucany, gdy njie uda³o siê utworzyæ elementów planszy
/// </summary>
class StageCreationFailedException: public IException
{
public:
	// zwrócenie komunikatu
	std::string ToString() const override;

	// pokazanie message boxa
	void ToMessageBox() override;
};
