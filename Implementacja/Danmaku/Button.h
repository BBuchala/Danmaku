#pragma once

#include "GraphicsDevice.h"
#include "ButtonType.h"
#include "Sprite.h"

class Button
{
	Sprite * _sprite;		// sprajt z paroma teksturami
	D3DXVECTOR2 _position;	// pozycja na ekranie
	ButtonType _tag;		// nazwa funkcji przycisku

	// obs³uga pulsowania - czas i wielkoœæ
	float _elapsedTime;
	float _buttonScale;

public:
	// Konstruktor
	Button(D3DXVECTOR2 const & position, ButtonType const tag);
	// Destruktor
	~Button();

	// Inicjalizacja grafiki przycisku
	void Initialize(GraphicsDevice * const gDevice, std::vector<std::string> const & fileVector);

	void Update(float time);
	void Draw();

	// obs³uga animacji przycisku
	void Press();
	void Unpress();
	void ResetAnimation();

	/// <summary>
	/// Zwrócenie rodzaju przycisku.
	/// </summary>
	/// <returns></returns>
	inline ButtonType GetType() const
	{
		return _tag;
	}

};
