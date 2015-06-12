#include "PlayerBullet.h"

/// <summary>
/// Tworzy now¹ instacjê klasy <see cref="Bullet"/>.
/// </summary>
/// <param name="position">Pozycja.</param>
/// <param name="damage">Zadawane obra¿enia.</param>
/// <param name="speed">Szybkoœæ.</param>
PlayerBullet::PlayerBullet( D3DXVECTOR2 const & position,  const short unsigned damage, float const speed) : Bullet(position, speed), damage(damage)
{
};

/// <summary>
/// Tworzy now¹ instacjê klasy <see cref="Bullet"/>. class.
/// </summary>
/// <param name="speed">Szybkoœæ.</param>
/// <param name="damage">Zadawane obra¿enia.</param>
PlayerBullet::PlayerBullet( float const speed, const short unsigned damage ) : Bullet(speed), damage(damage)
{
};

/// <summary>
/// Niszczy instancjê klasy <see cref="PlayerBullet"/>.
/// </summary>
PlayerBullet::~PlayerBullet()
{
};

/// <summary>
/// Ustawia zadawane obra¿enia
/// </summary>
/// <param name="damage">Wartoœæ.</param>
void PlayerBullet::SetDamage( unsigned short const damage )
{
	this->damage = damage;
};