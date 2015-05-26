#include "GameObject.h"

////////// KONSTRUKTOR ///////////////////////
GameObject::GameObject(D3DXVECTOR2 const & pos, float const speed, float const acc)
	: acceleration(acc), scale(1.0f), rotation(0.0f)
{
	///// Przydzielenie wartoœci sk³adowym
	this->SetPosition(pos);
	this->speed = speed;
	this->hitbox = NULL;
};


////////// DESTRUKTOR ///////////////////////
GameObject::~GameObject()
{
};


GameObject::GameObject( GameObject const & go ) : hitbox(new Hitbox(*go.hitbox))
{
	this->position = go.position;
	this->centerPoint = go.centerPoint;
	this->speed = go.speed;
	this->acceleration = go.acceleration;
	this->sprite = go.sprite;
	this->scale = go.scale;
	this->rotation = go.rotation;
};


void GameObject::SetCenterPoint()
{
	this->centerPoint = this->position + this->GetSprite()->GetCenterPoint();
};


bool GameObject::InitializeSprite(SpritePtr sprite)
{
	this->sprite = sprite;
	if ( !this->sprite)
	{
		return false;
	}
	this->SetCenterPoint();
	return true;
};


bool GameObject::InitializeHitbox( Hitbox::Shape const shape, Hitbox::Size const size )
{
	this->hitbox = HitboxPtr( new Hitbox( shape, size, sprite->GetWidth(), sprite->GetHeight(), this->centerPoint ) );
	return true;
};


void GameObject::Draw( RECT const & rect )
{
	if (this->sprite && IsObjectWithinBounds(rect))
	{
		this->sprite->Draw(this->GetPosition(), scale, rotation);
	}
};


bool GameObject::IsObjectWithinBounds( RECT const & rect )
{
	D3DXVECTOR2 center = this->GetCenterPoint();
	D3DXVECTOR2 diffPos = scale * (center - this->GetPosition());
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
	this->SetCenterPoint();
};


void GameObject::SetPosition(D3DXVECTOR2 const & v)
{
	this->position = v;
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
	this->rotation += angle;
};



void GameObject::Scale( float const scale )
{
	this->scale *= scale;
	this->hitbox->Scale( scale );
};



void GameObject::Translate( D3DXVECTOR2 const & dv )
{
	this->position += dv;
};

