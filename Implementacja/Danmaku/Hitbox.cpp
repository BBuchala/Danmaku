#include "Hitbox.h"

Hitbox::Hitbox()
{
	Hitbox(0.0f);
};

Hitbox::Hitbox( float const radius ) : theta(0.0f), radius(radius), useSprite(false)
{
	this->sprite = nullptr;
};



bool Hitbox::InitializeSprite( LPDIRECT3DDEVICE9 device, std::string const & file )
{
	this->sprite = new Sprite();
	this->useSprite = true;
	if ( !this->sprite || !this->sprite->Initialize(device, file, 4 * radius, 4 * radius ) )
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
	this->radius *= scale;
	if (sprite)
		sprite->Scale(scale);
};


void Hitbox::Rotate( float const theta )
{
	if (sprite)
		sprite->Rotate( theta );
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
	this->radius = radius;
};


void Hitbox::SetPosition( D3DXVECTOR2 const & position )
{
	// this->position = position;
};


void Hitbox::SetUseSprite( bool useSprite )
{
	this->useSprite = useSprite;
};


