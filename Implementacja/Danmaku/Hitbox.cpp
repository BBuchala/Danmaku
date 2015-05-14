#include "Hitbox.h"

Hitbox::Hitbox( Hitbox::Shape const shape, Hitbox::Size const size, float const radiusA, float const radiusB )
	: theta(0.0f), useSprite(false), sprite(nullptr)
{
	float divisor;
	switch(size)
	{
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
};

Hitbox::Hitbox( Hitbox const & h) : radiusA_(h.radiusA_), radiusB_(h.radiusB_), theta(h.theta), 
	useSprite(h.useSprite)
{
};


bool Hitbox::InitializeSprite( LPDIRECT3DDEVICE9 device, std::string const & file )
{
	this->sprite = new Sprite();
	this->useSprite = true;
	if ( !this->sprite || !this->sprite->Initialize(device, file, 4 * radiusA_, 4 * radiusB_ ) )
	{
		return false;
	}
	return true;
};


void Hitbox::Translate( D3DXVECTOR2 const & translate )
{
	// this->position += translate;
};


void Hitbox::Scale( float const scale )
{
	radiusA_ *= scale;
	radiusB_ *= scale;
	if (sprite)
		sprite->Scale(scale);
};


void Hitbox::Rotate( float const theta )
{
	if (sprite)
		sprite->Rotate( theta );
	this->theta += theta;
};


void Hitbox::Draw(D3DXVECTOR2 const & position)
{
	if (sprite)
	{
		sprite->Draw( D3DXVECTOR2 ( position.x - this->sprite->GetWidth() / 2.0f, position.y - this->sprite->GetWidth() / 2.0f ) );
	}
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


void Hitbox::SetPosition( D3DXVECTOR2 const & position )
{
	// this->position = position;
};


void Hitbox::SetUseSprite( bool useSprite )
{
	this->useSprite = useSprite;
};


