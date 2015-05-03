#include "PPattern.h"


PPattern::PPattern(void): elapsedTime(0.0f)
{
}


PPattern::~PPattern(void)
{
	for ( PBulletQue::const_iterator it = bullet.begin(); it != bullet.end(); it++ )
	{
		delete *it;
	}
}

void PPattern::Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position)
{
	this->device = device;
	this->position = position;
}

void PPattern::Draw( RECT const & rect )
{
	for ( PBulletQue::const_iterator it = bullet.begin(); it != bullet.end(); it++ )
	{
		(*it)->Draw(rect);
	}
};

//void PPattern::SetPosition(D3DXVECTOR2 const & pos)
//{
//	this->position = pos;
//};

void PPattern::Update(float const time, bool pressedKey, D3DXVECTOR2 const & playerPos)
{
	for ( PBulletQue::const_iterator it = bullet.begin(); it != bullet.end(); it++ )
	{
		(*it)->Update(time);
	}
}