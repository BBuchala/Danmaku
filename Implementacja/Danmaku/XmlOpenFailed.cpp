#include "XmlOpenFailed.h"

// Konstruktor
XmlOpenFailed::XmlOpenFailed(std::string const & fileName) : FileException(fileName)
{
};

// zwrócenie komunikatu
std::string XmlOpenFailed::ToString() const
{
	return "Opening XML file " + _fileName + " was unsuccessful.\nIt probably doesn't exist.";
};
