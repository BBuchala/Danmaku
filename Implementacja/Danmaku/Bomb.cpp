#include "Bomb.h"

Bomb::Bomb(D3DXVECTOR2 const & position, float const speed): GameObject( position, speed ), maxTime(3.0f)
{
};

Bomb::Bomb( Bomb const & bomb) : GameObject(bomb), maxTime(3.0f)
{
};

Bomb::~Bomb()
{
};

void Bomb::Initialize(LPDIRECT3DDEVICE9 device)
{	
	SpritePtr sprite = SpritePtr(new Sprite(device, Sprite::GetFilePath( "master_spark", "png")));
	this->InitializeSprite(sprite);
	this->InitializeHitbox(Hitbox::Shape::ELLIPSE, Hitbox::Size::TWO_THIRDS_LENGTH);
	this->inUse = false;
	this->shift = D3DXVECTOR2(this->GetSprite()->GetWidth()/2,this->GetSprite()->GetHeight());
}

void Bomb::Update(float const time)
{
	/*if (inUse)
	{
		this->elapsedTime += time;
		if (elapsedTime < maxTime)
		{
			//this->SetPosition = 
			GameObject::Update( time );
		}
		else
			inUse = false;
	}*/
};

void Bomb::Update(float const time, D3DXVECTOR2 const & position)
{
	if (inUse)
	{
		this->elapsedTime += time;
		if (elapsedTime < maxTime)
		{
			this->SetPosition(position - shift);
			GameObject::Update( time );
		}
		else
			inUse = false;
	}
};

void Bomb::Launch()
{
	elapsedTime = 0;
	inUse = true;
};