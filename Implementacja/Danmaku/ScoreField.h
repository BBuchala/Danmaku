#pragma once

#include "Font.h"
#include "Playfield.h"
#include "Sprite.h"
#include "ScoreParser.h"

class ScoreField: public Playfield
{
	typedef std::vector<std::string>	Entry;
	typedef std::vector<Entry>			EntryVector;

	// t³o
	Sprite * _background;
	D3DXVECTOR2 _BGposition;
	// pozycje scorów
	std::vector<Font*> _entryText;
	// urz¹dzenie do rysowania
	GraphicsDevice * _gDevice;
	// sparsowane wyniki
	ScoreParser * _scores;

public:
	// Konstruktor
	ScoreField(GraphicsDevice * const gDevice, EndStageInfo * endStageInfo);
	// Destruktor
	~ScoreField();

	// obs³uga pola
	void Update(float const time) override;
	void DrawScene() override;
	bool Initialize() override;
	EndStageInfo * ReturnInformation() override;
};
