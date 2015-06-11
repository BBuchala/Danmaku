#pragma once

#include <vector>
#include "XmlParser.h"

class ScoreParser: public XmlParser
{
	// maksymalna liczba zapisanych wynik�w gry
	static const unsigned short MAX_RECORDS = 12;

	// rekordy z wynikami
	typedef std::vector<std::string>	Entry;
	typedef std::vector<Entry>			EntryVector;
	EntryVector _entry;

public:
	// Konstruktor
	ScoreParser(std::string const & file);
	// Przetowrzenie pliku
	void Create() override;

	// Zwr�cenie rekord�w
	inline EntryVector GetEntries() const
	{
		return _entry;
	};

	inline unsigned short GetMaxRecordNumber() const
	{
		return MAX_RECORDS;
	}
};
