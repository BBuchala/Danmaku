#include "PlayerPattern.h"


PlayerPattern::PlayerPattern(void)
{
}


PlayerPattern::~PlayerPattern(void)
{
}

void PlayerPattern::Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position)
{
	CPattern::Initialize(device);
	this->line1 = TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, position, D3DXToRadian(90) ) );
}

// Póki co nie u¿ywana
void PlayerPattern::Update(float const time)
{
	if (this->elapsedTime >= 0.05000f)
		{
			//Add();
			this->elapsedTime = 0;
		}
		this->elapsedTime += time;


	for ( EBulletQue::const_iterator it = bullet.begin(); it != bullet.end(); it++ )
	{
		(*it)->Update(time);
	}
}

void PlayerPattern::Update(float const time, bool pressedKey, D3DXVECTOR2 const & playerPos)
{
	if (this->elapsedTime >= 0.05000f)
		{
			if (pressedKey)
				Add(playerPos);
			this->elapsedTime = 0;
		}
		this->elapsedTime += time;


	for ( EBulletQue::const_iterator it = bullet.begin(); it != bullet.end(); it++ )
	{
		(*it)->Update(time);
	}
}

void PlayerPattern::Add(D3DXVECTOR2 const & playerPos)
{
	EnemyBullet * newBullet;
	newBullet = new EnemyBullet( 1000.0f );
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