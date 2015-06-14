#include "GameObject.h"

/// <summary>
/// Tworzy now� instacj� klasy <see cref="GameObject"/>.
/// </summary>
/// <param name="pos">Pozycja.</param>
/// <param name="speed">Szybko��.</param>
/// <param name="acc">Przyspieszenie.</param>
GameObject::GameObject(D3DXVECTOR2 const & pos, float const speed, float const acc)
	: acceleration(acc), scale(1.0f), rotation(0.0f)
{
	// Przydzielenie warto�ci sk�adowym
	this->SetPosition(pos);
	this->speed = speed;
	this->hitbox = NULL;
};

/// <summary>
/// Niszczy instancj� klasy <see cref="GameObject"/>.
/// </summary>

GameObject::~GameObject()
{
};

/// <summary>
/// Tworzy kopi� instacji klasy <see cref="GameObject"/>.
/// </summary>
/// <param name="bonus">Obiekt do skopiowania</param>
GameObject::GameObject( GameObject const & go ) : hitbox(go.hitbox->Clone())
{
	this->position = go.position;
	this->centerPoint = go.centerPoint;
	this->speed = go.speed;
	this->acceleration = go.acceleration;
	this->sprite = go.sprite;
	this->scale = go.scale;
	this->rotation = go.rotation;
};

/// <summary>
/// Ustawia punkt centralny.
/// </summary>
void GameObject::SetCenterPoint()
{
	this->centerPoint = this->position + this->GetSprite()->GetCenterPoint();
};

/// <summary>
/// Inicjalizuje sprajt.
/// </summary>
/// <param name="sprite">The sprite.</param>
/// <returns></returns>
bool GameObject::InitializeSprite(SpritePtr sprite)
{
	this->sprite = sprite;
	if ( !this->sprite)
	{
		return false;
	}
	this->SetCenterPoint();
	return true;
};

/// <summary>
/// Inicjalizuje hitbox.
/// </summary>
/// <param name="shape">The shape.</param>
/// <param name="size">The size.</param>
/// <returns></returns>
bool GameObject::InitializeHitbox( Hitbox::Shape const shape, Hitbox::Size const size )
{
	switch(shape)
	{
	case Hitbox::Shape::CIRCLE: default:
		hitbox = HitboxPtr(new HitboxCircle(size, static_cast<float>( min(sprite->GetWidth(), sprite->GetHeight()) ), &centerPoint));
		return true;
	case Hitbox::Shape::ELIPSE:
		hitbox = HitboxPtr(new HitboxElipse(size, static_cast<float>(sprite->GetWidth()) / 2.0f, static_cast<float>(sprite->GetHeight()) / 2.0f, &centerPoint));
		return true;
	}
	return false;
};

/// <summary>
/// Narysowanie
/// </summary>
/// <param name="rect">Protok�t w kt�rym sprajt mo�e by� rysowany.</param>
void GameObject::Draw( RECT const & rect )
{
	if (this->sprite && IsObjectWithinBounds(rect))
	{
		this->sprite->Draw(this->GetPosition(), scale, rotation);
	}
};


/// <summary>
/// Czy obiekt znajduje si� w przekazanym prostok�cie
/// </summary>
/// <param name="rect">Granice.</param>
/// <returns></returns>
bool GameObject::IsObjectWithinBounds( RECT const & rect )
{
	D3DXVECTOR2 center = this->GetCenterPoint();
	D3DXVECTOR2 diffPos = scale * (center - this->GetPosition());
	// je�eli ca�y sprajt 
	if (center.x + diffPos.x < rect.left	||	// jest za lew� �cian� lub
		center.y + diffPos.y < rect.top		||	// jest za g�rn� �cian� lub
		center.x - diffPos.x > rect.right	||	// jest za praw� �cian� lub
		center.y - diffPos.y > rect.bottom		// jest za doln� �cian�
		)
	{
		return false;	// nie rysuj go
	}
	// jak widac to rysuj, dozo~
	return true;
};

/// <summary>
/// Aktualizuje stan.
/// </summary>
/// <param name="time">Pr�bka czasu.</param>
void GameObject::Update(float const time)
{
	this->speed += this->acceleration * time;
	this->SetCenterPoint();
};


/// <summary>
/// Ustawia pozycj�.
/// </summary>
/// <param name="v">Pozycja.</param>
void GameObject::SetPosition(D3DXVECTOR2 const & v)
{
	this->position = v;
};


/// <summary>
/// Ustawia szybko��.
/// </summary>
/// <param name="speed">Szybko��.</param>
void GameObject::SetSpeed(float const speed)
{
	this->speed = speed;
};


/// <summary>
/// Ustawia przyspieszenie.
/// </summary>
/// <param name="acc">Przyspieszenie.</param>
void GameObject::SetAcceleration(float const acc)
{
	this->acceleration = acc;
};


/// <summary>
/// Obraca obiekt o wskazany k�t.
/// </summary>
/// <param name="angle">K�t.</param>
void GameObject::Rotate( float const angle )
{
	this->rotation += angle;
};



/// <summary>
/// Zmienia rozmiar wg skali.
/// </summary>
/// <param name="scale">Skala.</param>
void GameObject::Scale( float const scale )
{
	this->scale *= scale;
	this->hitbox->Scale( scale );
};



/// <summary>
/// Przesuwa obiekt.
/// </summary>
/// <param name="dv">Przesuni�cie.</param>
void GameObject::Translate( D3DXVECTOR2 const & dv )
{
	this->position += dv;
};

