#include "XmlParseFailed.h"

// Konstruktor
XmlParseFailed::XmlParseFailed(std::string const & fileName) : FileException(fileName)
{
};

// zwrócenie komunikatu
std::string XmlParseFailed::ToString() const
{
	return "Parsing XML file " + _fileName + " was unsuccessful.";
};
