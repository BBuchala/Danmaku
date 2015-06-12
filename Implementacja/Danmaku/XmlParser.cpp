#include "XmlParser.h"


/// <summary>
/// Tworzy now¹ instacjê klasy <see cref="XmlParser"/>.
/// </summary>
/// <param name="file">The file.</param>
XmlParser::XmlParser(std::string const & file) : _filePath(file)
{
};


/// <summary>
/// Sprasowanie pliku.
/// </summary>
void XmlParser::Start()
{
	this->GetContents();
	this->ReadXMLFile();
	this->Create();
};


/// <summary>
/// Pobranie zawartoœci pliku i przypisanie jej do _contents.
/// </summary>
void XmlParser::GetContents()
{
	_contents = std::unique_ptr<char>(XML2Char(_filePath));
};


/// <summary>
/// Konwersja XML na char*.
/// </summary>
/// <param name="stageFile">Plik wejœciowy XML.</param>
/// <returns></returns>
char * XmlParser::XML2Char ( std::string const & stageFile )
{
	std::ifstream file( stageFile );
	if( file.fail() )
	{
		throw XmlOpenFailedException(stageFile);
	}
	std::filebuf * pbuf = file.rdbuf();
	long fileLength = static_cast<long>(pbuf->pubseekoff( 0, std::ios::end, std::ios::in ));
	file.seekg( 0 );
	char * out = new char[ fileLength + 1 ];
	file.read( out, fileLength );
	return out;
};


/// <summary>
/// Sprawdznie poprawnoœci pliku xml i przypisanie do zmiennej _doc.
/// </summary>
void XmlParser::ReadXMLFile()
{
	try
	{
		std::string what(_contents.get());
		_doc.parse<0>(_contents.get());
	}
	catch( rapidxml::parse_error e )
	{
		std::string str(e.what());
		if (!str.compare("expected <") == 0)
			throw XmlParseFailedException(_filePath);
	}
};

/// <summary>
/// Usuniêcie dokumentu z pamiêci.
/// </summary>
void XmlParser::ClearDocument()
{
	_doc.clear();
};
