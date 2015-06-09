#include "XmlOpenFailed.h"

// Konstruktor
XmlOpenFailed::XmlOpenFailed(std::string const & fileName) : FileException(fileName)
{
};

// zwr�cenie komunikatu
std::string XmlOpenFailed::ToString() const
{
	return "Opening XML file " + _fileName + " was unsuccessful.\nIt probably doesn't exist.";
};
