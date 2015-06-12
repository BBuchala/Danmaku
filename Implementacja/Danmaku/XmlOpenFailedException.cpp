#include "XmlOpenFailedException.h"

// Konstruktor
/// <summary>
/// Tworzy now¹ instacjê klasy <see cref="XmlOpenFailedException"/>.
/// </summary>
/// <param name="fileName">Nazwa pliku.</param>
XmlOpenFailedException::XmlOpenFailedException(std::string const & fileName) : FileException(fileName)
{
};

/// <summary>
/// Zwrócenie komunikatu.
/// </summary>
/// <returns></returns>
std::string XmlOpenFailedException::ToString() const
{
	return "Opening XML file " + _fileName + " was unsuccessful.\nIt probably doesn't exist.";
};
