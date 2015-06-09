#pragma once
#include "IException.h"

class FileException: public IException
{
protected:
	std::string _fileName;

public:
	// Konstruktor
	FileException(std::string const & fileName);

	// zwr�cenie komunikatu
	virtual std::string ToString() const override;

	// pokazanie message boxa
	void ToMessageBox() override;
};
