#pragma once

#include "Font.h"
#include "Playfield.h"
#include "Sprite.h"
#include "XmlParser.h"

class ScoreField: public Playfield, public XmlParser
{
	Sprite * _background;
	D3DXVECTOR2 _BGposition;

	typedef std::vector<std::string>	Entry;
	typedef std::vector<Entry>			EntryVector;
	EntryVector _entry;

	std::vector<Font*> _entryText;

	GraphicsDevice * _gDevice;

public:
	ScoreField(GraphicsDevice * const gDevice, EndStageInfo * endStageInfo, std::string const & file)
		: Playfield(gDevice), XmlParser(file)
	{
		_background = new Sprite(gDevice->device, Sprite::GetFilePath("scoresscreen"));
		_BGposition = D3DXVECTOR2(0.0f, 0.0f);
		this->previousStageInfo = endStageInfo;
		endStageInfo->nextMode = ScreenMode::TITLE;
		_gDevice = gDevice;
	};

	void Create() override
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
		this->ClearDocument();
	};

	void Update(float const time) override
	{
		if (this->input->KeyDownOne(DIK_ESCAPE))
		{
			this->ended = true;
		}
	}
	void DrawScene() override
	{
		_background->Draw(_BGposition);
		_entryText[0]->Draw("Nick", 12);
		_entryText[1]->Draw("Score", 12);
		_entryText[2]->Draw("Date", 12);
		for (int i = 0; i < _entryText.size() - 3; i++)
		{
			_entryText[i + 3]->Draw(_entry[i / 3][i % 3], 12);
		}
	}

	bool Initialize() override
	{
		this->Start();
		for (int i = 0; i < 3; i++)
		{
			Font * newEntry = new Font( D3DXVECTOR2( (i + 1) * 200, 30 ), 400, 60 );
			newEntry->Initialize( _gDevice, 40, 0, "Arial", true, false, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f) );
			_entryText.push_back(newEntry);
		}
		for (int i = 0; i < _entry.size(); i++)
		{
			for (int j = 0; j < 3; j++)
			{
				Font * newEntry = new Font( D3DXVECTOR2( (j + 1) * 200, 50 + (i + 1) * 50 ), 400, 60 );
				newEntry->Initialize( _gDevice, 40, 0, "Arial", true, false, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f) );
				_entryText.push_back(newEntry);
			}
		}
		return true;
	}

	EndStageInfo * ReturnInformation() override
	{
		return previousStageInfo;
	};
};
