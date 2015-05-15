#include "Bomb.h"

Bomb::Bomb(D3DXVECTOR2 const & position, float const value, float const speed, std::string fileName)
	: GameObject( position.x, position.y, speed ), maxTime(3.0f)
{
}

Bomb::Bomb( Bomb const & bomb) : GameObject(bomb), maxTime(3.0f)
{
	//this->maxTime = bomb->maxTime;
};

Bomb::~Bomb()
{
};

bool Bomb::Initialize(LPDIRECT3DDEVICE9 device)
{
	return this->sprite->Initialize( device, Sprite::GetFilePath( "master_spark","png"));
}

void Bomb::Update(float const time)
{
	//this->position = 

	this->elapsedTime += time;


	GameObject::Update(time);
};