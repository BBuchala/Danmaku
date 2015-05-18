#include "EnemyPattern02.h"

EnemyPattern02::EnemyPattern02() : EPattern(0.0f), scaleTime(0.0f), _elapsedTime(0.0f)
{
}


void EnemyPattern02::Initialize(D3DXVECTOR2 const & position)
{
	EPattern::Initialize(position);
	trajMap_.insert(TrajectoryPair("traj1", TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::SPIRAL, position, 0, 24 ) ) ) );
	trajMap_.insert(TrajectoryPair("traj2", TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::SPIRAL, position, 0, 24 ) ) ) );
	trajMap_["traj2"]->Rotate( D3DXToRadian( 180.0f ) );
};


void EnemyPattern02::Update(float const time, D3DXVECTOR2 const & position)
{
	// Nowe pociski
	if (_bullet.size() < BULLET_NUMBER_S)
	{
		if (_elapsedTime >= 0.01000f)
		{
			Add();
			_elapsedTime = 0;
		}
		_elapsedTime += time;
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
	for ( EBulletQue::const_iterator it = _bullet.begin(); it != _bullet.end(); it++ )
	{
		(*it)->Update(time);
	}
};


void EnemyPattern02::Add()
{
	// nowy pocisk o zerowej prêdkoœci
	EnemyBullet * newBullet;
	newBullet = new EnemyBullet( 0.0f );
	if ( _bullet.size() == 0 )
	{
		// pobranie œcie¿ki do pliku ze sprajtem i utworzenie go
		std::string file = Sprite::GetFilePath( "Bullet0", 3, "png" );
		//newBullet->InitializeSprite( _device, file );
	}
	else
	{
		newBullet->SetSprite( _bullet[0]->GetSprite() );
	}

	newBullet->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::HALF_LENGTH );
	
	// wybór trajektorii
	newBullet->SetTrajectory( _bullet.size() % 2 == 0 ? trajMap_["traj1"] : trajMap_["traj2"] );
	// odleg³oœæ od ogniska spirali
	newBullet->SetDistance( D3DXToRadian( _bullet.size() * 5.0f ) );
	// dodanie pocisku
	_bullet.push_back(newBullet);
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
