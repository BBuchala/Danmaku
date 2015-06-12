#pragma once
#include "FileException.h"

/// <summary>
/// Wyj�tek zwi�zany z nieudanym otarciem pliku XML
/// </summary>
class XmlOpenFailedException: public FileException
{
public:
	// Konstruktor
	XmlOpenFailedException(std::string const & fileName);

	// zwr�cenie komunikatu
	std::string ToString() const override;
};
