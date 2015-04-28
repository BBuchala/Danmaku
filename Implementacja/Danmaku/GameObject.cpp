#include "GameObject.h"

////////// KONSTRUKTOR ///////////////////////
GameObject::GameObject(float const x, float const y, float const speed, float const acc)
	: acceleration(acc)
{
	///// Przydzielenie wartoœci sk³adowym
	this->SetPosition(x, y);
	this->speed = speed < 0 ? 0 : speed;
	this->hitbox = NULL;

	///// Przydzielenie pamiêci obiektom klas
	this->sprite = SpritePtr(new Sprite());
};


////////// DESTRUKTOR ///////////////////////
GameObject::~GameObject()
{
};


GameObject::GameObject( GameObject const & go )
{
	this->position = go.position;
	this->speed = go.speed;
	this->acceleration = go.acceleration;
	this->sprite = SpritePtr(go.GetSprite());
	this->hitbox = HitboxPtr(go.GetHitbox());
};


bool GameObject::InitializeSprite(LPDIRECT3DDEVICE9 device, std::string const & file, UINT const width, UINT const height)
{
	if ( !this->sprite || !this->sprite->Initialize(device, file, width, height ) )
	{
		return false;
	}
	return true;
};


bool GameObject::InitializeSprite(LPDIRECT3DDEVICE9 device, std::vector<std::string> const & fileVect, UINT const width, UINT const height)
{
	if ( !this->sprite || !this->sprite->Initialize(device, fileVect, width, height) )
	{
		return false;
	}
	return true;
};


bool GameObject::InitializeSprite( SpritePtr const & sprite )
{
	this->sprite = SpritePtr(sprite);
	return true;
};


bool GameObject::InitializeHitbox( BYTE const radius )
{
	float newRadius;
	if (radius == DEFAULT_HITBOX_RADIUS)
		newRadius = min( this->sprite->GetWidth(), this->sprite->GetHeight() ) / 4.0f;
	else
		newRadius = static_cast<float>(radius);
	this->hitbox = HitboxPtr( new Hitbox( newRadius ) );
	return true;
};


bool GameObject::InitializeHitbox( BYTE const radius, std::string const & spritePath,
								   GraphicsDevice * const gDevice )
{
	this->InitializeHitbox(radius);
	if (!spritePath.empty() && gDevice != nullptr )
	{
		this->hitbox->InitializeSprite( gDevice->device, spritePath );
	}
	return true;
};


void GameObject::Draw()
{
	if (this->sprite)
	{
		this->sprite->Draw(this->position);
		if (this->hitbox != NULL && this->hitbox->UseSprite())
		{
			this->hitbox->Draw( this->GetCenterPoint() );
		}
	}
};


void GameObject::Update(float const time)
{
	this->speed += this->acceleration * time;
};


void GameObject::SetPosition(D3DXVECTOR2 const & v)
{
	this->position = v;
};


void GameObject::SetPosition(float const x, float const y)
{
	this->position.x = x;
	this->position.y = y;
};

void GameObject::SetAcceleration(float const acc)
{
	this->acceleration = acc;
};


void GameObject::Rotate( float const angle )
{
	this->sprite->Rotate( angle );
};



void GameObject::Scale( float const scale )
{
	this->sprite->Scale( scale );
	this->hitbox->Scale( scale );
};



void GameObject::Translate( float const dx, float const dy )
{
	this->position.x += dx;
	this->position.y += dy;
};


void GameObject::Translate( D3DXVECTOR2 const & dv )
{
	this->position += dv;
};

