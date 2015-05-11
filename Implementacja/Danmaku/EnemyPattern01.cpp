#include "EnemyPattern01.h"

EnemyPattern01::EnemyPattern01() : bulletTime(0.0f)
{
};


void EnemyPattern01::Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position)
{
	EPattern::Initialize(device, position);
	road_[Traj::vElipse] = "vElipse";
	road_[Traj::hElipse] = "hElipse";
	road_[Traj::circle] = "circle";
	road_[Traj::line1] = "line1";
	road_[Traj::line2] = "line2";

	// utworzenie torów dla pocisków
	trajMap_.insert(TrajectoryPair(road_[vElipse], TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::ELIPSE, position, 300, 100 ) ) ) );
	trajMap_.insert(TrajectoryPair(road_[hElipse], TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::ELIPSE, position, 100, 300 ) ) ) );
	trajMap_.insert(TrajectoryPair(road_[circle],  TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::ELIPSE, position, 220, 220 ) ) ) );
	trajMap_.insert(TrajectoryPair(road_[line1],   TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, position, D3DXToRadian(-60) ) ) ) );
	trajMap_.insert(TrajectoryPair(road_[line2],   TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, position, D3DXToRadian(-120), 600 ) ) ) );

	initialized_ = false;
	initCount_ = 0;
};


void EnemyPattern01::Update(float const time)
{
	// OBS£UGA POCISKÓW
	// Nowe pociski
	this->elapsedTime += time;
	if ( !initialized_ )
	{
		this->bulletTime += time;
		if (bulletTime >= 0.25f)
		{
			Add();
			bulletTime = 0.0f;
			initCount_++;
		}
		if (initCount_ == BULLET_JUMP_A)
		{
			initialized_ = true;
		}
	}

	EBulletQue::const_iterator it;
	for ( it = bullet.begin(); it != bullet.end(); it++ )
	{
		(*it)->Rotate(0.1f);
		(*it)->GetTrajectory()->Rotate(0.001f);
	}

	if (this->elapsedTime > 5.000000000f && this->elapsedTime < 7.000000000f)
	{
		for ( it = bullet.begin(); it != bullet.end(); it++ )
		{
			(*it)->SetAcceleration(1);
			if ((*it)->GetTrajectory() == trajMap_[road_[vElipse]] ||
				(*it)->GetTrajectory() == trajMap_[road_[hElipse]] )
			{
				(*it)->GetTrajectory()->Scale( 9.9900f / 10.0f );
			}
			else if ((*it)->GetTrajectory() == trajMap_[road_[circle]])
			{
				(*it)->Scale ( 1.008f / 1.000f );
				(*it)->GetTrajectory()->Scale ( 1.0003f / 1.000f );
			}
		}
	}
	else if (this->elapsedTime > 7.000000000f && this->elapsedTime < 9.00000000f)
	{
		for ( it = bullet.begin(); it != bullet.end(); it++ )
		{
			(*it)->SetAcceleration(-1);
			if ((*it)->GetTrajectory() == trajMap_[road_[vElipse]] ||
				(*it)->GetTrajectory() == trajMap_[road_[hElipse]] )
			{
				(*it)->GetTrajectory()->Scale ( 10.0f / 9.9900f );
			}
			else if ((*it)->GetTrajectory() == trajMap_[road_[circle]])
			{
				(*it)->Scale ( 1.000f / 1.008f );
				(*it)->GetTrajectory()->Scale ( 1.000f / 1.0003f );
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


void EnemyPattern01::Add()
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
		newBullet->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::HALF_LENGTH );
		//newBullet->InitializeHitbox( Hitbox::Shape::ELLIPSE, Hitbox::Size::TWO_THIRDS_LENGTH, Sprite::GetFilePath("hitbox", "png"), device );

		switch(i)
		{
		case 0:
			newBullet->SetTrajectory( trajMap_[road_[Traj::vElipse]] ); 
			break;
		case 1:
			newBullet->SetTrajectory( trajMap_[road_[Traj::hElipse]] );
			break;
		case 2:
			newBullet->SetTrajectory( trajMap_[road_[Traj::circle]] );
			break;
		case 3:
			newBullet->SetTrajectory( trajMap_[road_[Traj::line1]] );
			break;
		case 4:
			newBullet->SetTrajectory( trajMap_[road_[Traj::line2]] );
			break;
		}
		newBullet->SetDistance( D3DXToRadian( 45.0f ) );
		this->bullet.push_back(newBullet);
	}
};


void EnemyPattern01::SetPosition(D3DXVECTOR2 const & pos)
{
	for(TrajectoryMap::const_iterator it = trajMap_.begin();
		it != trajMap_.end();
		++it)
	{
		it->second->SetStartPoint(pos);
	}
};
