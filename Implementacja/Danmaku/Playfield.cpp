#include "Playfield.h"

Playfield::Playfield()
{
	this->ended = false;
};


Playfield::~Playfield()
{
	if (this->timer) delete this->timer;
};


bool Playfield::Initialize(HWND & hWnd, GraphicsDevice * const gDevice)
{
	this->gDevice = gDevice;
	this->timer = new Timer();
	if (!this->timer->Start())
	{
		return false;
	}
	return true;
};



void Playfield::Run()
{
	this->timer->Update();
	this->Update( timer->elapsedTime );
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