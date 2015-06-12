#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <Windows.h>

#include "XmlOpenFailedException.h"
#include "XmlParseFailedException.h"

using namespace rapidxml;

/// <summary>
/// Klasa odpowiadaj¹ca za parsowanie plików XML
/// </summary>
class XmlParser
{
protected:
	std::string _filePath;				// œcie¿ka do parsowanego pliku
	rapidxml::xml_document <> _doc;		// plik z danymi
	std::unique_ptr<char> _contents;	// zawartoœæ pliku XML

public:
	// Konstruktor
	XmlParser(std::string const & file);

	// sprasowanie pliku
	void Start();

	// pobranie zawartoœci pliku i przypisanie jej do _contents
	void GetContents();

	// Konwersja XML na char*
	char * XML2Char ( std::string const & stageFile );

	// sprawdznie poprawnoœci pliku xml i przypisanie do zmiennej _doc
	void ReadXMLFile();

	// sposób parsowania plikku
	virtual void Create() = 0;

	// usuniêcie dokumentu z pamiêci
	void ClearDocument();


private:
	/// <summary>
	/// Zmiana stringu z danymi pliku na char* zrozumia³y dla biblioteki
	/// </summary>
	/// <param name="s">String.</param>
	/// <returns></returns>
	inline char * stringToChar( std::string const & s )
	{
		unsigned int N = s.length();
		char * out = new char[ N + 1 ];
		std::copy( s.c_str(), ( s.c_str() + N - 1 ), out );
		return out;
	};
};
