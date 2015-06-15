#include "EnemyPatternBezier.h"

/// <summary>
/// Tworzy now¹ instacjê klasy <see cref="EnemyPatternBezier"/>.
/// </summary>
/// <param name="traj">Trajektoria Beziera dla wzoru.</param>
/// <param name="number">Liczba pocisków.</param>
/// <param name="actTime">Czas aktywacji.</param>
EnemyPatternBezier::EnemyPatternBezier(TrajectoryBezier * const traj, int number, float actTime) : EnemyPattern(actTime),
			_number(number)
{
	this->_traj = TrajectoryPtr(traj);
};

/// <summary>
/// Niszczy instancjê klasy <see cref="EnemyPatternBezier"/>.
/// </summary>
EnemyPatternBezier::~EnemyPatternBezier()
{
	_traj.reset();
};

/// <summary>
/// Utworzenie pocisków i ustalenie ich pocz¹tkowych paarmetrów.
/// </summary>
/// <returns></returns>
void EnemyPatternBezier::CreateBullets()
{
	for (int i = 0; i < _number; i++)
	{
		AddBullet();
		_bullet[i]->SetSpeed(_bulletSpeed + i * 20.0f);
	}
};

/// <summary>
/// Aktualizuje stan.
/// </summary>
/// <param name="time">Próbka czasu.</param>
void EnemyPatternBezier::Update(float const time)
{
	if (_activated)
	{
		EnemyPattern::Update(time);
	}
};

/// <summary>
/// Dodanie nowego pocisku.
/// </summary>
void EnemyPatternBezier::AddBullet()
{
	EnemyBullet * newBullet = new EnemyBullet(_bulletSpeed, _bulletAcc);
	newBullet->InitializeSprite( _bulletSprite );
	newBullet->InitializeHitbox( _hitboxShape, _hitboxSize );
	newBullet->SetTrajectory( _traj );
	_bullet.push_back(newBullet);
};

/// <summary>
/// Rozpoczêcie poruszania pocisków.
/// </summary>
void EnemyPatternBezier::StartBullets()
{
	_traj->SetStartPoint(*_position);
};

/// <summary>
/// Skopiowanie instancji wzoru.
/// </summary>
/// <returns></returns>
EnemyPattern * EnemyPatternBezier::Clone() const
{
	return new EnemyPatternBezier(*this);
};
