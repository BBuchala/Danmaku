#include "Pattern02.h"

Pattern02::Pattern02() : scaleTime(0.0f)
{
}


void Pattern02::Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position)
{
	CPattern::Initialize(device);
	this->traj1 = TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory(Road::SPIRAL, position, 0, 24));
	this->traj2 = TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory(Road::SPIRAL, position, 0, 24));
	traj2->Rotate( D3DXToRadian( 180.0f ) );
};


void Pattern02::Update(float const & time)
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

	this->traj1->Rotate( D3DXToRadian( 1.0f ) );
	this->traj2->Rotate( D3DXToRadian( 1.0f ) );

	this->scaleTime += time;
	if (scaleTime >= 4.0000000f)
	{
		this->traj1->Scale( 0.9994f );
		this->traj2->Scale( 0.9994f );
	}

	// Zmiana po³o¿enia pocisków
	for ( EBulletQue::const_iterator it = bullet.begin(); it != bullet.end(); it++ )
	{
		(*it)->Update(time);
	}
};


void Pattern02::Add()
{
	// nowy pocisk o zerowej prêdkoœci
	EnemyBullet * newBullet;
	newBullet = new EnemyBullet( 0.0f );
	if ( bullet.size() == 0 )
	{
		// pobranie œcie¿ki do pliku ze sprajtem i utworzenie go
		std::string file = Sprite::GetFilePath( "Bullet0", 3, "png" );
		newBullet->InitializeSprite( device, file, BULLET_WIDTH_S, BULLET_HEIGHT_S );
	}
	else
	{
		newBullet->SetSprite( bullet[0]->GetSprite() );
	}

	newBullet->InitializeHitbox( BULLET_WIDTH_S, false );
	
	// wybór trajektorii
	newBullet->SetTrajectory( bullet.size() % 2 == 0 ? traj1 : traj2 );
	// odleg³oœæ od ogniska spirali
	newBullet->SetDistance( D3DXToRadian( bullet.size() * 5.0f ) );
	// dodanie pocisku
	this->bullet.push_back(newBullet);
};