#include "EnemyPatternEllipse.h"

/// <summary>
/// Tworzy now� instacj� klasy <see cref="EnemyPatternEllipse"/>.
/// </summary>
/// <param name="radiusA">Pierwsza p�o�.</param>
/// <param name="radiusB">Druga p�o�.</param>
/// <param name="number">Liczba pocisk�w.</param>
/// <param name="activationTime">Czas aktywacji.</param>
EnemyPatternEllipse::EnemyPatternEllipse(float const radiusA, float const radiusB, float const number,
										 float const activationTime)
										 : EnemyPattern(activationTime)
{
	_radiusA = radiusA;
	_radiusB = radiusB;
	_number = number;
	_traj = std::shared_ptr<Trajectory>(TrajectoryFactory::Instance().CreateTrajectory( Road::ELIPSE, D3DXVECTOR2(0.0f, 0.0f), _radiusA, _radiusB ) );
};


/// <summary>
/// Tworzy kopi� instacji klasy <see cref="EnemyPatternEllipse"/>.
/// </summary>
/// <param name="other">Obiekt do skopiowania.</param>
EnemyPatternEllipse::EnemyPatternEllipse(EnemyPatternEllipse const & other) : EnemyPattern(other)
{
	_radiusA = other._radiusA;
	_radiusB = other._radiusB;
	_number = other._number;
	_traj = std::shared_ptr<Trajectory>(TrajectoryFactory::Instance().CreateTrajectory( Road::ELIPSE, D3DXVECTOR2(0.0f, 0.0f), _radiusA, _radiusB ) );
	this->SetPositionPtr(new D3DXVECTOR2(*other._position));
}

/// <summary>
/// Niszczy instancj� klasy <see cref="EnemyPatternEllipse"/>.
/// </summary>
EnemyPatternEllipse::~EnemyPatternEllipse()
{
	_traj.reset();
}

/// <summary>
/// Utworzenie pocisk�w i ustalenie ich pocz�tkowych paarmetr�w.
/// </summary>
/// <returns></returns>
void EnemyPatternEllipse::CreateBullets()
{
	for (int i = 0; i < _number; i++)
	{
		AddBullet();
		_bullet[i]->SetDistance(D3DXToRadian(i * (360.0f / _number)));
	}
};

/// <summary>
/// Aktualizuje stan.
/// </summary>
/// <param name="time">Pr�bka czasu.</param>
void EnemyPatternEllipse::Update(float const time)
{
	if (_activated)
	{
		// Przekszta�cenia tor�w pocisk�w
		this->Scale();
		this->Rotate();
		// Procedurta nadrz�dna
		EnemyPattern::Update(time);
	}
};

/// <summary>
/// Dodanie nowego pocisku.
/// </summary>
void EnemyPatternEllipse::AddBullet()
{
	EnemyBullet * newBullet = new EnemyBullet(_bulletSpeed, _bulletAcc);
	newBullet->InitializeSprite( _bulletSprite );
	newBullet->InitializeHitbox( _hitboxShape, _hitboxSize );
	newBullet->SetTrajectory( _traj );
	_bullet.push_back(newBullet);
};

/// <summary>
/// Zeskalowanie wzoru o krok.
/// </summary>
void EnemyPatternEllipse::Scale()
{
	_traj->Scale(_scaleStep);
};


/// <summary>
/// Obr�cenie wzoru o krok.
/// </summary>
void EnemyPatternEllipse::Rotate()
{
	_traj->Rotate(_rotateStep);
};


/// <summary>
/// Obr�cenie wzoru o wybrany k�t.
/// </summary>
/// <param name="theta">K�t.</param>
void EnemyPatternEllipse::Rotate(float const theta)
{
	_traj->Rotate(theta);
};

/// <summary>
/// Rozpocz�cie poruszania pocisk�w.
/// </summary>
void EnemyPatternEllipse::StartBullets()
{
	_traj->SetCenterPoint(*_position);
};

/// <summary>
/// Skopiowanie instancji wzoru.
/// </summary>
/// <returns></returns>
EnemyPattern * EnemyPatternEllipse::Clone() const
{
	return new EnemyPatternEllipse(*this);
};
