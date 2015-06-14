#include "PlayerPattern03.h"

/// <summary>
/// Tworzy nowπ instacjÍ klasy <see cref="PlayerPattern03"/>.
/// </summary>
PlayerPattern03::PlayerPattern03(void)
{
	leftShift = D3DXVECTOR2(20,15);
	rightShift = D3DXVECTOR2(-20,15);
}

/// <summary>
/// Niszczy instancjÍ klasy <see cref="PlayerPattern03"/>.
/// </summary>
PlayerPattern03::~PlayerPattern03(void)
{
}

/// <summary>
/// Aktualizuje stan.
/// </summary>
/// <param name="time">PrÛbka czasu.</param>
void PlayerPattern03::Update(float const time)
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
void PlayerPattern03::AddBullet()
{
	for (int i = 0; i < 2; i++ )
	{
		PlayerBullet * newBullet;
		newBullet = new PlayerBullet( 1000.0f, 100 );
		
		newBullet->SetSprite ( templateSprite );
		
		newBullet->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::HALF_LENGTH );

		newBullet->SetDistance( D3DXToRadian( 45.0f ) );
		switch (i % 2)
		{
			case 0:
				newBullet->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, *position - leftShift, D3DXToRadian(90) ) ) );
				break;
			case 1:
				newBullet->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, *position - rightShift, D3DXToRadian(90) ) ) );
				break;
			default:
				break;
		}
		this->bullet.push_back( newBullet );
	}
}

/// <summary>
/// Za≥adowanie sprajtÛw dla pociskÛw.
/// </summary>
/// <param name="pbsResource">èrÛd≥o sprajtÛw pociskÛw.</param>
void PlayerPattern03::LoadSprite(PlayerBulletSpriteResource & pbsResource)
{
	this->LoadBulletType(templateSprite, "PlayerBullet2", pbsResource);
};
