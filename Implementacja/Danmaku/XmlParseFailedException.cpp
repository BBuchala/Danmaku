#include "XmlParseFailedException.h"

/// <summary>
/// Tworzy now� instacj� klasy <see cref="XmlParseFailedException"/>.
/// </summary>
/// <param name="fileName">Nazwa pliku.</param>
XmlParseFailedException::XmlParseFailedException(std::string const & fileName) : FileException(fileName)
{
};

/// <summary>
/// Zwr�cenie komunikatu.
/// </summary>
/// <returns></returns>
std::string XmlParseFailedException::ToString() const
{
	return "Parsing XML file " + _fileName + " was unsuccessful.";
};
