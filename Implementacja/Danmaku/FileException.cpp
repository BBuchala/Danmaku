#include "FileException.h"

/// <summary>
/// Tworzy now¹ instacjê klasy <see cref="FileException"/>.
/// </summary>
/// <param name="fileName">Nazwa pliku.</param>
FileException::FileException(std::string const & fileName) : _fileName(fileName)
{
};

/// <summary>
/// Zwrócenie komunikatu.
/// </summary>
/// <returns></returns>
std::string FileException::ToString() const
{
	return "Unable to open " + _fileName + " file";
};

/// <summary>
/// Pokazanie message boxa.
/// </summary>
/// <returns></returns>
void FileException::ToMessageBox()
{
	MessageBox(NULL, this->ToString().c_str(), "Error!", MB_OK | MB_ICONERROR);
};
