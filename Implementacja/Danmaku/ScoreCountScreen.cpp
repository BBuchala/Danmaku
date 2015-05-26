#include "ScoreCountScreen.h"

ScoreCountScreen::ScoreCountScreen( GraphicsDevice * const gDevice ) : Playfield(gDevice), elapsedTime(0.0f)
{
	this->background = new Sprite(gDevice->device, Sprite::GetFilePath( "titlescreen", "png"));

	
};


ScoreCountScreen::~ScoreCountScreen()
{
	if (this->background) delete this->background;
};


bool ScoreCountScreen::Initialize()
{
	return true;
};


void ScoreCountScreen::Update(float const time)
{

};



void ScoreCountScreen::DrawScene()
{

};
	


void ScoreCountScreen::Clear()
{
	this->gDevice->Clear( D3DXCOLOR ( 1.0f, 1.0f, 1.0f ) );
};