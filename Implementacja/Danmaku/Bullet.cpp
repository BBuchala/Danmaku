#include "Bullet.h"

/// <summary>
/// Tworzy now¹ instacjê klasy <see cref="Bullet"/>.
/// </summary>
/// <param name="position">Pozycja.</param>
/// <param name="speed">Szybkoœæ.</param>
/// <param name="acc">Przyspieszenie.</param>
Bullet::Bullet( D3DXVECTOR2 const & position, float const speed, float const acc )
	: GameObject( position, speed, acc ), distance(0.0f)
{
};

/// <summary>
/// Tworzy now¹ instacjê klasy <see cref="Bullet"/>. class.
/// </summary>
/// <param name="speed">Szybkoœæ.</param>
/// <param name="acc">Przyspieszenie.</param>
Bullet::Bullet( float const speed, float const acc ) : GameObject( D3DXVECTOR2(0.0f, 0.0f), speed, acc ), distance(0.0f)
{
};

/// <summary>
/// Tworzy kopiê instacji klasy <see cref="Bullet"/>.
/// </summary>
Bullet::Bullet( Bullet const & bullet ) : GameObject(bullet), distance(bullet.distance)
{
};

/// <summary>
/// Niszczy instancjê klasy <see cref="Bullet"/>.
/// </summary>
Bullet::~Bullet()
{
};

/// <summary>
/// Aktualizuje stan pocisku.
/// </summary>
/// <param name="time">Próbka czasu.</param>
void Bullet::Update(float const time)
{
	this->distance += this->speed * time;
	this->position = this->GetTrajectory()->GetPosition( distance );
	this->position.x -= this->sprite->GetWidth() / 2;
	this->position.y -= this->sprite->GetHeight() / 2;
	GameObject::Update(time);
};


/// <summary>
/// Ustawia trajektoriê
/// </summary>
/// <param name="trajectory">Trajektoria.</param>
/// <param name="position">Pozyacja.</param>
/// <param name="a">Pierwszy parametr.</param>
/// <param name="b">Drugi parametr.</param>
void Bullet::SetTrajectory( Road const trajectory, D3DXVECTOR2 const & position, float const a, float const b )
{
	this->trajectory = TrajectoryPtr( TrajectoryFactory::Instance().CreateTrajectory(trajectory, position, a, b ) );
};

/// <summary>
/// Ustawia trajektoriê
/// </summary>
/// <param name="trajectory">Trajektoria.</param>
void Bullet::SetTrajectory( Trajectory * const trajectory )
{
	this->trajectory = TrajectoryPtr( trajectory );
};


/// <summary>
/// Ustawia trajektoriê
/// </summary>
/// <param name="trajectory">Trajektoria.</param>
void Bullet::SetTrajectory( TrajectoryPtr const & trajectory )
{
	this->trajectory = TrajectoryPtr(trajectory);
};


/// <summary>
/// Ustawia przebyty dystans
/// </summary>
/// <param name="distance">Dystans.</param>
void Bullet::SetDistance( float const distance )
{
	this->distance = distance;
};
