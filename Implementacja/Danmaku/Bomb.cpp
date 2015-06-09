#include "Bomb.h"

Bomb::Bomb(D3DXVECTOR2 * const playerPosition, float const speed) : GameObject(position, speed), maxTime(3.0f), damage(30)
{
	_playerPosition = playerPosition;
};

Bomb::Bomb(Bomb const & bomb) : GameObject(bomb), maxTime(3.0f), damage(30)
{
};

Bomb::~Bomb()
{
};

void Bomb::Initialize(LPDIRECT3DDEVICE9 device)
{	
	SpritePtr sprite = SpritePtr(new Sprite(device, Sprite::GetFilePath( "master_spark")));
	this->InitializeSprite(sprite);

	this->shift = D3DXVECTOR2(static_cast<float>(this->GetSprite()->GetWidth()) / 2.0f, static_cast<float>(this->GetSprite()->GetHeight()));
	this->SetPosition(*_playerPosition - shift);
	this->SetCenterPoint();

	this->InitializeHitbox(Hitbox::Shape::ELIPSE, Hitbox::Size::EXTENDED_LENGTH);
	this->inUse = false;
	
#ifdef DEBUG
	tmp = new Sprite(device, Sprite::GetFilePath( "bonusPower"));
#endif
}

void Bomb::Update(float const time)
{
	if (inUse)
	{
		this->elapsedTime += time;
		if (elapsedTime < maxTime)
		{
			this->SetPosition(*_playerPosition - shift);
			this->SetCenterPoint();
			GameObject::Update( time );
		}
		else
			inUse = false;
	}
};

void Bomb::Draw( RECT const & rect )
{
	GameObject::Draw(rect);
#ifdef DEBUG
	// narysowanie hitboxa
	HitboxElipse * hElipse = dynamic_cast<HitboxElipse*>(GetHitbox());
	if (hElipse != NULL)
	{
		for (float i = 0; i < 2 * D3DX_PI; i += 0.01)
		{
			this->tmp->Draw(centerPoint + Vector::Polar(hElipse->GetRadiusA(), hElipse->GetRadiusB(), i));
		}
	}
#endif
};

void Bomb::Launch()
{
	elapsedTime = 0;
	inUse = true;
};