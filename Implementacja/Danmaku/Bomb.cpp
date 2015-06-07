#include "Bomb.h"

Bomb::Bomb(D3DXVECTOR2 const & position, float const speed) : GameObject(position, speed), maxTime(3.0f), damage(static_cast<unsigned short>(30.0))
{
};

Bomb::Bomb(Bomb const & bomb) : GameObject(bomb), maxTime(3.0f), damage(static_cast<unsigned short>(30.0))
{
};

Bomb::~Bomb()
{
};

void Bomb::Initialize(LPDIRECT3DDEVICE9 device)
{	
	SpritePtr sprite = SpritePtr(new Sprite(device, Sprite::GetFilePath( "master_spark", "png")));
	this->InitializeSprite(sprite);
	this->InitializeHitbox(Hitbox::Shape::ELLIPSE, Hitbox::Size::EXTENDED_LENGTH);
	this->inUse = false;
	this->shift = D3DXVECTOR2((float)(this->GetSprite()->GetWidth()/2),(float)(this->GetSprite()->GetHeight()));
}

void Bomb::Update(float const time)
{
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