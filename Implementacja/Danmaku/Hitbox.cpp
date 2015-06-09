#include "Hitbox.h"

Hitbox::Hitbox( D3DXVECTOR2 * const position ) : _theta(0.0f)
{
	_position = const_cast<D3DXVECTOR2*>(position);
};


void Hitbox::Translate( D3DXVECTOR2 const & translate )
{
	*_position += translate;
};


void Hitbox::Rotate( float const theta )
{
	_theta += theta;
};


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
