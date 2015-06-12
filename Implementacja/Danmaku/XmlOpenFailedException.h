#pragma once
#include "FileException.h"

class XmlOpenFailedException: public FileException
{
public:
	// Konstruktor
	XmlOpenFailedException(std::string const & fileName);

	// zwr�cenie komunikatu
	std::string ToString() const override;
};
