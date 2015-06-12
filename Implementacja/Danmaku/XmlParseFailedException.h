#pragma once
#include "FileException.h"

class XmlParseFailedException: public FileException
{
public:
	// Konstruktor
	XmlParseFailedException(std::string const & fileName);

	// zwrócenie komunikatu
	std::string ToString() const override;
};
