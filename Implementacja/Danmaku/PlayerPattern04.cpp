#include "PlayerPattern04.h"


PlayerPattern04::PlayerPattern04(void)
{
}


PlayerPattern04::~PlayerPattern04(void)
{
}

void PlayerPattern04::Initialize(D3DXVECTOR2 const & position)
{
	PPattern::Initialize(position);
	leftShift = D3DXVECTOR2(20,15);
	rightShift = D3DXVECTOR2(-20,15);
};

void PlayerPattern04::Update(float const time, D3DXVECTOR2 const & playerPos)
{
	if (this->elapsedTime >= 0.07000f)
		{
			if (this->isKeyPressed)
				Add(playerPos);
			this->elapsedTime = 0;
		}
		this->elapsedTime += time;


	for ( PBulletQue::const_iterator it = bullet.begin(); it != bullet.end(); it++ )
	{
		(*it)->Update(time);
	}
}

void PlayerPattern04::Add(D3DXVECTOR2 const & playerPos)
{
	for (int i = 0; i < 2; i++ )
	{
		PlayerBullet * newBullet;
		PlayerBullet * newBullet2;

		newBullet = new PlayerBullet( 1000.0f, 100 );
		newBullet2 = new PlayerBullet( 800.0f, 50 );

		newBullet->SetSprite ( templateSprite );
		newBullet2->SetSprite ( templateSprite2 );
		
		newBullet->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::HALF_LENGTH );
		newBullet2->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::HALF_LENGTH );

		switch (i % 2)
		{
			case 0:
				newBullet->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, playerPos - leftShift, D3DXToRadian(90) ) ) );
				newBullet2->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, playerPos - rightShift, D3DXToRadian(85) ) ) );
				break;
			case 1:
				newBullet->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, playerPos - rightShift, D3DXToRadian(90) ) ) );
				newBullet2->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, playerPos - leftShift, D3DXToRadian(95) ) ) );
				break;

			default:
				break;
		}
		this->bullet.push_back( newBullet );
		this->bullet.push_back( newBullet2 );
	}
}

void PlayerPattern04::LoadSprite(PlayerBulletSpriteResource & pbsResource)
{
	templateSprite = pbsResource["PlayerBullet1"];
	templateSprite2 = pbsResource["PlayerBullet2"];
};
