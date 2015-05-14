#include "PlayerPattern05.h"


PlayerPattern05::PlayerPattern05(void)
{
}


PlayerPattern05::~PlayerPattern05(void)
{
}

void PlayerPattern05::Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position)
{
	PPattern::Initialize(device, position);
	leftShift = D3DXVECTOR2(20,15);
	rightShift = D3DXVECTOR2(-20,15);
};

void PlayerPattern05::Update(float const time, D3DXVECTOR2 const & playerPos)
{
	if (this->elapsedTime >= 0.07000f)
		{
			if (this->isKeyPressed)
				Add(playerPos);
			this->elapsedTime = 0;
		}
		this->elapsedTime += time;


	for ( PBulletQue::const_iterator it = bullet.begin(); it != bullet.end(); it++ )
	{
		(*it)->Update(time);
	}
}

void PlayerPattern05::Add(D3DXVECTOR2 const & playerPos)
{
	for (int i = 0; i < 2; i++ )
	{
		PlayerBullet * newBullet;
		PlayerBullet * newBullet2;
		PlayerBullet * newBullet3;
		PlayerBullet * newBullet4;

		newBullet = new PlayerBullet( 1000.0f, 150 );
		newBullet2 = new PlayerBullet( 800.0f, 100 );
		newBullet3 = new PlayerBullet( 600.0f, 50 );
		newBullet4 = new PlayerBullet( 600.0f, 50 );

		if ( bullet.size() == 0 )
		{
			std::string file = Sprite::GetFilePath( "PlayerBullet3","png");
			newBullet->InitializeSprite( device, file );

			file = Sprite::GetFilePath( "PlayerBullet2","png");
			newBullet2->InitializeSprite( device, file );

			file = Sprite::GetFilePath( "PlayerBullet4","png");
			newBullet3->InitializeSprite( device, file );

			file = Sprite::GetFilePath( "PlayerBullet","png");
			newBullet4->InitializeSprite( device, file );
		}
		else
		{
			newBullet->SetSprite( bullet[0]->GetSprite() );
			newBullet2->SetSprite( bullet[1]->GetSprite() );
			newBullet3->SetSprite( bullet[2]->GetSprite() );
			newBullet4->SetSprite( bullet[3]->GetSprite() );
		}
		
		newBullet->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::HALF_LENGTH );
		newBullet2->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::HALF_LENGTH );
		newBullet3->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::HALF_LENGTH );
		newBullet4->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::HALF_LENGTH );

		switch (i % 2)
		{
			case 0:
				newBullet->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, playerPos - leftShift, D3DXToRadian(90) ) ) );
				newBullet2->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, playerPos - rightShift, D3DXToRadian(85) ) ) );
				newBullet3->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, playerPos + leftShift, D3DXToRadian(-90) ) ) );
				newBullet4->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, playerPos - rightShift, D3DXToRadian(80) ) ) );
				break;
			case 1:
				newBullet->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, playerPos - rightShift, D3DXToRadian(90) ) ) );
				newBullet2->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, playerPos - leftShift, D3DXToRadian(95) ) ) );
				newBullet3->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, playerPos + rightShift, D3DXToRadian(-90) ) ) );
				newBullet4->SetTrajectory( TrajectoryPtr(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, playerPos - leftShift, D3DXToRadian(100) ) ) );
				break;

			default:
				break;
		}
		this->bullet.push_back( newBullet );
		this->bullet.push_back( newBullet2 );
		this->bullet.push_back( newBullet3 );
		this->bullet.push_back( newBullet4 );
	}
}