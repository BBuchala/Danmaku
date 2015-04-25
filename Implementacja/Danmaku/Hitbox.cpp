#include "Hitbox.h"

Hitbox::Hitbox() : theta(0.0f)
{
	SetRadius(0.0f);
	SetUseSprite(false);
	this->sprite = NULL;
};

Hitbox::Hitbox( float const & radius, bool useSprite ) : theta(0.0f)
{
	SetRadius(radius);
	SetUseSprite(useSprite);
	if (useSprite)
		this->sprite = new Sprite();
	else
		this->sprite = NULL;
};



bool Hitbox::InitializeSprite( LPDIRECT3DDEVICE9 device, std::string const & file, short const & width )
{
	if (!this->sprite || !this->sprite->Initialize(device, file, width, width) )
	{
		return false;
	}
	this->SetRadius( width / 4.0f );
	return true;
};


void Hitbox::Translate( D3DXVECTOR2 const & translate )
{
	// this->position += translate;
};


void Hitbox::Scale( float const & scale )
{
	this->radius *= scale;
	if (sprite)
		sprite->Scale(scale);
};


void Hitbox::Rotate( float const & theta )
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



void Hitbox::SetRadius( float const & radius )
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


