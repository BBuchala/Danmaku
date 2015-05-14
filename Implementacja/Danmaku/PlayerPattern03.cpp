#include "PlayerPattern03.h"


PlayerPattern03::PlayerPattern03(void)
{
}


PlayerPattern03::~PlayerPattern03(void)
{
}

void PlayerPattern03::Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position)
{
	PPattern::Initialize(device, position);
	leftShift = D3DXVECTOR2(20,15);
	rightShift = D3DXVECTOR2(-20,15);
}

void PlayerPattern03::Update(float const time, D3DXVECTOR2 const & playerPos)
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

void PlayerPattern03::Add(D3DXVECTOR2 const & playerPos)
{
	for (int i = 0; i < 2; i++ )
	{
		PlayerBullet * newBullet;
		newBullet = new PlayerBullet( 1000.0f, 100 );
		if ( bullet.size() == 0 )
		{
			// pobranie œcie¿ki do pliku ze sprajtem i utworzenie go
			std::string file = Sprite::GetFilePath( "PlayerBullet2","png");
			newBullet->InitializeSprite( device, file );
		}
		else
		{
			newBullet->SetSprite( bullet[0]->GetSprite() );
		}
		
		newBullet->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::HALF_LENGTH );

		newBullet->SetDistance( D3DXToRadian( 45.0f ) );
		switch (i % 2)
		{
			case 0:
				newBullet->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, playerPos - leftShift, D3DXToRadian(90) ) ) );
				break;
			case 1:
				newBullet->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, playerPos - rightShift, D3DXToRadian(90) ) ) );
				break;
			default:
				break;
		}
		this->bullet.push_back( newBullet );
	}
}