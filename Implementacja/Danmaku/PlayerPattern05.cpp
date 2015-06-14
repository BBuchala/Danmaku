#include "PlayerPattern05.h"

/// <summary>
/// Tworzy nowπ instacjÍ klasy <see cref="PlayerPattern05"/>.
/// </summary>
PlayerPattern05::PlayerPattern05(void)
{
	leftShift = D3DXVECTOR2(20,15);
	rightShift = D3DXVECTOR2(-20,15);
}

/// <summary>
/// Niszczy instancjÍ klasy <see cref="PlayerPattern05"/>.
/// </summary>
PlayerPattern05::~PlayerPattern05(void)
{
}

/// <summary>
/// Aktualizuje stan.
/// </summary>
/// <param name="time">PrÛbka czasu.</param>
void PlayerPattern05::Update(float const time)
{
	if (this->elapsedTime >= 0.07000f)
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
void PlayerPattern05::AddBullet()
{
	for (int i = 0; i < 2; i++ )
	{
		PlayerBullet * newBullet;
		PlayerBullet * newBullet2;
		PlayerBullet * newBullet3;
		PlayerBullet * newBullet4;

		newBullet = new PlayerBullet( 1000.0f, 150 );
		newBullet2 = new PlayerBullet( 800.0f, 100 );
		newBullet3 = new PlayerBullet( 600.0f, 50 );
		newBullet4 = new PlayerBullet( 600.0f, 50 );

		newBullet->SetSprite ( templateSprite );
		newBullet2->SetSprite ( templateSprite2 );
		newBullet3->SetSprite ( templateSprite3 );
		newBullet4->SetSprite ( templateSprite4 );
		
		newBullet->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::HALF_LENGTH );
		newBullet2->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::HALF_LENGTH );
		newBullet3->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::HALF_LENGTH );
		newBullet4->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::HALF_LENGTH );

		switch (i % 2)
		{
			case 0:
				newBullet->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, *position - leftShift, D3DXToRadian(90) ) ) );
				newBullet2->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, *position - rightShift, D3DXToRadian(85) ) ) );
				newBullet3->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, *position + leftShift, D3DXToRadian(-90) ) ) );
				newBullet4->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, *position - rightShift, D3DXToRadian(80) ) ) );
				break;
			case 1:
				newBullet->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, *position - rightShift, D3DXToRadian(90) ) ) );
				newBullet2->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, *position - leftShift, D3DXToRadian(95) ) ) );
				newBullet3->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, *position + rightShift, D3DXToRadian(-90) ) ) );
				newBullet4->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, *position - leftShift, D3DXToRadian(100) ) ) );
				break;

			default:
				break;
		}
		this->bullet.push_back( newBullet );
		this->bullet.push_back( newBullet2 );
		this->bullet.push_back( newBullet3 );
		this->bullet.push_back( newBullet4 );
	}
}

/// <summary>
/// Za≥adowanie sprajtÛw dla pociskÛw.
/// </summary>
/// <param name="pbsResource">èrÛd≥o sprajtÛw pociskÛw.</param>
void PlayerPattern05::LoadSprite(PlayerBulletSpriteResource & pbsResource)
{
	this->LoadBulletType(templateSprite, "PlayerBullet3", pbsResource);
	this->LoadBulletType(templateSprite2, "PlayerBullet2", pbsResource);
	this->LoadBulletType(templateSprite3, "PlayerBullet4", pbsResource);
	this->LoadBulletType(templateSprite4, "PlayerBullet1", pbsResource);
};
