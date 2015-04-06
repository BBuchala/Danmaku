#include "GameObject.h"

////////// KONSTRUKTOR ///////////////////////
GameObject::GameObject(float const & x, float const & y, float const & speed, float const & acc)
{
	this->SetPosition(x, y);
	this->speed = speed < 0 ? 0 : speed;
	this->acceleration = acc;
};


////////// DESTRUKTOR ///////////////////////
GameObject::~GameObject()
{
	if (this->sprite)
		delete this->sprite;
};


bool GameObject::Initialize(LPDIRECT3DDEVICE9 device, std::string const & file, int const & width, int const & height)
{
	if (!this->sprite)
	{
		this->sprite = new Sprite();
		if ( !this->sprite->Initialize(device, file, width, height, this->position) )
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
		if ( !this->sprite->Initialize(device, fileVect, width, height, this->position) )
		{
			return false;
		}
	}
	return true;
};


void GameObject::Draw()
{
	if (this->sprite)
		this->sprite->Draw(this->position);
};


void GameObject::Update(float const & time)
{
	this->speed += this->acceleration * time;
	this->SetCenterPoint();
};


void GameObject::SetPosition(D3DXVECTOR3 const & v)
{
	this->position = v;
};


void GameObject::SetPosition(float const & x, float const & y)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = 0;
};

void GameObject::SetAcceleration(float const & acc)
{
	this->acceleration = acc;
};


void GameObject::SetCenterPoint()
{
	this->sprite->SetCenterPoint( this->position );
};


void GameObject::Rotate( float const & angle )
{
	this->sprite->Rotate( angle );
};



void GameObject::Scale( float const & scale )
{
	this->sprite->Scale( scale );
};



void GameObject::Translate( float const & dx, float const & dy, float const & dz )
{
	this->position.x += dx;
	this->position.y += dy;
	this->position.z += dz;
};


void GameObject::Translate( D3DXVECTOR3 dv )
{
	this->position += dv;
};