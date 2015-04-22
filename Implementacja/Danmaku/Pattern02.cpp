#include "Pattern02.h"

Pattern02::~Pattern02()
{
	if (bullet)
	{
		for (int i = 0; i < BULLET_NUMBER; i++)
		{
			delete bullet[i];
		}
		delete[] bullet;
	}
};


void Pattern02::Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position)
{
	this->bulletNumber = 0;
	this->elapsedTime = this->scaleTime = 0.0f;
	this->bullet = new EnemyBullet * [BULLET_NUMBER];

	this->traj1 = TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory(Road::SPIRAL, position, 0, 24));
	this->traj2 = TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory(Road::SPIRAL, position, 0, 24));
	traj2->Rotate( D3DXToRadian( 180.0f ) );

	for (int i = 0; i < BULLET_NUMBER; i++)
	{
		bullet[i] = new EnemyBullet( position, 0 );
		std::string file = Sprite::GetFilePath( "Bullet0", 3, "png" );
		bullet[i]->Initialize( device, file, BULLET_WIDTH, BULLET_HEIGHT );
		bullet[i]->SetTrajectory( i % 2 == 0 ? traj1 : traj2 );
		bullet[i]->SetDistance( D3DXToRadian( i * 5.0f ) );
	}
};


void Pattern02::Update(float const & time)
{
	// Nowe pociski
	if (bulletNumber < BULLET_NUMBER)
	{
		if (this->elapsedTime >= 0.01000f)
		{
			bulletNumber++;
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
	for (unsigned int i = 0; i < bulletNumber; i++)
	{
		this->bullet[i]->Update(time);
	}
};


void Pattern02::Draw()
{
	for (unsigned int i = 0; i < bulletNumber; i++)
	{
		this->bullet[i]->Draw();
	}
};