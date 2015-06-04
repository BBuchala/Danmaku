#pragma once

#include <Windows.h>
#include <vector>

#include "Button.h"
#include "GraphicsDevice.h"
#include "Playfield.h"
#include "Sprite.h"
#include "ScoreField.h"

class TitleScreen : public Playfield
{
	//// Liczba przycisków
	static const unsigned short BUTTON_CNT = 4;
	//// Wybrany przycisk
	static unsigned short _chosenButton;

	//// Elementy ekranu
	// t³o
	Sprite * _background;		
	D3DXVECTOR2 BGposition;
	// przyciski
	typedef std::vector<Button*> ButtonVector;
	ButtonVector _button;

	bool enter;

public:
	TitleScreen( GraphicsDevice * const gDevice, EndStageInfo * endStageInfo );
	~TitleScreen();

	bool Initialize() override;
	void Clear();
	void Update(float const time) override;
	void DrawScene() override;

	EndStageInfo * ReturnInformation() override;
};