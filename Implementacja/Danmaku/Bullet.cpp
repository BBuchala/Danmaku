#include "Bullet.h"

Bullet::Bullet( float const & x, float const & y ) : GameObject(x, y)
{
};


Bullet::~Bullet()
{
};


bool Bullet::Initialize(LPDIRECT3DDEVICE9 device, std::string const & file, int const & width, int const & height)
{
	return GameObject::Initialize(device, file, width, height);
};


bool Bullet::Initialize(LPDIRECT3DDEVICE9 device, std::vector<std::string> const & fileVect, int const & width, int const & height)
{
	return GameObject::Initialize(device, fileVect, width, height);
};