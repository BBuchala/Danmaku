#pragma once

#include "Font.h"
#include "Playfield.h"
#include "Sprite.h"
#include "ScoreParser.h"

class ScoreField: public Playfield
{
	typedef std::vector<std::string>	Entry;
	typedef std::vector<Entry>			EntryVector;

	Sprite * _background;
	D3DXVECTOR2 _BGposition;

	std::vector<Font*> _entryText;

	GraphicsDevice * _gDevice;

	ScoreParser * _scores;

public:
	ScoreField(GraphicsDevice * const gDevice, EndStageInfo * endStageInfo)
		: Playfield(gDevice)
	{
		_background = new Sprite(gDevice->device, Sprite::GetFilePath("scoresscreen"));
		_BGposition = D3DXVECTOR2(0.0f, 0.0f);
		this->previousStageInfo = endStageInfo;
		endStageInfo->nextMode = ScreenMode::TITLE;
		_gDevice = gDevice;
		_scores = new ScoreParser("scores/scores.xml");
	};

	~ScoreField()
	{
		delete _scores;
	}

	void Update(float const time) override
	{
		if (this->input->KeyDownOne(DIK_ESCAPE))
		{
			this->ended = true;
			_scores->ClearDocument();
		}
	}
	void DrawScene() override
	{
		EntryVector entry = _scores->GetEntries();
		_background->Draw(_BGposition);
		_entryText[0]->Draw("Nick", 12);
		_entryText[1]->Draw("Score", 12);
		_entryText[2]->Draw("Date", 12);
		for (int i = 0; i < _entryText.size() - 3; i++)
		{
			_entryText[i + 3]->Draw(entry[i / 3][i % 3], 12);
		}
	}

	bool Initialize() override
	{
		_scores->Start();
		for (int i = 0; i < 3; i++)
		{
			Font * newEntry = new Font( D3DXVECTOR2( (i + 1) * 200, 30 ), 400, 60 );
			newEntry->Initialize( _gDevice, 40, 0, "Arial", true, false, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f) );
			_entryText.push_back(newEntry);
		}
		for (int i = 0; i < _scores->GetEntries().size(); i++)
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
