#pragma once
#include "IException.h"

/// <summary>
/// Wyj�tek zwi�zany z obs�ug� plik�w wej�ciowych
/// </summary>
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
