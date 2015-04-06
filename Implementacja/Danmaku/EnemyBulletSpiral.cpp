#include "EnemyBulletSpiral.h"

EnemyBulletSpiral::EnemyBulletSpiral(float const & x, float const & y, float const & angular_speed)
	: EnemyBullet( x, y )
{
	this->center.x = x;
	this->center.y = y;
	this->theta = this->speed = D3DXToRadian(angular_speed);
};


EnemyBulletSpiral::~EnemyBulletSpiral()
{

};


void EnemyBulletSpiral::SetRadius( float const & rad )
{
	this->SetRadius( rad, rad );
};


void EnemyBulletSpiral::SetRadius( float const & r1, float const & r2 )
{
	this->radius1 = r1;
	this->radius2 = r2;
};

void EnemyBulletSpiral::Update(float const & time)
{
	GameObject::Update(time);
	this->theta += this->speed * time;

	D3DXVECTOR3 dv (
		this->radius1 * this->theta * cos(this->theta) - this->sprite->GetWidth() / 2 + 400, 
		this->radius2 * this->theta * sin(this->theta) - this->sprite->GetHeight() / 2 + 300, 
		0
	);
	this->SetPosition( dv );
};