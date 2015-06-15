#include "EnemyPatternLine.h"

/// <summary>
/// Tworzy now� instacj� klasy <see cref="EnemyPatternLine"/>.
/// </summary>
/// <param name="radiusA">Pierwsza p�o�.</param>
/// <param name="radiusB">Druga p�o�.</param>
/// <param name="number">Liczba pocisk�w.</param>
/// <param name="activationTime">Czas aktywacji.</param>
EnemyPatternLine::EnemyPatternLine(float const angle, float const length, float const number, float const activationTime)
								   : EnemyPattern(activationTime)
{
	_angle = angle;
	_number = number;
	_traj = std::shared_ptr<Trajectory>(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, D3DXVECTOR2(0.0f, 0.0f), D3DXToRadian(_angle) ) );
};

/// <summary>
/// Niszczy instancj� klasy <see cref="EnemyPatternLine"/>.
/// </summary>
EnemyPatternLine::~EnemyPatternLine()
{
	_traj.reset();
}

/// <summary>
/// Utworzenie pocisk�w i ustalenie ich pocz�tkowych paarmetr�w.
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
/// <param name="time">Pr�bka czasu.</param>
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
/// Rozpocz�cie poruszania pocisk�w.
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
