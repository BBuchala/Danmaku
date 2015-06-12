#include "ScoreParser.h"


/// <summary>
/// Tworzy now¹ instacjê klasy <see cref="ScoreParser"/>.
/// </summary>
/// <param name="file">Plik wejœciowy.</param>
ScoreParser::ScoreParser(std::string const & file) : XmlParser(file)
{
};


/// <summary>
/// Przetowrzenie pliku.
/// </summary>
void ScoreParser::Create()
{
	xml_node <> * firstNode = _doc.first_node();
	for(xml_node <> * entry = firstNode->first_node(); entry; entry = entry->next_sibling())
	{
		std::string nick, score, date;
		Entry newEntry;
		for (xml_attribute <>* entryAtr = entry->first_attribute(); entryAtr; entryAtr = entryAtr->next_attribute())
		{
			std::string str(entryAtr->name());
			if (str.compare("nick") == 0)
			{
				nick = std::string(entryAtr->value());
				newEntry.push_back(nick);
			}
			else if (str.compare("score") == 0)
			{
				score = std::string(entryAtr->value());
				newEntry.push_back(score);
			}
			else if (str.compare("date") == 0)
			{
				date = std::string(entryAtr->value());
				newEntry.push_back(date);
			}
		}
		_entry.push_back(newEntry);
	}
};


/// <summary>
/// Zwrócenie najwy¿szego wyniku z zapisanych.
/// </summary>
/// <returns></returns>
ULONG ScoreParser::GetHighestScore()
{
	ULONG highestScore = 0;
	for(EntryVector::const_iterator it = _entry.begin(); it != _entry.end(); ++it)
	{
		ULONG score = std::stol((*it)[1]);
		if (score > highestScore) highestScore = score;
	}
	return highestScore;
};
