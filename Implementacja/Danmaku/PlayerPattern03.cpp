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
};

// Póki co nie u¿ywana
void PlayerPattern03::Update(float const time)
{
	if (this->elapsedTime >= 0.05000f)
		{
			//Add();
			this->elapsedTime = 0;
		}
		this->elapsedTime += time;


	for ( PBulletQue::const_iterator it = bullet.begin(); it != bullet.end(); it++ )
	{
		(*it)->Update(time);
	}
}

void PlayerPattern03::Update(float const time, bool pressedKey, D3DXVECTOR2 & playerPos)
{
	if (this->elapsedTime >= 0.05000f)
		{
			if (pressedKey)
				Add(playerPos);
			this->elapsedTime = 0;
		}
		this->elapsedTime += time;


	for ( PBulletQue::const_iterator it = bullet.begin(); it != bullet.end(); it++ )
	{
		(*it)->Update(time);
	}
}

void PlayerPattern03::Add(D3DXVECTOR2 & playerPos)
{
	for (int i = 0; i < 2; i++ )
	{
		PlayerBullet * newBullet;
		PlayerBullet * newBullet2;

		newBullet = new PlayerBullet( 1000.0f, 100 );
		newBullet2 = new PlayerBullet( 800.0f, 50 );

		if ( bullet.size() == 0 )
		{
			std::string file = Sprite::GetFilePath( "PlayerBullet2","png");
			newBullet->InitializeSprite( device, file );

			file = Sprite::GetFilePath( "PlayerBullet","png");
			newBullet2->InitializeSprite( device, file );
		}
		else
		{
			newBullet->SetSprite( bullet[0]->GetSprite() );
			newBullet2->SetSprite( bullet[1]->GetSprite() );
		}
		
		newBullet->InitializeHitbox( DEFAULT_HITBOX_RADIUS );
		newBullet2->InitializeHitbox( DEFAULT_HITBOX_RADIUS );

		//newBullet->SetDistance( D3DXToRadian( 180.0f ) );
		//newBullet2->SetDistance( D3DXToRadian( 45.0f ) );

		

		switch (i % 2)
		{
			case 0:
				newBullet->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, playerPos - leftShift, D3DXToRadian(90) ) ) );
				newBullet2->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, playerPos - rightShift, D3DXToRadian(75) ) ) );
				//newBullet2->Rotate(D3DXToRadian(-15));
				break;
			case 1:
				newBullet->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, playerPos - rightShift, D3DXToRadian(90) ) ) );
				newBullet2->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, playerPos - leftShift, D3DXToRadian(105) ) ) );
				//newBullet2->Rotate(D3DXToRadian(15));
				break;

			default:
				break;
		}
		this->bullet.push_back( newBullet );
		this->bullet.push_back( newBullet2 );
	}
}