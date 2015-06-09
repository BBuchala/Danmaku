#pragma once
#include "IException.h"

class StageCreationFailed: public IException
{
public:
	// zwrócenie komunikatu
	std::string ToString() const override;

	// pokazanie message boxa
	void ToMessageBox() override;
};
