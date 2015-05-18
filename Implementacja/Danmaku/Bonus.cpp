#include "Bonus.h"

Bonus::Bonus(D3DXVECTOR2 const & position, float const value, float const speed)
	: GameObject( position, speed ), value(value), distance(0.0f), _vacuumed(false)
{
	this->trajectory = TrajectoryPtr( TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, position, D3DXToRadian(-90) ) );
};

Bonus::Bonus( Bonus const & bonus) 
	: GameObject(bonus), distance(bonus.distance), fileName(bonus.fileName), trajectory(bonus.trajectory)
{
};

Bonus::~Bonus()
{
};


void Bonus::SetSprite(SpritePtr sprite)
{
	this->sprite = sprite;
}

void Bonus::Update(float const time)
{
	this->distance += this->speed * time;
	this->position = this->GetTrajectory()->GetPosition( distance );
	this->position.x -= this->sprite->GetWidth() / 2;
	this->position.y -= this->sprite->GetHeight() / 2;

	GameObject::Update(time);
};

