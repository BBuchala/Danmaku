#include "ScoreParser.h"

/* ---- Konstruktor
   ------------------------------------------------------------------------------------------- */
ScoreParser::ScoreParser(std::string const & file) : XmlParser(file)
{
};

/* ---- Create
   ------------------------------------------------------------------------------------------- */
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
