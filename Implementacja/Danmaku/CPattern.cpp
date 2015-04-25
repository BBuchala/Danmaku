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
		// je¿eli ca³y sprajt 
		if (center.x + diffPos.x < x			||	// jest za lew¹ œcian¹ lub
			center.y + diffPos.y < y			||	// jest za górn¹ œcian¹ lub
			center.x - diffPos.x > x + width	||	// jest za praw¹ œcian¹ lub
			center.y - diffPos.y > y + height		// jest za doln¹ œcian¹
			)
		{
			continue;	// nie rysuj go
		}
		// jak widac to rysuj, dozo~
		(*it)->Draw();
	}
};