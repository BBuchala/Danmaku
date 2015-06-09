#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <Windows.h>


using namespace rapidxml;

class XmlParser
{
protected:
	std::string _filePath;				// �cie�ka do parsowanego pliku
	rapidxml::xml_document <> _doc;		// plik z danymi
	std::unique_ptr<char> _contents;
	// zawarto�� pliku XML
	bool prawda = false;
	int numbers;

public:
	// Konstruktor
	XmlParser(std::string const & file);

	// sprasowanie pliku
	void Start();

	// pobranie zawarto�ci pliku i przypisanie jej do _contents
	void GetContents();

	// Konwersja XML na char*
	char * XML2Char ( std::string const & stageFile );

	// sprawdznie poprawno�ci pliku xml i przypisanie do zmiennej _doc
	void ReadXMLFile();

	// spos�b parsowania plikku
	virtual void Create() = 0;

	// usuni�cie dokumentu z pami�ci
	void ClearDocument();


private:
	// zmiana stringu z danymi pliku na char* zrozumia�y dla biblioteki
	inline char * stringToChar( std::string const & s )
	{
		unsigned int N = s.length();
		char * out = new char[ N + 1 ];
		std::copy( s.c_str(), ( s.c_str() + N - 1 ), out );
		return out;
	};
};
