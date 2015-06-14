#include "PlayerPattern02.h"

/// <summary>
/// Tworzy now¹ instacjê klasy <see cref="PlayerPattern02"/>.
/// </summary>
PlayerPattern02::PlayerPattern02(void)
{
}

/// <summary>
/// Niszczy instancjê klasy <see cref="PlayerPattern02"/>.
/// </summary>
PlayerPattern02::~PlayerPattern02(void)
{
}

/// <summary>
/// Aktualizuje stan.
/// </summary>
/// <param name="time">Próbka czasu.</param>
void PlayerPattern02::Update(float const time)
{
	if (this->elapsedTime >= 0.08000f)
		{
			if (this->isKeyPressed)
				AddBullet();
			this->elapsedTime = 0;
		}
		this->elapsedTime += time;


	for ( PBulletQue::const_iterator it = bullet.begin(); it != bullet.end(); it++ )
	{
		(*it)->Update(time);
	}
}

/// <summary>
/// Dodanie nowego pocisku.
/// </summary>
void PlayerPattern02::AddBullet()
{
	PlayerBullet * newBullet;
	newBullet = new PlayerBullet( 1000.0f, 100 );
	newBullet->SetSprite ( templateSprite );
	newBullet->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::HALF_LENGTH );
	newBullet->SetDistance( D3DXToRadian( 45.0f ) );
	newBullet->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, *position, D3DXToRadian(90) ) ) );
	this->bullet.push_back( newBullet );
}

/// <summary>
/// Za³adowanie sprajtów dla pocisków.
/// </summary>
/// <param name="pbsResource">ród³o sprajtów pocisków.</param>
void PlayerPattern02::LoadSprite(PlayerBulletSpriteResource & pbsResource)
{
	this->LoadBulletType(templateSprite, "PlayerBullet2", pbsResource);
};
