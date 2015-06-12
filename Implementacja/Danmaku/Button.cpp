#include "Button.h"

/// <summary>
/// Tworzy now¹ instacjê klasy <see cref="Button"/>.
/// </summary>
/// <param name="position">The position.</param>
/// <param name="tag">The tag.</param>
Button::Button(D3DXVECTOR2 const & position, ButtonType const tag) : _position(position), _tag(tag), 
	_elapsedTime(0.0f), _buttonScale(1.0f)
{
};

/// <summary>
/// Niszczy instancjê klasy <see cref="Button"/>.
/// </summary>
Button::~Button()
{
	delete _sprite;
};


/// <summary>
/// Inicjalizacja przycisku.
/// </summary>
/// <param name="gDevice">Ur¿adzenie do tworzenia grafiki.</param>
/// <param name="fileVector">Zbiór œcie¿ek do plików.</param>
void Button::Initialize(GraphicsDevice * const gDevice, std::vector<std::string> const & fileVector)
{
	_sprite = new Sprite(gDevice->device, fileVector);
	_sprite->SetCurrentTexture(0);
};


/// <summary>
/// Aktualizuje stan.
/// </summary>
/// <param name="time">Próbka czasu.</param>
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


/// <summary>
/// Narysowanie pocisku.
/// </summary>
void Button::Draw()
{
	_sprite->Draw(_position, _buttonScale);
};


/// <summary>
/// Wciœniêcie przycisku.
/// </summary>
void Button::Press()
{
	_sprite->SetCurrentTexture(1);
};

/// <summary>
/// Odciœniêcie przycisku.
/// </summary>
void Button::Unpress()
{
	_sprite->SetCurrentTexture(0);
};

/// <summary>
/// Reset animacji.
/// </summary>
void Button::ResetAnimation()
{
	_buttonScale = 1.0f;
	_elapsedTime = 0.0f;
};
