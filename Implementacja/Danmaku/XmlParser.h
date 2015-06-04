#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>

using namespace rapidxml;

class XmlParser
{
protected:
	std::string _filePath;
	rapidxml::xml_document <> _doc;		// plik z danymi
	std::unique_ptr<char> _contents;	// zawartoœæ pliku XML

public:
	XmlParser(std::string const & file)
	{
		_filePath = file;
	}

	void Start()
	{
		this->ConvertXMLFile();
		this->ReadXMLFile();
		this->Create();
	}

	void ConvertXMLFile()
	{
		_contents = std::unique_ptr<char>(XML2Char(_filePath));
	}

	char * XML2Char ( std::string const & stageFile )
	{
		std::ifstream file( stageFile );
		if( file.bad() )
		{
			exit( - 1 );
		}
		std::filebuf * pbuf = file.rdbuf();
		long fileLength = static_cast<long>(pbuf->pubseekoff( 0, std::ios::end, std::ios::in ));
		file.seekg( 0 );
		char * out = new char[ fileLength + 1 ];
		file.read( out, fileLength );
		return out;
	}

	void ReadXMLFile()
	{
		try
		{
			_doc.parse<0>(_contents.get());
		}
		catch( rapidxml::parse_error e )
		{
			e.what();
		}
	}

	virtual void Create() = 0;

	void ClearDocument()
	{
		_doc.clear();
	}


private:
	inline char * stringToChar( std::string const & s )
	{
		unsigned int N = s.length();
		char * out = new char[ N + 1 ];
		std::copy( s.c_str(), ( s.c_str() + N - 1 ), out );
		return out;
	}

};
