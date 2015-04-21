#include "Playfield.h"

Playfield::Playfield()
{
	this->ended = this->resetTimer = false;
};


Playfield::~Playfield()
{
};


bool Playfield::Initialize(HWND & hWnd, GraphicsDevice * const gDevice)
{
	this->gDevice = gDevice;
	return true;
};


void Playfield::Run( float const & dt )
{
	this->Update( dt );
	this->Draw();
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
	this->gDevice->Clear( D3DXCOLOR ( 0, 0, 0 ) );
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