#include "PlayerPattern01.h"


PlayerPattern01::PlayerPattern01(void)
{
}


PlayerPattern01::~PlayerPattern01(void)
{
}

void PlayerPattern01::Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position)
{
	PPattern::Initialize(device, position);
}

// Póki co nie u¿ywana
void PlayerPattern01::Update(float const time)
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

void PlayerPattern01::Update(float const time, bool pressedKey, D3DXVECTOR2 const & playerPos)
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

void PlayerPattern01::Add(D3DXVECTOR2 const & playerPos)
{
	PlayerBullet * newBullet;
	newBullet = new PlayerBullet( 1000.0f, 50 );
	if ( bullet.size() == 0 )
	{
		// pobranie œcie¿ki do pliku ze sprajtem i utworzenie go
		std::string file = Sprite::GetFilePath( "PlayerBullet","png");
		newBullet->InitializeSprite( device, file );
	}
	else
	{
		newBullet->SetSprite( bullet[0]->GetSprite() );
	}

	newBullet->InitializeHitbox( DEFAULT_HITBOX_RADIUS );

	newBullet->SetDistance( D3DXToRadian( 45.0f ) );
	newBullet->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, playerPos, D3DXToRadian(90) ) ) );
	this->bullet.push_back( newBullet );
}
