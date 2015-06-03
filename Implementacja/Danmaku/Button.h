#pragma once

#include "GraphicsDevice.h"
#include "ButtonType.h"
#include "Sprite.h"

class Button
{
	Sprite * _sprite;		// sprajt z paroma teksturami
	D3DXVECTOR2 _position;	// pozycja na ekranie
	ButtonType _tag;		// nazwa funkcji przycisku

	float _elapsedTime;
	float _buttonScale;
	bool _pressed;

public:
	Button(D3DXVECTOR2 const & position, ButtonType const tag) : _position(position), _tag(tag), 
		_elapsedTime(0.0f), _buttonScale(1.0f), _pressed(false)
	{
	};

	~Button()
	{
		delete _sprite;
	};

	void Initialize(GraphicsDevice * const gDevice, std::vector<std::string> const & fileVector)
	{
		_sprite = new Sprite(gDevice->device, fileVector);
		_sprite->SetCurrentTexture(0);
	}

	void Update(float time)
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
	}

	void Draw()
	{
		_sprite->Draw(_position, _buttonScale);
	}

	inline ButtonType GetType() const
	{
		return _tag;
	}

	void Press()
	{
		_pressed = true;
		_sprite->SetCurrentTexture(1);
	}

	void Unpress()
	{
		_pressed = false;
		_sprite->SetCurrentTexture(0);
	}

	inline bool IsPressed() const
	{
		return _pressed;
	}

	void ResetAnimation()
	{
		_buttonScale = 1.0f;
		_elapsedTime = 0.0f;
	}
};
