#include "EPattern.h"

EPattern::EPattern(float const activationTime) : _activationTime(activationTime), _activated(false)
{
	_translate = D3DXVECTOR2(0.0f, 0.0f);
	_rotate = 0.0f;
	_scale = 1.0f;
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

// ----- Translate ------------------------------------------------------------------------------
void EPattern::Translate(D3DXVECTOR2 const & translate)
{
	_translate += translate;
};

// ----- Scale ----------------------------------------------------------------------------------
void EPattern::Scale(float const scale)
{
	_scale *= scale;
};

// ----- Rotate ----------------------------------------------------------------------------------
void EPattern::Rotate(float const rotate)
{
	_rotate += rotate;
};

// ----- Set Translation --------------------------------------------------------------------------
void EPattern::SetTranslation(D3DXVECTOR2 const & translate)
{
	_translate = translate;
};

// ----- Set Scale --------------------------------------------------------------------------------
void EPattern::SetScale(float const scale)
{
	_scale = scale;
};

// ----- Set Rotation------------------------------------------------------------------------------
void EPattern::SetRotation(float const rotate)
{
	_rotate = rotate;
};
