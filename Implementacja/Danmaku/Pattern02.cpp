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


void Pattern02::Initialize(LPDIRECT3DDEVICE9 device)
{
	this->bulletNumber = 1;
	this->elapsedTime = 0.0f;
	this->bullet = new EnemyBullet * [BULLET_NUMBER];
	D3DXVECTOR2 center( 400, 300 );
	for (int i = 0; i < BULLET_NUMBER; i++)
	{
		bullet[i] = new EnemyBullet( D3DXToRadian(180.0f) );
		std::string file = Sprite::GetFilePath( "Bullet0", 3, "png" );
		bullet[i]->Initialize( device, file, BULLET_WIDTH, BULLET_HEIGHT );
		bullet[i]->SetTrajectory( Road::SPIRAL, center, 0, 12 );
	}
};


void Pattern02::Update(float const & time)
{
	this->elapsedTime += time;
	// Nowe pociski
	if (bulletNumber < BULLET_NUMBER)
	{
		if (this->elapsedTime >= 0.100000f)
		{
			bulletNumber++;
			this->elapsedTime = 0;
		}
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