#pragma once
#include "FileException.h"

/// <summary>
/// Wyj�tek zwi�zany z niepowodzeniem parsowania pliku XML
/// </summary>
class XmlParseFailedException: public FileException
{
public:
	// Konstruktor
	XmlParseFailedException(std::string const & fileName);

	// zwr�cenie komunikatu
	std::string ToString() const override;
};
