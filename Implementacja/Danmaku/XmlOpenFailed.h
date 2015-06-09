#pragma once
#include "FileException.h"

class XmlOpenFailed: public FileException
{
public:
	// Konstruktor
	XmlOpenFailed(std::string const & fileName);

	// zwrócenie komunikatu
	std::string ToString() const override;
};
