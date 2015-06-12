#include "Hitbox.h"

/// <summary>
/// Tworzy now� instacj� klasy <see cref="Hitbox"/>.
/// </summary>
/// <param name="position">The position.</param>
Hitbox::Hitbox( D3DXVECTOR2 * const position ) : _theta(0.0f)
{
	_position = const_cast<D3DXVECTOR2*>(position);
};


/// <summary>
/// Translacja.
/// </summary>
/// <param name="translate">Warto�� przesuni�cia.</param>
void Hitbox::Translate( D3DXVECTOR2 const & translate )
{
	*_position += translate;
};


/// <summary>
/// Obr�t o zadany k�t.
/// </summary>
/// <param name="theta">Kat.</param>
void Hitbox::Rotate( float const theta )
{
	_theta += theta;
};


/// <summary>
/// Zwraca odpowiednik dzielnik w celu utworzenia odpowiedniej wielko�ci hitboxa.
/// </summary>
/// <param name="hSize">Rozmiar.</param>
/// <returns></returns>
float Hitbox::GetDivisor(Hitbox::Size hSize)
{
	switch(hSize)
	{
	case ONE_THIRDS_LENGTH:
		return 6.0f;
	case HALF_LENGTH: default:
		return 4.0f;
	case TWO_THIRDS_LENGTH:
		return 3.0f;
	case FULL_LENGTH:
		return 2.0f;
	case EXTENDED_LENGTH:
		return 1.00f;
	}
};
