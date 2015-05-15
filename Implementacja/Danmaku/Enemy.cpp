#include "Enemy.h"

typedef std::vector<Bonus*>			BonusQue;

// ----- Konstruktor -----------------------------------------------------------------------------
Enemy::Enemy( D3DXVECTOR2 const & position, USHORT const life, float const speed, float const acc )
	: GameObject(position.x, position.y, speed, acc), life_(life), isShooting_(true),
	traj_(nullptr), distance_(0.0f), isPatternGlued_(false), isPatternDying_(false), _actTime(0.0f)
{
};


Enemy::Enemy(Enemy const & enemy) : GameObject(enemy.position.x, enemy.position.y, enemy.speed, enemy.acceleration),
	life_(enemy.life_), isShooting_(enemy.isShooting_), traj_(enemy.traj_), distance_(enemy.distance_),
	isPatternGlued_(enemy.isPatternGlued_), isPatternDying_(enemy.isPatternDying_)
{
	this->_bonusMap = enemy._bonusMap;
	/*for (PatternMap::const_iterator it = _pattern.begin(); it != _pattern.end(); ++it)
	{
		this->_pattern[(*it).first] = n(*it).second;
	}*/
	this->traj_  = enemy.traj_;
};

// ----- Initialize Pattern -----------------------------------------------------------------------
bool Enemy::InitializePatterns(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position)
{
	for (PatternMap::const_iterator it = _pattern.begin(); it != _pattern.end(); ++it)
	{
		(*it).second->Initialize(device, this->GetCenterPoint());
	}
	return true;
};


// ----- Update ----------------------------------------------------------------------------------
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
			if (isPatternGlued_)
				(*it).second->SetPosition(this->GetCenterPoint());
			(*it).second->Activate(_actTime, this->GetCenterPoint());
			(*it).second->Update(time, this->GetCenterPoint());
		}
	}
};


// ----- Add Pattern -----------------------------------------------------------------------------
void Enemy::AddPattern(Pattern const patId, std::string const & patternId, float const par1, float const par2,
					   float const bulletNumber, float const interval, float const actTime )
{
	switch(patId)
	{
	case Pattern::LINE:
		_pattern.insert(PatternPair(patternId, EPatternPtr(new EnemyPatternLine(par1, bulletNumber, actTime))));
		break;
	case Pattern::ELLIPSE:
		_pattern.insert(PatternPair(patternId, EPatternPtr(new EnemyPatternEllipse(par1, par2, bulletNumber, actTime))));
		break;
	default:
		break;
	}
};

// ----- Draw ------------------------------------------------------------------------------------
void Enemy::Draw(RECT const & rect)
{
	// najpierw rysujemy pociski, potem samego wroga
	for (PatternMap::const_iterator it = _pattern.begin(); it != _pattern.end(); ++it)
	{
		(*it).second->Draw(rect);
	}
	GameObject::Draw(rect);
};


// ----- Take Damage -----------------------------------------------------------------------------
void Enemy::TakeDamage( USHORT const damage )
{
	if (life_ - damage < 0  )
		life_ = 0;
	else
		life_ -= damage;
};


// ----- Create Bonus ----------------------------------------------------------------------------
BonusQue * Enemy::CreateBonus(LPDIRECT3DDEVICE9 device)
{
	BonusQue * bonus = new BonusQue();
	for (BonusMap::const_iterator it = _bonusMap.begin(); it != _bonusMap.end(); ++it)
	{
		if ((*it).second.first != Bonuses::NONE)
		{
			Bonus * newBonus = BonusFactory::Instance().CreateBonus((*it).second.first,
				D3DXVECTOR2(GetCenterPoint().x - 30 + rand() % 60, GetCenterPoint().y - 30 + rand() % 60), (*it).second.second, 200.0f);
			newBonus->Initialize( device );
			newBonus->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::FULL_LENGTH );
			bonus->push_back(newBonus);
		}
	}
	return bonus;
};


// ----- Get Bonus -------------------------------------------------------------------------------
BonusQue * Enemy::GetBonus(LPDIRECT3DDEVICE9 device)
{
	return CreateBonus(device);
};


// ----- Set Is Shooting --------------------------------------------------------------------------
void Enemy::SetIsShooting(bool const isShooting)
{
	isShooting_ = isShooting;
};


// ----- Set Trajectory ---------------------------------------------------------------------------
void Enemy::SetTrajectory( Road const trajectory, D3DXVECTOR2 const & position, float const a, float const b )
{
	traj_ = TrajectoryPtr( TrajectoryFactory::Instance().CreateTrajectory(trajectory, position, a, b ) );
};

// ----- Set Pattern Dying ------------------------------------------------------------------------
void Enemy::SetPatternDying(bool const isPatternDying)
{
	isPatternDying_ = isPatternDying;
};

// ----- Set Bonus --------------------------------------------------------------------------------
void Enemy::SetBonus(Bonuses const bonus, float const value)
{
	_bonusMap.insert(BonusMap::value_type(_bonusMap.size(), BonusPair(bonus, value)));
};

// ----- Set Distance -----------------------------------------------------------------------------
void Enemy::SetDistance(float const distance)
{
	distance_ = distance;
};

