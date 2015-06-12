#pragma once

#include <vector>
#include "XmlParser.h"

/// <summary>
/// Parser pliku z wynikami
/// </summary>
class ScoreParser: public XmlParser
{
	// maksymalna liczba zapisanych wyników gry
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

	ULONG GetHighestScore();

	/// <summary>
	/// Zwrócenie rekordów.
	/// </summary>
	/// <returns></returns>
	inline EntryVector GetEntries() const
	{
		return _entry;
	};

	/// <summary>
	/// Zwrócenie maksymalnej liczby rekordów.
	/// </summary>
	/// <returns></returns>
	inline unsigned short GetMaxRecordNumber() const
	{
		return MAX_RECORDS;
	}
};
