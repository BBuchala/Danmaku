#include "EnemyBullet.h"

/// <summary>
/// Tworzy now� instacj� klasy <see cref="EnemyBullet"/>.
/// </summary>
/// <param name="position">Pozycja.</param>
/// <param name="speed">Szybko��.</param>
/// <param name="acc">Przyspieszenie.</param>
EnemyBullet::EnemyBullet( D3DXVECTOR2 const & position, float const speed ) : Bullet(position, speed), isGrazed(false)
{
};

/// <summary>
/// Tworzy now� instacj� klasy <see cref="EnemyBullet"/>. class.
/// </summary>
/// <param name="speed">Szybko��.</param>
/// <param name="acc">Przyspieszenie.</param>
EnemyBullet::EnemyBullet( float const speed, float const acc ) : Bullet(speed, acc), isGrazed(false)
{
};

/// <summary>
/// Tworzy kopi� instacji klasy <see cref="EnemyBullet"/>.
/// </summary>
/// <param name="bonus">Obiekt do skopiowania</param>
EnemyBullet::EnemyBullet(EnemyBullet const & other) : Bullet(other), isGrazed(other.isGrazed)
{
};

/// <summary>
/// Niszczy instancj� klasy <see cref="EnemyBullet"/>.
/// </summary>
EnemyBullet::~EnemyBullet()
{
};


/// <summary>
/// Ustawienie grezju
/// </summary>
/// <param name="isGrazed">Czy jest zgrezjowany.</param>
void EnemyBullet::SetGrazed( bool const isGrazed )
{
	this->isGrazed = isGrazed;
};