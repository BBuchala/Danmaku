#include "EPattern.h"

EPattern::EPattern() : elapsedTime(0.0f)
{
};


EPattern::~EPattern()
{
	for ( EBulletQue::const_iterator it = bullet.begin(); it != bullet.end(); it++ )
	{
		delete *it;
	}
};


void EPattern::Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position )
{
	this->device = device;
	this->position = position;
};


void EPattern::Draw( RECT const & rect )
{
	for ( EBulletQue::const_iterator it = bullet.begin(); it != bullet.end(); it++ )
	{
		(*it)->Draw(rect);
	}
};


void EPattern::SetPosition(D3DXVECTOR2 const & pos)
{
	this->position = pos;
};