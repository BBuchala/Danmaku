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
	this->bulletNumber = 0;
	this->elapsedTime = 0.0f;
	this->bullet = new EnemyBullet * [BULLET_NUMBER];
	D3DXVECTOR2 center( 400, 300 );
	for (int i = 0; i < BULLET_NUMBER; i++)
	{
		bullet[i] = new EnemyBullet( center, D3DXToRadian(180.0f) );
		std::string file = Sprite::GetFilePath( "Bullet0", 3, "png" );
		bullet[i]->Initialize( device, file, BULLET_WIDTH, BULLET_HEIGHT );
		bullet[i]->SetTrajectory( Road::SPIRAL, center, 6, 12 );
		bullet[i]->SetDistance( D3DXToRadian( i * 0.0f ) );
		bullet[i]->SetAcceleration( -0.05f );
	}
};


void Pattern02::Update(float const & time)
{
	// Nowe pociski
	if (bulletNumber < BULLET_NUMBER)
	{
		if (this->elapsedTime >= 0.20000f)
		{
			bulletNumber++;
			this->elapsedTime = 0;
		}
	}
	this->elapsedTime += time;

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