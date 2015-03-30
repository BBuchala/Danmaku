#include "GameObject.h"

GameObject::GameObject(float const & x, float const & y)
{
	this->setPosition(x, y);
};

GameObject::GameObject(float const & x, float const & y, float const & speed)
{
	this->setPosition(x, y);
	this->speed = speed < 0 ? 0 : speed;
};


GameObject::~GameObject()
{
	if (this->sprite)
		delete this->sprite;
};


bool GameObject::Initialize(LPDIRECT3DDEVICE9 device, char const * file, int const & width, int const & height)
{
	if (!this->sprite)
	{
		this->sprite = new Sprite();
		if ( !this->sprite->Initialize(device, file, width, height) )
		{
			return false;
		}
	}
	return true;
};


void GameObject::Draw()
{
	if (this->sprite)
		this->sprite->Draw(this->position);
};


void GameObject::Update(float const & time)
{

};


void GameObject::setPosition(float const & x, float const & y)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = 0;
};