#include "Button.h"

/* ---- Konstruktor
   ------------------------------------------------------------------------------------------- */
Button::Button(D3DXVECTOR2 const & position, ButtonType const tag) : _position(position), _tag(tag), 
	_elapsedTime(0.0f), _buttonScale(1.0f)
{
};

/* ---- Destruktor
   ------------------------------------------------------------------------------------------- */
Button::~Button()
{
	delete _sprite;
};

/* ---- Initialize
   ------------------------------------------------------------------------------------------- */
void Button::Initialize(GraphicsDevice * const gDevice, std::vector<std::string> const & fileVector)
{
	_sprite = new Sprite(gDevice->device, fileVector);
	_sprite->SetCurrentTexture(0);
};

/* ---- Update
   ------------------------------------------------------------------------------------------- */
void Button::Update(float time)
{
	// pulsowanie pocisku
	_elapsedTime += time;
	if (_elapsedTime > 0.0000000f && _elapsedTime < 1.0000000f)
	{
		_buttonScale *= 100.0f / 99.75f;
	}
	else if (_elapsedTime < 2.0000000f)
	{
		_buttonScale *= 99.75f / 100.0f;
	}
	else
	{
		ResetAnimation();
	}
};

/* ---- Draw
   ------------------------------------------------------------------------------------------- */
void Button::Draw()
{
	_sprite->Draw(_position, _buttonScale);
};

/* ---- Press
   ------------------------------------------------------------------------------------------- */
void Button::Press()
{
	_sprite->SetCurrentTexture(1);
};

/* ---- Unpress
   ------------------------------------------------------------------------------------------- */
void Button::Unpress()
{
	_sprite->SetCurrentTexture(0);
};

/* ---- Reset Animation
   ------------------------------------------------------------------------------------------- */
void Button::ResetAnimation()
{
	_buttonScale = 1.0f;
	_elapsedTime = 0.0f;
};
