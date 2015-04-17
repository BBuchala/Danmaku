#include "Bullet.h"

Bullet::Bullet( float const & speed ) : GameObject( 0.0f, 0.0f, speed )
{
	this->distance = 0.0f;
};


Bullet::~Bullet()
{
	if (trajectory) delete trajectory;
};


bool Bullet::Initialize(LPDIRECT3DDEVICE9 device, std::string const & file, int const & width, int const & height)
{
	return GameObject::Initialize(device, file, width, height);
};


bool Bullet::Initialize(LPDIRECT3DDEVICE9 device, std::vector<std::string> const & fileVect, int const & width, int const & height)
{
	return GameObject::Initialize(device, fileVect, width, height);
};


void Bullet::Update(float const & time)
{
	this->distance += this->speed * time;
	this->position = this->GetTrajectory()->GetPosition( distance );
	this->position.x -= this->sprite->GetWidth() / 2;
	this->position.y -= this->sprite->GetHeight() / 2;
	GameObject::Update(time);
};


bool Bullet::SetTrajectory( Road const & trajectory, D3DXVECTOR2 const & position, float const & a, float const & b )
{
	switch(trajectory)
	{
	case Road::LINE:
		this->trajectory = new TrajectoryLine( position, a );
		return true;
	case Road::ELIPSE:
		this->trajectory = new TrajectoryElipse( position, a, b );
		return true;
	case Road::SPIRAL:
		this->trajectory = new TrajectorySpiral( position, a, b );
		return true;
	default:
		return false;
	};
	return false;
};


void Bullet::SetDistance( float const & distance )
{
	this->distance = distance;
};
