#include "Bomb.h"

/// <summary>
/// Tworzy now� instacj� klasy <see cref="Bomb"/>.
/// </summary>
/// <param name="playerPosition">Pozycja gracza.</param>
/// <param name="speed">Szybko��.</param>
Bomb::Bomb(D3DXVECTOR2 * const playerPosition, float const speed) : GameObject(position, speed), maxTime(3.0f), damage(30)
{
	_playerPosition = playerPosition;
};

/// <summary>
/// Tworzy kopi� instacji klasy <see cref="Bomb"/>.
/// </summary>
/// <param name="bomb">The bomb.</param>
Bomb::Bomb(Bomb const & bomb) : GameObject(bomb), maxTime(3.0f), damage(30)
{
};

/// <summary>
/// Niszczy instancj� klasy <see cref="Bomb"/>.
/// </summary>
Bomb::~Bomb()
{
};

/// <summary>
/// Inicjalizuje obiekt bomby
/// </summary>
/// <param name="device">Urz�dznie graficzne.</param>
bool Bomb::Initialize(LPDIRECT3DDEVICE9 device)
{	
	bool success = true;
	SpritePtr sprite = SpritePtr(new Sprite(device, Sprite::GetFilePath("master_spark")));
	success &= this->InitializeSprite(sprite);
	this->shift = D3DXVECTOR2(static_cast<float>(this->GetSprite()->GetWidth()) / 2.0f, static_cast<float>(this->GetSprite()->GetHeight()));
	this->SetPosition(*_playerPosition - shift);
	this->SetCenterPoint();
	this->inUse = false;
	success &= this->InitializeHitbox(Hitbox::Shape::ELIPSE, Hitbox::Size::EXTENDED_LENGTH);

#ifdef DEBUG
	tmp = new Sprite(device, Sprite::GetFilePath( "bonusPower"));
#endif

	return success;
}

/// <summary>
/// Aktualizuje stan.
/// </summary>
/// <param name="time">Pr�bka czasu.</param>
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

/// <summary>
/// Narysowanie bomby
/// </summary>
/// <param name="rect">Protok�t w kt�rym sprajt mo�e by� rysowany.</param>
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

/// <summary>
/// Odpalenie bomby.
/// </summary>
void Bomb::Launch()
{
	elapsedTime = 0;
	inUse = true;
};