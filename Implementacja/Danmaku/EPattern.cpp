#include "EPattern.h"

EPattern::EPattern() : _elapsedTime(0.0f), _bulletTime(0.0f)
{
};


EPattern::~EPattern()
{
	for ( EBulletQue::const_iterator it = _bullet.begin(); it != _bullet.end(); it++ )
	{
		delete *it;
	}
};


void EPattern::Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position )
{
	this->_device = device;
	this->_position = position;
};


void EPattern::InitializeBullets(std::string bulletImage, float bulletSpeed, BYTE bulletWidth, BYTE bulletHeight, Hitbox::Shape hitboxShape, Hitbox::Size hitboxSize)
{
	_bulletImage = bulletImage;
	_bulletSpeed = bulletSpeed;
	_bulletWidth = bulletWidth;
	_bulletHeight = bulletHeight;
	_hitboxShape = hitboxShape;
	_hitboxSize = hitboxSize;
};


void EPattern::Draw( RECT const & rect )
{
	for ( EBulletQue::const_iterator it = _bullet.begin(); it != _bullet.end(); it++ )
	{
		(*it)->Draw(rect);
	}
};


void EPattern::SetPosition(D3DXVECTOR2 const & pos)
{
	this->_position = pos;
};