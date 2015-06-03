#include "Playfield.h"

Playfield::Playfield( GraphicsDevice * const gDevice ) : gDevice(gDevice), ended(false)
{
};


Playfield::~Playfield()
{
};


void Playfield::InitializeKeyboardInput(Input const * input)
{
	this->input = const_cast<Input*>(input);
};


void Playfield::Run( float const dt )
{
	this->Update( dt );
	this->Draw();
	this->clearOutOfBoundsObjects();
};



void Playfield::Draw()
{
	this->Clear();
	this->BeginScene();
	this->DrawScene();
	this->EndScene();
};


void Playfield::Clear()
{
	this->gDevice->Clear( MYCOLOR ( 0, 0, 0 ) );
};


void Playfield::BeginScene()
{
	this->gDevice->Begin();
};


void Playfield::EndScene()
{
	this->gDevice->End();
	this->gDevice->Present();
};

EndStageInfo * Playfield::ReturnInformation()
{
	return new EndStageInfo();
};