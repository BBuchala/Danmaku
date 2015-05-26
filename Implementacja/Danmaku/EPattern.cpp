#include "EPattern.h"

EPattern::EPattern(float const activationTime) : _activationTime(activationTime), _activated(false),
	 _bulletScale(1.0f), _bulletRotate(0.0f), _scaleStep(1.0f), _rotateStep(0.0f)
{
	_translate = D3DXVECTOR2(0.0f, 0.0f);
	_rotate = 0.0f;
	_scale = 1.0f;
};


EPattern::EPattern(EPattern const & pattern)
{
	_translate = pattern._translate;
	_rotate = pattern._rotate;
	_scale = pattern._scale;
	_activationTime = pattern._activationTime;
	_activated = pattern._activated;
	_bulletScale = pattern._bulletScale;
	_bulletRotate = pattern._bulletRotate;
	_scaleStep = pattern._scaleStep;
	_rotateStep = pattern._rotateStep;
	_position = pattern._position;
	_bulletSprite = pattern._bulletSprite;
	_bulletSpeed = pattern._bulletSpeed;
	_bulletAcc = pattern._bulletAcc;
	_bulletWidth = pattern._bulletWidth;
	_bulletHeight = pattern._bulletHeight;
	_hitboxShape = pattern._hitboxShape;
	_hitboxSize = pattern._hitboxSize;
	_scaleStep = pattern._scaleStep;
	_rotateStep = pattern._rotateStep;
	_bulletScale = pattern._bulletScale;
	_bulletRotate = pattern._bulletRotate;
	_number = pattern._number;
	_interval = pattern._interval;
};

EPattern::~EPattern()
{
	for ( EBulletQue::const_iterator it = _bullet.begin(); it != _bullet.end(); it++ )
	{
		delete *it;
	}
};


void EPattern::Initialize(D3DXVECTOR2 const & position )
{
	this->_position = position;
};


void EPattern::InitializeBullets(std::shared_ptr<Sprite> bulletSprite, float bulletSpeed, float bulletAcc,
								 BYTE bulletWidth, BYTE bulletHeight, Hitbox::Shape hitboxShape,
								 Hitbox::Size hitboxSize, float bulletScale, float bulletRotate)
{
	_bulletSprite = bulletSprite;
	_bulletSpeed = bulletSpeed;
	_bulletAcc = bulletAcc;
	_bulletWidth = bulletWidth;
	_bulletHeight = bulletHeight;
	_hitboxShape = hitboxShape;
	_hitboxSize = hitboxSize;
	_bulletScale = bulletScale;
	_bulletRotate = bulletRotate;
};


void EPattern::Update(float const time, D3DXVECTOR2 const & position)
{
	this->_scale += _scaleStep;
	this->_rotate += _rotateStep;
	for ( EBulletQue::const_iterator it = _bullet.begin(); it != _bullet.end(); it++ )
	{
		(*it)->Scale(_bulletScale);
		(*it)->Rotate(_bulletRotate);
		(*it)->Update(time);
	}
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


void EPattern::SetBulletScale(float scale)
{
	_bulletScale = scale;
};


void EPattern::SetBulletRotation(float rotate)
{
	_bulletRotate = rotate;
};


void EPattern::Activate(float const actTime, D3DXVECTOR2 const & position)
{
	if (!_activated && actTime >= _activationTime)
	{
		this->StartBullets(position);
		_activated = true;
	}
};