#include "Bullet.h"

Bullet::Bullet( D3DXVECTOR2 const & position, float const & speed ) : GameObject( position.x, position.y, speed )
{
	this->distance = 0.0f;
};

Bullet::Bullet( float const & speed ) : GameObject( 0.0f, 0.0f, speed )
{
	this->distance = 0.0f;
};


Bullet::~Bullet()
{
};


bool Bullet::Initialize(LPDIRECT3DDEVICE9 device, std::string const & file, int const & width, int const & height)
{
	if ( !GameObject::Initialize(device, file, width, height))
	{
		return false;
	}
	///// ZAK£ADAMY, ¯E WSZYSTKIE POCISKI S¥ PROPORCJONALNE
	this->hitbox = new Hitbox( this->GetCenterPoint(), (float) width );
	return true;
};


bool Bullet::Initialize(LPDIRECT3DDEVICE9 device, std::vector<std::string> const & fileVect,
						int const & width, int const & height)
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


void Bullet::SetTrajectory( Road const & trajectory, D3DXVECTOR2 const & position, float const & a, float const & b )
{
	this->trajectory = TrajectoryPtr( TrajectoryFactory::Instance().CreateTrajectory(trajectory, position, a, b ) );
};

void Bullet::SetTrajectory( Trajectory * trajectory )
{
	this->trajectory = TrajectoryPtr( trajectory );
};


void Bullet::SetTrajectory( TrajectoryPtr trajectory )
{
	this->trajectory = TrajectoryPtr(trajectory);
};


void Bullet::SetDistance( float const & distance )
{
	this->distance = distance;
};
