#include "Hitbox.h"

Hitbox::Hitbox( Hitbox::Shape const shape, Hitbox::Size const size, float const radiusA, float const radiusB, D3DXVECTOR2 const & position )
	: theta(0.0f)
{
	float divisor;
	switch(size)
	{
	case ONE_THIRDS_LENGTH:
		divisor = 6.0f;
		break;
	case HALF_LENGTH: default:
		divisor = 4.0f;
		break;
	case TWO_THIRDS_LENGTH:
		divisor = 3.0f;
		break;
	case FULL_LENGTH:
		divisor = 2.0f;
		break;
	}
	switch(shape)
	{
	case CIRCLE:
		radiusA_ = radiusB_ = min(radiusA, radiusB) / divisor;
		break;
	case ELLIPSE:
		radiusA_ = radiusA / divisor;
		radiusB_ = radiusB / divisor;
		break;
	}
	this->position = const_cast<D3DXVECTOR2*>(&position);
};

Hitbox::Hitbox( Hitbox const & h) : radiusA_(h.radiusA_), radiusB_(h.radiusB_), theta(h.theta)
{
};

void Hitbox::Translate( D3DXVECTOR2 const & translate )
{
	*this->position += translate;
};


void Hitbox::Scale( float const scale )
{
	radiusA_ *= scale;
	radiusB_ *= scale;
};


void Hitbox::Rotate( float const theta )
{
	this->theta += theta;
};


void Hitbox::SetRadius( float const radius )
{
	SetRadius(radius, radius);
};


void Hitbox::SetRadius( float const radiusA, float const radiusB )
{
	radiusA_ = radiusA;
	radiusB_ = radiusB;
};


