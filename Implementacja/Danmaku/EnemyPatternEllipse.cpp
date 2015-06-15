#include "EnemyPatternEllipse.h"

/// <summary>
/// Tworzy now¹ instacjê klasy <see cref="EnemyPatternEllipse"/>.
/// </summary>
/// <param name="radiusA">Pierwsza pó³oœ.</param>
/// <param name="radiusB">Druga pó³oœ.</param>
/// <param name="number">Liczba pocisków.</param>
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
/// Tworzy kopiê instacji klasy <see cref="EnemyPatternEllipse"/>.
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
/// Niszczy instancjê klasy <see cref="EnemyPatternEllipse"/>.
/// </summary>
EnemyPatternEllipse::~EnemyPatternEllipse()
{
	_traj.reset();
}

/// <summary>
/// Utworzenie pocisków i ustalenie ich pocz¹tkowych paarmetrów.
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
/// <param name="time">Próbka czasu.</param>
void EnemyPatternEllipse::Update(float const time)
{
	if (_activated)
	{
		// Przekszta³cenia torów pocisków
		this->Scale();
		this->Rotate();
		// Procedurta nadrzêdna
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
/// Obrócenie wzoru o krok.
/// </summary>
void EnemyPatternEllipse::Rotate()
{
	_traj->Rotate(_rotateStep);
};


/// <summary>
/// Obrócenie wzoru o wybrany k¹t.
/// </summary>
/// <param name="theta">K¹t.</param>
void EnemyPatternEllipse::Rotate(float const theta)
{
	_traj->Rotate(theta);
};

/// <summary>
/// Rozpoczêcie poruszania pocisków.
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
