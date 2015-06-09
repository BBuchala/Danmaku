#include "FileException.h"

FileException::FileException(std::string const & fileName) : _fileName(fileName)
{
};

std::string FileException::ToString() const
{
	return "Unable to open " + _fileName + " file";
};

void FileException::ToMessageBox()
{
	MessageBox(NULL, this->ToString().c_str(), "Error!", MB_OK | MB_ICONERROR);
};
