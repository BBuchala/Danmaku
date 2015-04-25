#include "CPattern.h"

CPattern::CPattern() : elapsedTime(0.0f)
{
};


CPattern::~CPattern()
{
	for ( EBulletQue::const_iterator it = bullet.begin(); it != bullet.end(); it++ )
	{
		delete *it;
	}
};


void CPattern::Initialize(LPDIRECT3DDEVICE9 device)
{
	this->device = device;
};


void CPattern::Draw( short const & x, short const & y, short const & width, short const & height )
{
	for ( EBulletQue::const_iterator it = bullet.begin(); it != bullet.end(); it++ )
	{
		D3DXVECTOR2 center = (*it)->GetCenterPoint();
		D3DXVECTOR2 diffPos = center - (*it)->GetPosition();
		// je�eli ca�y sprajt 
		if (center.x + diffPos.x < x			||	// jest za lew� �cian� lub
			center.y + diffPos.y < y			||	// jest za g�rn� �cian� lub
			center.x - diffPos.x > x + width	||	// jest za praw� �cian� lub
			center.y - diffPos.y > y + height		// jest za doln� �cian�
			)
		{
			continue;	// nie rysuj go
		}
		// jak widac to rysuj, dozo~
		(*it)->Draw();
	}
};