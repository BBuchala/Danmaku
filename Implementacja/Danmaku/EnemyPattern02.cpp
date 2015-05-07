#include "EnemyPattern02.h"

EnemyPattern02::EnemyPattern02() : scaleTime(0.0f)
{
}


void EnemyPattern02::Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position)
{
	EPattern::Initialize(device, position);
	trajMap_.insert(TrajectoryPair("traj1", TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::SPIRAL, position, 0, 24 ) ) ) );
	trajMap_.insert(TrajectoryPair("traj2", TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::SPIRAL, position, 0, 24 ) ) ) );
	trajMap_["traj2"]->Rotate( D3DXToRadian( 180.0f ) );
};


void EnemyPattern02::Update(float const time)
{
	// Nowe pociski
	if (bullet.size() < BULLET_NUMBER_S)
	{
		if (this->elapsedTime >= 0.01000f)
		{
			Add();
			this->elapsedTime = 0;
		}
		this->elapsedTime += time;
	}

	for(TrajectoryMap::const_iterator it = trajMap_.begin();
		it != trajMap_.end();
		++it)
	{
		it->second->Rotate( D3DXToRadian( 1.0f ) );
	}

	this->scaleTime += time;
	if (scaleTime >= 4.0000000f)
	{
		for(TrajectoryMap::const_iterator it = trajMap_.begin();
			it != trajMap_.end();
			++it)
		{
			it->second->Scale( 0.9994f );
		}
	}

	// Zmiana po³o¿enia pocisków
	for ( EBulletQue::const_iterator it = bullet.begin(); it != bullet.end(); it++ )
	{
		(*it)->Update(time);
	}
};


void EnemyPattern02::Add()
{
	// nowy pocisk o zerowej prêdkoœci
	EnemyBullet * newBullet;
	newBullet = new EnemyBullet( 0.0f );
	if ( bullet.size() == 0 )
	{
		// pobranie œcie¿ki do pliku ze sprajtem i utworzenie go
		std::string file = Sprite::GetFilePath( "Bullet0", 3, "png" );
		newBullet->InitializeSprite( device, file );
	}
	else
	{
		newBullet->SetSprite( bullet[0]->GetSprite() );
	}

	newBullet->InitializeHitbox( DEFAULT_HITBOX_RADIUS );
	
	// wybór trajektorii
	newBullet->SetTrajectory( bullet.size() % 2 == 0 ? trajMap_["traj1"] : trajMap_["traj2"] );
	// odleg³oœæ od ogniska spirali
	newBullet->SetDistance( D3DXToRadian( bullet.size() * 5.0f ) );
	// dodanie pocisku
	this->bullet.push_back(newBullet);
};


void EnemyPattern02::SetPosition(D3DXVECTOR2 const & pos)
{
	for(TrajectoryMap::const_iterator it = trajMap_.begin();
		it != trajMap_.end();
		++it)
	{
		it->second->SetStartPoint(pos);
	}
};
