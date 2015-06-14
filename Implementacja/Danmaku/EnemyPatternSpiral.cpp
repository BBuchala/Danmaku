#include "EnemyPatternSpiral.h"

/// <summary>
/// Tworzy now¹ instacjê klasy <see cref="EnemyPatternSpiral"/>.
/// </summary>
/// <param name="radiusA">Obrót spirali.</param>
/// <param name="radiusB">Odleg³oœæ miêdzy kolejnymi obrotami spirali.</param>
/// <param name="number">Liczba pocisków.</param>
/// <param name="activationTime">Czas aktywacji.</param>
EnemyPatternSpiral::EnemyPatternSpiral(float const radiusA, float const radiusB, float const number,
										 float const activationTime)
										 : EPattern(activationTime)
{
	_radiusA = radiusA;
	_radiusB = radiusB;
	_number = number;
};

/// <summary>
/// Niszczy instancjê klasy <see cref="EnemyPatternSpiral"/>.
/// </summary>
EnemyPatternSpiral::~EnemyPatternSpiral()
{
	_traj.reset();
}

/// <summary>
/// Utworzenie pocisków i ustalenie ich pocz¹tkowych paarmetrów.
/// </summary>
/// <returns></returns>
void EnemyPatternSpiral::CreateBullets()
{
	for (int i = 0; i < _number; i++)
	{
		AddBullet();
		_bullet[i]->SetDistance(static_cast<float>(i));
	}
};

/// <summary>
/// Aktualizuje stan.
/// </summary>
/// <param name="time">Próbka czasu.</param>
void EnemyPatternSpiral::Update(float const time)
{
	if (_activated)
	{
		// Przekszta³cenia torów pocisków
		this->Scale();
		this->Rotate();
		// Procedurta nadrzêdna
		EPattern::Update(time);
	}
};

/// <summary>
/// Dodanie nowego pocisku.
/// </summary>
void EnemyPatternSpiral::AddBullet()
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
void EnemyPatternSpiral::Scale()
{
	_traj->Scale(_scaleStep);
};

/// <summary>
/// Obrócenie wzoru o krok.
/// </summary>
void EnemyPatternSpiral::Rotate()
{
	_traj->Rotate(_rotateStep);
};

/// <summary>
/// Rozpoczêcie poruszania pocisków.
/// </summary>
void EnemyPatternSpiral::StartBullets()
{
	_traj->SetStartPoint(*_position);
}


/// <summary>
/// Ustawienie skali wzoru.
/// </summary>
/// <param name="scale">Skala.</param>
void EnemyPatternSpiral::SetScale(float const scale)
{
	_traj->Scale(scale);
}


/// <summary>
/// ustawienie obrotu wzoru.
/// </summary>
/// <param name="rotate">Obrót.</param>
void EnemyPatternSpiral::SetRotation(float const rotate)
{
	_traj->Rotate(rotate);
}

