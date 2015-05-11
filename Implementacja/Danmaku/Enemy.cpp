#include "Enemy.h"

// ----- Konstruktor -----------------------------------------------------------------------------
Enemy::Enemy( D3DXVECTOR2 const & position, USHORT const life, float const speed, float const acc )
	: GameObject(position.x, position.y, speed, acc), life_(life), isShooting_(false), bonus_(nullptr),
	traj_(nullptr), distance_(0.0f), isPatternGlued_(true), isPatternDying_(false)
{
};

// ----- Initialize Pattern -----------------------------------------------------------------------
bool Enemy::InitializePattern(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position)
{
	pattern_->Initialize(device, this->GetCenterPoint());
	return true;
};


// ----- Update ----------------------------------------------------------------------------------
void Enemy::Update( float const time )
{
	GameObject::Update(time);
	distance_ += this->speed * time;
	this->position = traj_->GetPosition(distance_);
	if (isShooting_ && pattern_ != nullptr)
	{
		if (isPatternGlued_)
			pattern_->SetPosition(this->GetCenterPoint());
		pattern_->Update(time);
	}
};


// ----- Draw ------------------------------------------------------------------------------------
void Enemy::Draw(RECT const & rect)
{
	if (pattern_ != nullptr)
		pattern_->Draw(rect);
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
void Enemy::CreateBonus(LPDIRECT3DDEVICE9 device)
{
	bonus_ = new PowerBonus( D3DXVECTOR2(this->GetCenterPoint()), 200.0f );
	bonus_->Initialize( device );
	bonus_->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::FULL_LENGTH );
};


// ----- Get Bonus -------------------------------------------------------------------------------
Bonus & Enemy::GetBonus(LPDIRECT3DDEVICE9 device)
{
	CreateBonus(device);
	return *bonus_;
};


// ----- Set Is Shooting --------------------------------------------------------------------------
void Enemy::SetIsShooting(bool const isShooting)
{
	isShooting_ = isShooting;
};


// ----- Set Pattern -----------------------------------------------------------------------------
void Enemy::SetPattern( Pattern const patId )
{
	if (pattern_)
		pattern_.release();

	switch(patId)
	{
	case Pattern::A:
		this->pattern_ = EPatternPtr(new EnemyPattern01());
		break;
	case Pattern::S:
		this->pattern_ = EPatternPtr(new EnemyPattern02());
		break;
	case Pattern::NONE:
		this->pattern_ = nullptr;
		break;
	}
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
