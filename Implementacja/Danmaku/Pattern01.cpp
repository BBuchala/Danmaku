#include "Pattern01.h"

Pattern01::~Pattern01()
{
	for ( EBulletQue::const_iterator it = bullet.begin(); it != bullet.end(); it++ )
	{
		delete *it;
	}
};


void Pattern01::Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position)
{
	this->elapsedTime = bulletTime = 0.0f;
	// utworzenie torów dla pocisków
	this->vElipse = TrajectoryPtr( TrajectoryFactory::Instance().CreateTrajectory( Road::ELIPSE, position, 500, 200 ) );
	this->hElipse = TrajectoryPtr( TrajectoryFactory::Instance().CreateTrajectory( Road::ELIPSE, position, 200, 500 ) );
	this->circle = TrajectoryPtr( TrajectoryFactory::Instance().CreateTrajectory( Road::ELIPSE, position, 330, 330 ) );
	this->device = device;
};



void Pattern01::Update(float const & time)
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

	if (this->elapsedTime > 4.000000000f && this->elapsedTime < 6.000000000f)
	{
		for ( unsigned int i = 0 ; i < bullet.size(); i++ )
		{
			this->bullet[i]->SetAcceleration(1);
			if ( i % BULLET_INC_A == 2 )
			{
				this->bullet[i]->Scale ( 1.008f / 1.000f );
				this->bullet[i]->GetTrajectory()->Scale ( 1.0003f / 1.000f );
			}
			else
				this->bullet[i]->GetTrajectory()->Scale( 9.9900f / 10.0f );
		}
	}
	else if (this->elapsedTime > 6.000000000f && this->elapsedTime < 8.00000000f)
	{
		for ( unsigned  int i = 0 ; i < bullet.size(); i++ )
		{
			this->bullet[i]->SetAcceleration(-1);
			if ( i % BULLET_INC_A == 2 )
			{
				this->bullet[i]->Scale ( 1.000f / 1.008f );
				this->bullet[i]->GetTrajectory()->Scale ( 1.000f / 1.0003f );
			}
			else
				this->bullet[i]->GetTrajectory()->Scale ( 10.0f / 9.9900f );
		}
	}
	else if (this->elapsedTime > 8.00000000f)
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


void Pattern01::Draw()
{
	for ( unsigned int i = 0; i < bullet.size(); i++)
	{
		this->bullet[i]->Draw();
	}
};


void Pattern01::Add()
{
	// po 3 naraz
	for (int i = 0; i < BULLET_INC_A; i++)
	{
		// nowy pocisk z pewn¹ prêdkoœci¹
		EnemyBullet * newBullet = new EnemyBullet( D3DXToRadian( 90.0f ) );
		std::string file = Sprite::GetFilePath( "Bullet0", 2, "png" );
		newBullet->Initialize( device, file, BULLET_WIDTH_A, BULLET_HEIGHT_A );

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
		}
		newBullet->SetDistance( D3DXToRadian( 45.0f ) );
		this->bullet.push_back(newBullet);
	}
};
