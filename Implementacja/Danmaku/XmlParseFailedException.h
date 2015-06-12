#pragma once
#include "FileException.h"

/// <summary>
/// Wyj¹tek zwi¹zany z niepowodzeniem parsowania pliku XML
/// </summary>
class XmlParseFailedException: public FileException
{
public:
	// Konstruktor
	XmlParseFailedException(std::string const & fileName);

	// zwrócenie komunikatu
	std::string ToString() const override;
};
