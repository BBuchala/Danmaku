#include "EnemyBulletSpiral.h"

EnemyBulletSpiral::EnemyBulletSpiral(float const & x, float const & y, float const & angular_speed)
	: EnemyBullet( x, y )
{
	this->center.x = x;
	this->center.y = y;
	this->speed = D3DXToRadian(angular_speed);
	this->theta = 0;
};


EnemyBulletSpiral::~EnemyBulletSpiral()
{
};


void EnemyBulletSpiral::SetParameters( float const & a, float const & b )
{
	this->a = a;
	this->b = b;
	rotation = 0;
};


//void EnemyBulletSpiral::SetRadius( float const & r1, float const & r2 )
//{
//	this->radius1 = r1;
//	this->radius2 = r2;
//};

void EnemyBulletSpiral::Update(float const & time)
{
	GameObject::Update(time);
	this->theta += this->speed * time;

	float radius = this->a + this->b * this->theta;

	D3DXVECTOR3 dv = Vector::Polar(radius, this->theta + rotation);
	dv.x = dv.x - this->sprite->GetWidth() / 2 + 400;
	dv.y = dv.y - this->sprite->GetHeight() / 2 + 300;

	//D3DXVECTOR3 dv (
	//	this->radius * this->theta * cos(this->theta) - this->sprite->GetWidth() / 2 + 400, 
	//	this->radius * this->theta * sin(this->theta) - this->sprite->GetHeight() / 2 + 300, 
	//	0
	//);
	this->SetPosition( dv );
};



void EnemyBulletSpiral::Rotate( float const & angle )
{
	this->rotation += angle;
};