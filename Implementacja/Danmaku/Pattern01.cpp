#include "Pattern01.h"

Pattern01::~Pattern01()
{
	if (hBullet && vBullet)
	{
		for (int i = 0; i < BULLET_NUMBER; i++)
		{
			delete hBullet[i];
			delete vBullet[i];
			delete mBullet[i];
		}
		delete[] hBullet;
		delete[] vBullet;
		delete[] mBullet;
	}
};


void Pattern01::Initialize(LPDIRECT3DDEVICE9 device)
{
	this->bulletNumber = 1;
	this->elapsedTime = 0.0f;
	this->scale = true;

	// u³omna implementacja pocisków
	this->hBullet = new EnemyBulletElipse * [BULLET_NUMBER];
	this->vBullet = new EnemyBulletElipse * [BULLET_NUMBER];
	this->mBullet = new EnemyBulletElipse * [BULLET_NUMBER];
	this->sBullet = new EnemyBulletElipse * [BULLET_NUMBER];
	for (int i = 0; i < BULLET_NUMBER; i++)
	{
		hBullet[i] = new EnemyBulletElipse( 200, 200, 90 );
		vBullet[i] = new EnemyBulletElipse( 200, 200, 90 );
		mBullet[i] = new EnemyBulletElipse( 200, 200, 90 );
		std::string file = Sprite::GetFilePath( "Bullet0", 2, "png" );
		hBullet[i]->Initialize( device, file, BULLET_WIDTH, BULLET_HEIGHT );
		vBullet[i]->Initialize( device, file, BULLET_WIDTH, BULLET_HEIGHT );
		mBullet[i]->Initialize( device, file, BULLET_WIDTH, BULLET_HEIGHT );
		hBullet[i]->setElipseTrajectory( 400, 300, 300, 100 );
		vBullet[i]->setElipseTrajectory( 400, 300, 100, 300 );
		mBullet[i]->setCircleTrajectory( 400, 300 );
	}
};



void Pattern01::Update(float const & time)
{
	// OBS£UGA POCISKÓW
	// Nowe pociski
	if (bulletNumber < BULLET_NUMBER)
	{
		if (this->elapsedTime >= 0.500000f)
		{
			bulletNumber++;
			this->elapsedTime = 0;
		}
	}

	this->elapsedTime += time;

	for (unsigned int i = 0; i < bulletNumber; i++)
	{
		this->vBullet[i]->Rotate(0.1f);
		this->hBullet[i]->Rotate(0.1f);
		this->mBullet[i]->Rotate(0.1f);
	}

	if (this->elapsedTime > 3.000000000f && this->elapsedTime < 6.000000000f)
	{
		for (unsigned int i = 0; i < bulletNumber; i++)
		{
			this->vBullet[i]->SetAcceleration(1);
			this->hBullet[i]->SetAcceleration(1);
			this->mBullet[i]->SetAcceleration(1);
			this->mBullet[i]->Scale ( 1.008f / 1.000f );
		}
		if (this->scale)
		{
			for (unsigned int i = 0; i < bulletNumber; i++)
			{
				this->vBullet[i]->ScaleRadius( 0.99f );
				this->hBullet[i]->ScaleRadius( 0.99f );
			}
		}
	}
	else if (this->elapsedTime > 6.000000000f && this->elapsedTime < 9.00000000f)
	{
		for (unsigned int i = 0; i < bulletNumber; i++)
		{
			this->vBullet[i]->SetAcceleration(-1);
			this->hBullet[i]->SetAcceleration(-1);
			this->mBullet[i]->SetAcceleration(-1);
			this->mBullet[i]->Scale ( 1.000f / 1.008f );
		}
		if (this->scale)
		{
			for (unsigned int i = 0; i < bulletNumber; i++)
			{
				this->vBullet[i]->ScaleRadius( 10.0f / 9.9000f );
				this->hBullet[i]->ScaleRadius( 10.0f / 9.9000f );
			}
		}
	}
	else if (this->elapsedTime > 9.00000000f)
	{
		this->elapsedTime = 0;
		for (unsigned int i = 0; i < bulletNumber; i++)
		{
			this->vBullet[i]->SetAcceleration(0);
			this->hBullet[i]->SetAcceleration(0);
			this->mBullet[i]->SetAcceleration(0);
		}
	}

	// Zmiana po³o¿enia pocisków
	for (unsigned int i = 0; i < bulletNumber; i++)
	{
		this->vBullet[i]->Update(time);
		this->hBullet[i]->Update(time);
		this->mBullet[i]->Update(time);
	}
};


void Pattern01::Draw()
{
	for (unsigned int i = 0; i < this->bulletNumber; i++)
	{
		this->vBullet[i]->Draw();
		this->hBullet[i]->Draw();
		this->mBullet[i]->Draw();
	}
};


void Pattern01::SetScale( float const & scale, float const & frac_time )
{
	this->scale = true;
	this->scale_frac = scale /  frac_time;
};