#include "GameObject.h"

////////// KONSTRUKTOR ///////////////////////
GameObject::GameObject(float const & x, float const & y, float const & speed, float const & acc)
{
	this->SetPosition(x, y);
	this->speed = speed < 0 ? 0 : speed;
	this->acceleration = acc;
	this->hitbox = new Hitbox();
};


////////// DESTRUKTOR ///////////////////////
GameObject::~GameObject()
{
	if (sprite) delete sprite;
	if (hitbox) delete hitbox;
};


bool GameObject::Initialize(LPDIRECT3DDEVICE9 device, std::string const & file, int const & width, int const & height)
{
	if (!this->sprite)
	{
		this->sprite = new Sprite();
		if ( !this->sprite->Initialize(device, file, width, height) )
		{
			return false;
		}
	}
	return true;
};


bool GameObject::Initialize(LPDIRECT3DDEVICE9 device, std::vector<std::string> const & fileVect, int const & width, int const & height)
{
	if (!this->sprite)
	{
		this->sprite = new Sprite();
		if ( !this->sprite->Initialize(device, fileVect, width, height) )
		{
			return false;
		}
	}
	return true;
};


void GameObject::Draw()
{
	if (this->sprite)
	{

		this->sprite->Draw(this->position);

		if (this->hitbox->UseSprite())
		{
			this->hitbox->Draw( this->GetCenterPoint() );
		}
	}
};


void GameObject::Update(float const & time)
{
	this->speed += this->acceleration * time;
};


void GameObject::SetPosition(D3DXVECTOR2 const & v)
{
	this->position = v;
};


void GameObject::SetPosition(float const & x, float const & y)
{
	this->position.x = x;
	this->position.y = y;
};

void GameObject::SetAcceleration(float const & acc)
{
	this->acceleration = acc;
};


void GameObject::Rotate( float const & angle )
{
	this->sprite->Rotate( angle );
};



void GameObject::Scale( float const & scale )
{
	this->sprite->Scale( scale );
	this->hitbox->Scale( scale );
};



void GameObject::Translate( float const & dx, float const & dy )
{
	this->position.x += dx;
	this->position.y += dy;
};


void GameObject::Translate( D3DXVECTOR2 dv )
{
	this->position += dv;
};

