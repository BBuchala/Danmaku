#include "Pattern02.h"

Pattern02::~Pattern02()
{
	if (bullet1 && bullet2)
	{
		for (int i = 0; i < BULLET_NUMBER; i++)
		{
			delete bullet1[i];
			delete bullet2[i];
		}
		delete[] bullet1;
		delete[] bullet2;
	}
};


void Pattern02::Initialize(LPDIRECT3DDEVICE9 device)
{
	this->bulletNumber = 1;
	this->elapsedTime = 0.0f;
	this->bullet1 = new EnemyBulletSpiral * [BULLET_NUMBER];
	this->bullet2 = new EnemyBulletSpiral * [BULLET_NUMBER];
	for (int i = 0; i < BULLET_NUMBER; i++)
	{
		bullet1[i] = new EnemyBulletSpiral( 400, 300, 180 );
		bullet2[i] = new EnemyBulletSpiral( 400, 300, 180 );
		std::string file = Sprite::GetFilePath( "Bullet0", 3, "png" );
		bullet1[i]->Initialize( device, file, BULLET_WIDTH, BULLET_HEIGHT );
		bullet2[i]->Initialize( device, file, BULLET_WIDTH, BULLET_HEIGHT );
		bullet1[i]->SetParameters( 0, 12 );
		bullet2[i]->SetParameters( 0, 12 );
		bullet2[i]->Rotate( D3DXToRadian(180) );
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
		this->bullet1[i]->Update(time);
		this->bullet2[i]->Update(time);
	}
};


void Pattern02::Draw()
{
	for (unsigned int i = 0; i < bulletNumber; i++)
	{
		this->bullet1[i]->Draw();
		this->bullet2[i]->Draw();
	}
};