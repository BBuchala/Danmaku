#include "Bullet.h"

// po to by pociski by³y na œrodku
Bullet::Bullet(float const & x, float const & y, float const & angular_speed) : GameObject(x, y)
{
	this->theta = this->speed = D3DXToRadian(angular_speed);
};


Bullet::~Bullet()
{
};


void Bullet::setCircleTrajectory( float const & x0, float const & y0 )
{
	this->setCenterPoint( x0, y0 );
	// obliczenie promienia
	this->radius1 = this->radius2 =
		sqrt( pow( this->position.x - x0, 2) + pow( this->position.y - y0, 2) );
};


void Bullet::setCenterPoint( float const & x0, float const & y0 )
{
	this->center.x = x0;
	this->center.y = y0;
};


void Bullet::setElipseTrajectory( float const & x0, float const & y0, float const & a, float const & b )
{
	this->setCenterPoint( x0, y0 );
	this->radius1 = a;
	this->radius2 = b;
};



void Bullet::Update(float const & time)
{
	GameObject::Update(time);
	this->theta += this->speed * time;

	this->position.x = this->center.x + this->radius1 * cos(this->theta) - this->sprite->GetWidth() / 2;
	this->position.y = this->center.y + this->radius2 * sin(this->theta) - this->sprite->GetHeight() / 2;

	this->sprite->SetCenterPoint( this->position );

};

bool Bullet::Initialize(LPDIRECT3DDEVICE9 device, char const * file, int const & width, int const & height)
{
	return GameObject::Initialize(device, file, width, height);
};



void Bullet::scaleRadius( float const & scale )
{
	this->radius1 *= scale;
	this->radius2 *= scale;
};