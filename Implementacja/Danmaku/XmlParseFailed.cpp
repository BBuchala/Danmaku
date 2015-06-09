#include "XmlParseFailed.h"

// Konstruktor
XmlParseFailed::XmlParseFailed(std::string const & fileName) : FileException(fileName)
{
};

// zwr�cenie komunikatu
std::string XmlParseFailed::ToString() const
{
	return "Parsing XML file " + _fileName + " was unsuccessful.";
};
