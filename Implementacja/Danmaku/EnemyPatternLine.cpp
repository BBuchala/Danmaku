#include "EnemyPatternLine.h"

/// <summary>
/// Tworzy now¹ instacjê klasy <see cref="EnemyPatternLine"/>.
/// </summary>
/// <param name="radiusA">Pierwsza pó³oœ.</param>
/// <param name="radiusB">Druga pó³oœ.</param>
/// <param name="number">Liczba pocisków.</param>
/// <param name="activationTime">Czas aktywacji.</param>
EnemyPatternLine::EnemyPatternLine(float const angle, float const length, float const number, float const activationTime)
								   : EnemyPattern(activationTime)
{
	_angle = angle;
	_number = number;
	_traj = std::shared_ptr<Trajectory>(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, D3DXVECTOR2(0.0f, 0.0f), D3DXToRadian(_angle) ) );
};

/// <summary>
/// Niszczy instancjê klasy <see cref="EnemyPatternLine"/>.
/// </summary>
EnemyPatternLine::~EnemyPatternLine()
{
	_traj.reset();
}

/// <summary>
/// Utworzenie pocisków i ustalenie ich pocz¹tkowych paarmetrów.
/// </summary>
/// <returns></returns>
void EnemyPatternLine::CreateBullets()
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
void EnemyPatternLine::Update(float const time)
{
	if (_activated)
	{
		EnemyPattern::Update(time);
	}
};

/// <summary>
/// Dodanie nowego pocisku.
/// </summary>
void EnemyPatternLine::AddBullet()
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
void EnemyPatternLine::StartBullets()
{
	for (EBulletQue::const_iterator it = _bullet.begin(); it != _bullet.end(); ++it)
	{
		(*it)->GetTrajectory()->SetStartPoint(*_position);
	}
}

/// <summary>
/// Skopiowanie instancji wzoru.
/// </summary>
/// <returns></returns>
EnemyPattern * EnemyPatternLine::Clone() const
{
	return new EnemyPatternLine(*this);
}
