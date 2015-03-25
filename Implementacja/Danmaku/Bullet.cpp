#include "Bullet.h"

Bullet::Bullet(float const & x, float const & y, float const & speed, char const * file,
	   float const & x_circle, float const & y_circle, LPDIRECT3DDEVICE9 device) : x(x), y(y), speed(speed),
	   x_circle(x_circle), y_circle(y_circle)
{
	this->radius = sqrt( pow( x - x_circle, 2) + pow( y - y_circle, 2) );
	this->theta = D3DXToRadian(speed);
	this->sprite = new Sprite(x, y);
	this->sprite->Initialize(device, "img/Bullet01.png", 40, 40);
};


Bullet::~Bullet()
{
	if (this->sprite) delete sprite;
};


void Bullet::move()
{
	this->theta += D3DXToRadian(this->speed);
	this->x =  this->x_circle + this->radius * cos(this->theta);
	this->y =  this->y_circle + this->radius * sin(this->theta);

	this->sprite->setPosition( this->x, this->y );
};