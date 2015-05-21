#include "Bullet.h"

Bullet::Bullet( D3DXVECTOR2 const & position, float const speed, float const acc )
	: GameObject( position, speed, acc ), distance(0.0f)
{
};

Bullet::Bullet( float const speed, float const acc ) : GameObject( D3DXVECTOR2(0.0f, 0.0f), speed, acc ), distance(0.0f)
{
};


Bullet::Bullet( Bullet const & bullet ) : GameObject(bullet), distance(bullet.distance)
{
};


Bullet::~Bullet()
{
};

void Bullet::Update(float const time)
{
	this->distance += this->speed * time;
	this->position = this->GetTrajectory()->GetPosition( distance );
	this->position.x -= this->sprite->GetWidth() / 2;
	this->position.y -= this->sprite->GetHeight() / 2;
	GameObject::Update(time);
};


void Bullet::SetTrajectory( Road const trajectory, D3DXVECTOR2 const & position, float const a, float const b )
{
	this->trajectory = TrajectoryPtr( TrajectoryFactory::Instance().CreateTrajectory(trajectory, position, a, b ) );
};

void Bullet::SetTrajectory( Trajectory * const trajectory )
{
	this->trajectory = TrajectoryPtr( trajectory );
};


void Bullet::SetTrajectory( TrajectoryPtr const & trajectory )
{
	this->trajectory = TrajectoryPtr(trajectory);
};


void Bullet::SetDistance( float const distance )
{
	this->distance = distance;
};
