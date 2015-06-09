#pragma once
#include "FileException.h"

class XmlOpenFailed: public FileException
{
public:
	// Konstruktor
	XmlOpenFailed(std::string const & fileName);

	// zwr�cenie komunikatu
	std::string ToString() const override;
};
