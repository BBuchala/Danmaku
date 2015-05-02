#include "Pattern01.h"

Pattern01::Pattern01() : bulletTime(0.0f)
{
};


void Pattern01::Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position)
{
	EPattern::Initialize(device, position);
	// utworzenie torów dla pocisków
	this->vElipse = TrajectoryPtr( TrajectoryFactory::Instance().CreateTrajectory( Road::ELIPSE, position, 300, 100 ) );
	this->hElipse = TrajectoryPtr( TrajectoryFactory::Instance().CreateTrajectory( Road::ELIPSE, position, 100, 300 ) );
	this->circle = TrajectoryPtr( TrajectoryFactory::Instance().CreateTrajectory( Road::ELIPSE, position, 220, 220 ) );
	this->line1 = TrajectoryPtr( TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, position, D3DXToRadian(-60) ) );
	this->line2 = TrajectoryPtr( TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, position, D3DXToRadian(-120), 600 ) );
};



void Pattern01::Update(float const time)
{
	// OBS£UGA POCISKÓW
	// Nowe pociski
	this->elapsedTime += time;
	this->bulletTime += time;
	if ( bulletTime >= 0.25f && bullet.size() < BULLET_NUMBER_A  )
	{
		Add();
		bulletTime = 0.0f;
	}

	EBulletQue::const_iterator it;
	for ( it = bullet.begin(); it != bullet.end(); it++ )
	{
		(*it)->Rotate(0.1f);
		(*it)->GetTrajectory()->Rotate(0.001f);
	}

	if (this->elapsedTime > 5.000000000f && this->elapsedTime < 7.000000000f)
	{
		for ( unsigned int i = 0 ; i < bullet.size(); i++ )
		{
			this->bullet[i]->SetAcceleration(1);
			switch(i % BULLET_INC_A)
			{
			case 2:
				this->bullet[i]->Scale ( 1.008f / 1.000f );
				this->bullet[i]->GetTrajectory()->Scale ( 1.0003f / 1.000f );
				break;
			case 0: case 1:
				this->bullet[i]->GetTrajectory()->Scale( 9.9900f / 10.0f );
				break;
			}
		}
	}
	else if (this->elapsedTime > 7.000000000f && this->elapsedTime < 9.00000000f)
	{
		for ( unsigned  int i = 0 ; i < bullet.size(); i++ )
		{
			this->bullet[i]->SetAcceleration(-1);
			switch(i % BULLET_INC_A)
			{
			case 2:
				this->bullet[i]->Scale ( 1.000f / 1.008f );
				this->bullet[i]->GetTrajectory()->Scale ( 1.000f / 1.0003f );
				break;
			case 0: case 1:
				this->bullet[i]->GetTrajectory()->Scale ( 10.0f / 9.9900f );
				break;
			}
		}
	}
	else if (this->elapsedTime > 9.00000000f)
	{
		this->elapsedTime = 0.0f;
		for ( it = bullet.begin(); it != bullet.end(); it++ )
		{
			(*it)->SetAcceleration(0);
		}
	}

	// Zmiana po³o¿enia pocisków
	for ( it = bullet.begin(); it != bullet.end(); it++ )
	{
		(*it)->Update(time);
	}
};


void Pattern01::Add()
{
	// po parê naraz
	for (int i = 0; i < BULLET_INC_A; i++)
	{
		// nowy pocisk z pewn¹ prêdkoœci¹
		EnemyBullet * newBullet;
		switch(i)
		{
		// pewna prêdkoœæ k¹towa dla pocisków na elipsach
		case 0: case 1: case 2:
			newBullet = new EnemyBullet( D3DXToRadian( 90.0f ) ); break;
		// dla tych po linii
		default:
			newBullet = new EnemyBullet( 180.0f ); break;
		}
		std::string file = Sprite::GetFilePath( "Bullet0", 2, "png" );
		newBullet->InitializeSprite( device, file );
		newBullet->InitializeHitbox( DEFAULT_HITBOX_RADIUS );

		switch(i)
		{
		case 0:
			newBullet->SetTrajectory( vElipse ); 
			break;
		case 1:
			newBullet->SetTrajectory( hElipse );
			break;
		case 2:
			newBullet->SetTrajectory( circle );
			break;
		case 3:
			newBullet->SetTrajectory( line1 );
			break;
		case 4:
			newBullet->SetTrajectory( line2 );
			break;
		}
		newBullet->SetDistance( D3DXToRadian( 45.0f ) );
		this->bullet.push_back(newBullet);
	}
};


void Pattern01::SetPosition(D3DXVECTOR2 const & pos)
{
	this->vElipse->SetStartPoint(pos);
	this->hElipse->SetStartPoint(pos);
	this->circle->SetStartPoint(pos);
	this->line1->SetStartPoint(pos);
	this->line2->SetStartPoint(pos);
};
