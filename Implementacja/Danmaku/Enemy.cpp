#include "Enemy.h"

typedef std::vector<Bonus*>			BonusQue;

// ----- Konstruktor -----------------------------------------------------------------------------
/// <summary>
/// Tworzy now¹ instacjê klasy <see cref="Enemy"/>.
/// </summary>
/// <param name="position">Pozycja.</param>
/// <param name="life">¯ycie.</param>
/// <param name="speed">Szybkoœæ.</param>
/// <param name="acc">Przyspieszenie.</param>
Enemy::Enemy( D3DXVECTOR2 const & position, USHORT const life, float const speed, float const acc )
	: GameObject(position, speed, acc), life_(life), isShooting_(true),
	traj_(nullptr), distance_(0.0f), isPatternGlued_(false), _actTime(0.0f)
{
};

/// <summary>
/// Tworzy kopiê instacji klasy <see cref="Enemy"/>.
/// </summary>
/// <param name="bonus">Obiekt do skopiowania</param>
Enemy::Enemy(Enemy const & enemy) : GameObject(enemy.position, enemy.speed, enemy.acceleration),
	life_(enemy.life_), isShooting_(enemy.isShooting_), traj_(enemy.traj_), distance_(enemy.distance_),
	isPatternGlued_(enemy.isPatternGlued_)
{
	this->_bonusMap = enemy._bonusMap;
	this->traj_  = enemy.traj_;
};

/// <summary>
/// Niszczy instancjê klasy <see cref="Enemy"/>.
/// </summary>
Enemy::~Enemy()
{
}

/// <summary>
/// Inicjalizuje wzory pocisków
/// </summary>
/// <param name="position">The position.</param>
/// <returns></returns>
bool Enemy::InitializePatterns()
{
	for (PatternMap::const_iterator it = _pattern.begin(); it != _pattern.end(); ++it)
	{
		(*it).second->Initialize(this->GetCenterPoint());
	}
	return true;
};


/// <summary>
/// Aktualizuje stan.
/// </summary>
/// <param name="time">Próbka czasu.</param>
void Enemy::Update( float const time )
{
	GameObject::Update(time);
	distance_ += this->speed * time;
	_actTime += time;
	this->position = traj_->GetPosition(distance_);
	if (isShooting_)
	{
		for (PatternMap::const_iterator it = _pattern.begin(); it != _pattern.end(); ++it)
		{
			(*it).second->Activate(_actTime, this->GetCenterPoint());
		}
	}
};


/// <summary>
/// Dodaje wzór.
/// </summary>
/// <param name="patternId">The pattern identifier.</param>
/// <param name="epattern">The epattern.</param>
void Enemy::AddPattern(std::string const & patternId, EPattern * epattern )
{
	_pattern.insert(PatternPair(patternId, EPatternPtr(epattern)));
};

/// <summary>
/// Narysowanie wroga
/// </summary>
/// <param name="rect">Protok¹t w którym sprajt mo¿e byæ rysowany.</param>
void Enemy::Draw(RECT const & rect)
{
	GameObject::Draw(rect);
};


/// <summary>
/// Otrzymuje obra¿enia i odejmuje ich wartoœæ od punktów ¿ycia.
/// </summary>
/// <param name="damage">Obra¿enia.</param>
void Enemy::TakeDamage( USHORT const damage )
{
	if (life_ - damage < 0  )
		life_ = 0;
	else
		life_ -= damage;
};


/// <summary>
/// Tworzy bonus jaki wypadnie po zabiciu wroga.
/// </summary>
/// <param name="device">The device.</param>
/// <param name="spriteMap">Mapa sprajtów, w celu pobrania odpowiedniego rodzaju.</param>
/// <returns>Kolejkê utworzonych bonusów</returns>
BonusQue * Enemy::CreateBonus(LPDIRECT3DDEVICE9 device, BonusSpriteMap & spriteMap)
{
	BonusQue * bonus = new BonusQue();
	for (BonusMap::const_iterator it = _bonusMap.begin(); it != _bonusMap.end(); ++it)
	{
		if ((*it).second.first != BonusType::NONE)
		{
			Bonus * newBonus = BonusFactory::Instance().CreateBonus((*it).second.first,
				D3DXVECTOR2(GetCenterPoint().x - 30 + rand() % 60, GetCenterPoint().y - 30 + rand() % 60), (*it).second.second, 200.0f);
			newBonus->SetSprite( spriteMap[(*it).second.first] );
			newBonus->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::FULL_LENGTH );
			bonus->push_back(newBonus);
		}
	}
	return bonus;
};


/// <summary>
/// Zwraca utworzone bonusy.
/// </summary>
/// <param name="device">The device.</param>
/// <param name="spriteMap">Mapa sprajtów.</param>
/// <returns></returns>
BonusQue * Enemy::GetBonus(LPDIRECT3DDEVICE9 device, BonusSpriteMap const & spriteMap)
{
	return CreateBonus(device, const_cast<BonusSpriteMap&>(spriteMap));
};


/// <summary>
/// Ustawia czy boss aktualnie strzela.
/// </summary>
/// <param name="isShooting">Czy strzela.</param>
void Enemy::SetIsShooting(bool const isShooting)
{
	isShooting_ = isShooting;
};


/// <summary>
/// Ustawia trajektoriê
/// </summary>
/// <param name="trajectory">Trajektoria.</param>
/// <param name="position">Pozyacja.</param>
/// <param name="a">Pierwszy parametr.</param>
/// <param name="b">Drugi parametr.</param>
void Enemy::SetTrajectory( Road const trajectory, D3DXVECTOR2 const & position, float const a, float const b )
{
	traj_ = TrajectoryPtr( TrajectoryFactory::Instance().CreateTrajectory(trajectory, position, a, b ) );
};

/// <summary>
/// Ustawia trajektoriê
/// </summary>
/// <param name="trajectory">Trajektoria.</param>
void Enemy::SetTrajectory( TrajectoryManyPoints * trCurve )
{
	traj_ = TrajectoryPtr( trCurve );
};

/// <summary>
/// Tworzy nowy bonus, jaki wypadnie.
/// </summary>
/// <param name="bonus">Typ bonusu.</param>
/// <param name="value">Wartoœæ bonusu.</param>
void Enemy::SetBonus(BonusType const bonus, float const value)
{
	_bonusMap.insert(BonusMap::value_type(_bonusMap.size(), BonusPair(bonus, value)));
};

/// <summary>
/// Ustawia przebyty dystans
/// </summary>
/// <param name="distance">Dystans.</param>
void Enemy::SetDistance(float const distance)
{
	distance_ = distance;
};

