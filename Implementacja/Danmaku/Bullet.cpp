#include "Bullet.h"

// po to by pociski by³y na œrodku
Bullet::Bullet(float const & x, float const & y, float const & angular_speed, float const & a,
			   float const & b) : GameObject(x, y)
{
	this->center.x = a;
	this->center.y = b;
	this->center.z = 0;

	this->radius = sqrt( pow( x - a, 2) + pow( y - b, 2) );
	this->theta = this->speed = D3DXToRadian(angular_speed);
};


Bullet::~Bullet()
{
};


void Bullet::Update(float const & time)
{
	this->theta += this->speed * time;
	this->position.x = this->center.x + this->radius * cos(this->theta);
	this->position.y = this->center.y + this->radius * sin(this->theta);
};

bool Bullet::Initialize(LPDIRECT3DDEVICE9 device, char const * file, int const & width, int const & height)
{
	GameObject::Initialize(device, file, width, height);
	this->position.x -= this->sprite->GetWidth() / 2;
	this->position.y -= this->sprite->GetHeight() / 2;
	this->center.x -= this->sprite->GetWidth() / 2;
	this->center.y -= this->sprite->GetHeight() / 2;

	return true;
};