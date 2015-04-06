#include "EnemyBulletElipse.h"

// po to by pociski by³y na œrodku
EnemyBulletElipse::EnemyBulletElipse(float const & x, float const & y, float const & angular_speed) : EnemyBullet(x, y)
{
	this->theta = this->speed = D3DXToRadian(angular_speed);
};


EnemyBulletElipse::~EnemyBulletElipse()
{
};


void EnemyBulletElipse::setCircleTrajectory( float const & x0, float const & y0 )
{
	this->setCenterPoint( x0, y0 );
	// obliczenie promienia
	this->radius1 = this->radius2 =
		sqrt( pow( this->position.x - x0, 2) + pow( this->position.y - y0, 2) );
};


void EnemyBulletElipse::setCenterPoint( float const & x0, float const & y0 )
{
	this->center.x = x0;
	this->center.y = y0;
};


void EnemyBulletElipse::setElipseTrajectory( float const & x0, float const & y0, float const & a, float const & b )
{
	this->setCenterPoint( x0, y0 );
	this->radius1 = a;
	this->radius2 = b;
};



void EnemyBulletElipse::Update(float const & time)
{
	GameObject::Update(time);
	this->theta += this->speed * time;

	D3DXVECTOR3 dv (
		this->center.x + this->radius1 * cos(this->theta) - this->sprite->GetWidth() / 2, 
		this->center.y + this->radius2 * sin(this->theta) - this->sprite->GetHeight() / 2, 
		0
	);
	this->SetPosition( dv );
	this->SetCenterPoint();

};



void EnemyBulletElipse::scaleRadius( float const & scale )
{
	this->radius1 *= scale;
	this->radius2 *= scale;
};