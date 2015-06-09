#pragma once

#include <vector>
#include "XmlParser.h"

class ScoreParser: public XmlParser
{
	// rekordy z wynikami
	typedef std::vector<std::string>	Entry;
	typedef std::vector<Entry>			EntryVector;
	EntryVector _entry;

public:
	// Konstruktor
	ScoreParser(std::string const & file);
	// Przetowrzenie pliku
	void Create() override;

	// Zwrócenie rekordów
	inline EntryVector GetEntries() const
	{
		return _entry;
	};
};
