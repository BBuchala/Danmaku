#include "Bonus.h"

Bonus::Bonus(D3DXVECTOR2 const & position, float const value, float const speed, std::string fileName)
	: GameObject( position.x, position.y, speed ), value(value), distance(0.0f), fileName(fileName)
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


bool Bonus::Initialize(LPDIRECT3DDEVICE9 device)
{
	return this->sprite->Initialize( device, fileName );	// Inicjalizuje sprite obrazkiem zgodnym z typem obiektu (nazwa podana w konstruktorze)
}

void Bonus::Update(float const time)
{
	this->distance += this->speed * time;
	this->position = this->GetTrajectory()->GetPosition( distance );
	this->position.x -= this->sprite->GetWidth() / 2;
	this->position.y -= this->sprite->GetHeight() / 2;

	GameObject::Update(time);
};

