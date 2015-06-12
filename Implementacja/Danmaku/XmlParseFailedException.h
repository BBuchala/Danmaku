#pragma once
#include "FileException.h"

class XmlParseFailedException: public FileException
{
public:
	// Konstruktor
	XmlParseFailedException(std::string const & fileName);

	// zwr�cenie komunikatu
	std::string ToString() const override;
};
