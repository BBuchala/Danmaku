#include "ConfigParser.h"


/// <summary>
/// Tworzy now¹ instacjê klasy <see cref="ConfigParser"/>.
/// </summary>
/// <param name="file">Plik wejœciowy.</param>
/// <param name="input">Input gry.</param>
ConfigParser::ConfigParser(std::string const & file, Input * input) : XmlParser(file)
{
	_gameInput = input;
};


/// <summary>
/// Sparsowanie pliku.
/// </summary>
void ConfigParser::Create()
{
	xml_node <> * firstNode = _doc.first_node();
	for(xml_node <> * entry = firstNode->first_node(); entry; entry = entry->next_sibling())
	{
		std::string str(entry->name());
		if (str.compare("Lifes") == 0)
		{
			for (xml_attribute <>* entryAtr = entry->first_attribute(); entryAtr; entryAtr = entryAtr->next_attribute())
			{
				str = entryAtr->name();
				if (str.compare("number") == 0)
				{
					this->lifeNumber = std::stoi(entryAtr->value());
				}
			}
		}
		else if (str.compare("Bombs") == 0)
		{
			for (xml_attribute <>* entryAtr = entry->first_attribute(); entryAtr; entryAtr = entryAtr->next_attribute())
			{
				str = entryAtr->name();
				if (str.compare("number") == 0)
				{
					this->bombNumber = std::stoi(entryAtr->value());
				}
			}
		}
		else if (str.compare("Controls") == 0)
		{
			for(xml_node <> * keyNode = entry->first_node(); keyNode; keyNode = keyNode->next_sibling())
			{
				str = keyNode->name();
				if (str.compare("Key") == 0)
				{
					std::string keyType, keyName;
					for (xml_attribute <>* keyAtr = keyNode->first_attribute(); keyAtr; keyAtr = keyAtr->next_attribute())
					{
						str = keyAtr->name();
						if (str.compare("type") == 0)
						{
							keyType = keyAtr->value();
						}
						else if (str.compare("key") == 0)
						{
							keyName = keyAtr->value();
						}
					}
					this->keyMap[String2GameControl(keyType)] = _gameInput->KeyNumber(keyName);
				}
			}
		}
	}
};


/// <summary>
/// Uruchomienie parsowania.
/// </summary>
void ConfigParser::Initialize()
{
	this->Start();
}


/// <summary>
/// Zapisanie dokonanych zmian do pliku.
/// </summary>
void ConfigParser::SaveOptions()
{
	xml_node <> * firstNode = _doc.first_node();
	for(xml_node <> * entry = firstNode->first_node(); entry; entry = entry->next_sibling())
	{
		std::string str(entry->name());
		if (str.compare("Lifes") == 0)
		{
			for (xml_attribute <>* entryAtr = entry->first_attribute(); entryAtr; entryAtr = entryAtr->next_attribute())
			{
				std::string str(entryAtr->name());
				if (str.compare("number") == 0)
				{
					entryAtr->value(_doc.allocate_string(std::to_string(this->lifeNumber).c_str()));
				}
			}
		}
		else if (str.compare("Bombs") == 0)
		{
			for (xml_attribute <>* entryAtr = entry->first_attribute(); entryAtr; entryAtr = entryAtr->next_attribute())
			{
				std::string str(entryAtr->name());
				if (str.compare("number") == 0)
				{
					entryAtr->value(_doc.allocate_string(std::to_string(this->bombNumber).c_str()));
				}
			}
		}
		else if (str.compare("Controls") == 0)
		{
			for(xml_node <> * keyNode = entry->first_node(); keyNode; keyNode = keyNode->next_sibling())
			{
				str = keyNode->name();
				if (str.compare("Key") == 0)
				{
					std::string type;
					for (xml_attribute <>* keyAtr = keyNode->first_attribute(); keyAtr; keyAtr = keyAtr->next_attribute())
					{
						str = keyAtr->name();
						if (str.compare("type") == 0)
						{
							type = keyAtr->value();
						}
						else if (str.compare("key") == 0)
						{
							keyAtr->value(_doc.allocate_string(_gameInput->KeyName(this->keyMap[String2GameControl(type)]).c_str()));
							break;
						}
					}
				}
			}
		}
	}
	std::ofstream file;
	file.open(_filePath, std::ofstream::out);
	file << _doc;
	_gameInput->SetGameControls(this->keyMap);
};
