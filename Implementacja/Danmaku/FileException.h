#pragma once
#include "IException.h"

class FileException: public IException
{
protected:
	std::string _fileName;

public:
	// Konstruktor
	FileException(std::string const & fileName);

	// zwrócenie komunikatu
	virtual std::string ToString() const override;

	// pokazanie message boxa
	void ToMessageBox() override;
};
