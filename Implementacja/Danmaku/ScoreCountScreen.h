#pragma once

#include <Windows.h>
#include <vector>

#include "GraphicsDevice.h"
#include "Playfield.h"
#include "Sprite.h"
#include "Font.h"

#define D3DXCOLOR( r, g, b ) D3DCOLOR_COLORVALUE( r, g, b, 0xFF )

class ScoreCountScreen : public Playfield
{

	Sprite * background;

	float elapsedTime;

public:
	ScoreCountScreen( GraphicsDevice * const gDevice );
	~ScoreCountScreen();

	bool Initialize() override;
	void Clear();
	void Update(float const time) override;
	void DrawScene() override;

};