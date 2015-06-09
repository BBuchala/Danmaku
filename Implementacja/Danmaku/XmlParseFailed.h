#pragma once
#include "FileException.h"

class XmlParseFailed: public FileException
{
public:
	// Konstruktor
	XmlParseFailed(std::string const & fileName);

	// zwr�cenie komunikatu
	std::string ToString() const override;
};
