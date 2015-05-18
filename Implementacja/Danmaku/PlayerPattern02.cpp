#include "PlayerPattern02.h"


PlayerPattern02::PlayerPattern02(void)
{
}


PlayerPattern02::~PlayerPattern02(void)
{
}

void PlayerPattern02::Initialize(D3DXVECTOR2 const & position)
{
	PPattern::Initialize(position);
}

void PlayerPattern02::Update(float const time, D3DXVECTOR2 const & playerPos)
{
	if (this->elapsedTime >= 0.08000f)
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

void PlayerPattern02::Add(D3DXVECTOR2 const & playerPos)
{
	PlayerBullet * newBullet;
	newBullet = new PlayerBullet( 1000.0f, 100 );
	
	newBullet->SetSprite ( templateSprite );

	newBullet->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::HALF_LENGTH );
	//newBullet->InitializeHitbox( Hitbox::Shape::ELLIPSE, Hitbox::Size::HALF_LENGTH, Sprite::GetFilePath("hitbox", "png"), device );

	newBullet->SetDistance( D3DXToRadian( 45.0f ) );
	newBullet->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, playerPos, D3DXToRadian(90) ) ) );
	this->bullet.push_back( newBullet );
}

void PlayerPattern02::LoadSprite(PlayerBulletSpriteResource & pbsResource)
{
	templateSprite = pbsResource["PlayerBullet2"];
};
