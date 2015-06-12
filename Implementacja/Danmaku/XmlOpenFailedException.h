#pragma once
#include "FileException.h"

/// <summary>
/// Wyj¹tek zwi¹zany z nieudanym otarciem pliku XML
/// </summary>
class XmlOpenFailedException: public FileException
{
public:
	// Konstruktor
	XmlOpenFailedException(std::string const & fileName);

	// zwrócenie komunikatu
	std::string ToString() const override;
};
