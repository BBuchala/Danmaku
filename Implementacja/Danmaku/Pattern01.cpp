#include "Pattern01.h"

Pattern01::~Pattern01()
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


void Pattern01::Initialize(LPDIRECT3DDEVICE9 device)
{
	this->elapsedTime = bulletTime = 0.0f;
	bulletNumber = 1;
	// u³omna implementacja pocisków
	this->bullet = new EnemyBullet * [BULLET_NUMBER];
	D3DXVECTOR2 center( 400, 300 );
	for (int i = 0; i < BULLET_NUMBER; i++)
	{
		bullet[i] = new EnemyBullet( D3DXToRadian( 90.0f ) );
		std::string file = Sprite::GetFilePath( "Bullet0", 2, "png" );
		bullet[i]->Initialize( device, file, BULLET_WIDTH, BULLET_HEIGHT );

		if ( i < 1 * BULLET_JUMP )
		{
			bullet[i]->SetTrajectory( Road::ELIPSE, center, 300, 100 );
		}
		else if ( i < 2 * BULLET_JUMP )
		{
			bullet[i]->SetTrajectory( Road::ELIPSE, center, 100, 300 );
		}
		else
		{
			bullet[i]->SetTrajectory( Road::ELIPSE, center, 220, 220 );
		}
		bullet[i]->SetDistance( D3DXToRadian( i * 45.0f ) );
	}
};



void Pattern01::Update(float const & time)
{
	// OBS£UGA POCISKÓW
	// Nowe pociski
	this->elapsedTime += time;
	this->bulletTime += time;
	if ( bulletTime >= 0.5f && bulletNumber < BULLET_JUMP  )
	{
		bulletTime = 0.0f;
		bulletNumber++;
	}

	for (unsigned int i = 0; i < BULLET_NUMBER; i++)
	{
		this->bullet[i]->Rotate(0.1f);
	}

	if (this->elapsedTime > 4.000000000f && this->elapsedTime < 7.000000000f)
	{
		for (unsigned int i = 0; i < BULLET_NUMBER; i++)
		{
			this->bullet[i]->SetAcceleration(1);
			if (i >= 2 * BULLET_JUMP )
				this->bullet[i]->Scale ( 1.008f / 1.000f );
			else
				this->bullet[i]->GetTrajectory()->Scale( 0.99f );
		}
	}
	else if (this->elapsedTime > 7.000000000f && this->elapsedTime < 10.00000000f)
	{
		for (unsigned int i = 0; i < BULLET_NUMBER; i++)
		{
			this->bullet[i]->SetAcceleration(-1);
			if (i >= 2 * BULLET_JUMP )
				this->bullet[i]->Scale ( 1.000f / 1.008f );
			else
				this->bullet[i]->GetTrajectory()->Scale ( 10.0f / 9.9000f );
		}
	}
	else if (this->elapsedTime > 10.00000000f)
	{
		this->elapsedTime = 0.0f;
		for (unsigned int i = 0; i < BULLET_NUMBER; i++)
		{
			this->bullet[i]->SetAcceleration(0);
		}
	}

	// Zmiana po³o¿enia pocisków
	for (unsigned int i = 0; i < BULLET_NUMBER; i++)
	{
		this->bullet[i]->Update(time);
	}
};


void Pattern01::Draw()
{
	for (unsigned int i = 0; i < bulletNumber; i++)
	{
		this->bullet[i]->Draw();
		this->bullet[i + BULLET_JUMP]->Draw();
		this->bullet[i + 2 * BULLET_JUMP]->Draw();
	}
};


void Pattern01::SetScale( float const & scale, float const & frac_time )
{
	//this->scale = true;
	//this->scale_frac = scale /  frac_time;
};