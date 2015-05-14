#include "GameObject.h"

////////// KONSTRUKTOR ///////////////////////
GameObject::GameObject(float const x, float const y, float const speed, float const acc)
	: acceleration(acc)
{
	///// Przydzielenie wartoœci sk³adowym
	this->SetPosition(x, y);
	this->speed = speed;
	this->hitbox = NULL;

	///// Przydzielenie pamiêci obiektom klas
	this->sprite = SpritePtr(new Sprite());
};


////////// DESTRUKTOR ///////////////////////
GameObject::~GameObject()
{
};


GameObject::GameObject( GameObject const & go ) : hitbox(new Hitbox(*go.hitbox))
{
	this->position = go.position;
	this->speed = go.speed;
	this->acceleration = go.acceleration;
	this->sprite = go.sprite;
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


bool GameObject::InitializeHitbox( Hitbox::Shape const shape, Hitbox::Size const size )
{
	this->hitbox = HitboxPtr( new Hitbox( shape, size, sprite->GetWidth(), sprite->GetHeight() ) );
	return true;
};


bool GameObject::InitializeHitbox( Hitbox::Shape const shape, Hitbox::Size const size,
								  std::string const & spritePath, LPDIRECT3DDEVICE9 device )
{
	this->InitializeHitbox(shape, size);
	if (!spritePath.empty() && device != nullptr )
	{
		this->hitbox->InitializeSprite( device, spritePath );
	}
	return true;
};


void GameObject::Draw( RECT const & rect )
{
	if (this->sprite && IsObjectWithinBounds(rect))
	{
		this->sprite->Draw(this->position);
		if (this->hitbox != NULL && this->hitbox->UseSprite())
		{
			this->hitbox->Draw( this->GetCenterPoint() );
		}
	}
};


bool GameObject::IsObjectWithinBounds( RECT const & rect )
{
	D3DXVECTOR2 center = this->GetCenterPoint();
	D3DXVECTOR2 diffPos = center - this->GetPosition();
	// je¿eli ca³y sprajt 
	if (center.x + diffPos.x < rect.left	||	// jest za lew¹ œcian¹ lub
		center.y + diffPos.y < rect.top		||	// jest za górn¹ œcian¹ lub
		center.x - diffPos.x > rect.right	||	// jest za praw¹ œcian¹ lub
		center.y - diffPos.y > rect.bottom		// jest za doln¹ œcian¹
		)
	{
		return false;	// nie rysuj go
	}
	// jak widac to rysuj, dozo~
	return true;
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


void GameObject::SetSpeed(float const speed)
{
	this->speed = speed;
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
