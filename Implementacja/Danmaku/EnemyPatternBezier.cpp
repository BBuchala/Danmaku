#include "EnemyPatternBezier.h"

/// <summary>
/// Tworzy now� instacj� klasy <see cref="EnemyPatternBezier"/>.
/// </summary>
/// <param name="traj">Trajektoria Beziera dla wzoru.</param>
/// <param name="number">Liczba pocisk�w.</param>
/// <param name="actTime">Czas aktywacji.</param>
EnemyPatternBezier::EnemyPatternBezier(TrajectoryBezier * const traj, int number, float actTime) : EnemyPattern(actTime),
			_number(number)
{
	this->_traj = TrajectoryPtr(traj);
};

/// <summary>
/// Niszczy instancj� klasy <see cref="EnemyPatternBezier"/>.
/// </summary>
EnemyPatternBezier::~EnemyPatternBezier()
{
	_traj.reset();
};

/// <summary>
/// Utworzenie pocisk�w i ustalenie ich pocz�tkowych paarmetr�w.
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
/// <param name="time">Pr�bka czasu.</param>
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
/// Rozpocz�cie poruszania pocisk�w.
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
