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

void PPattern::Initialize(D3DXVECTOR2 const & position)
{
	this->position = position;
}

void PPattern::Draw( RECT const & rect )
{
	for ( PBulletQue::const_iterator it = bullet.begin(); it != bullet.end(); it++ )
	{
		(*it)->Draw(rect);
	}
};


void PPattern::Update(float const time, D3DXVECTOR2 const & position)
{
	for ( PBulletQue::const_iterator it = bullet.begin(); it != bullet.end(); it++ )
	{
		(*it)->Update(time);
	}
};


void PPattern::SetKeyPressed(bool isKeyPressed)
{
	this->isKeyPressed = isKeyPressed;
};

