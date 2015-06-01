#pragma once

#include "Boss.h"

Boss::Boss( D3DXVECTOR2 const & position, USHORT const life, std::string const & name )
		: GameObject(position), isShooting_(true), waitTime_(3.0f), currentSc_(1), name_(name), MAX_LIFE(life), life_(life), scId(1)
{
}

Boss::~Boss()
{
}

void Boss::Draw(RECT const & rect)
{
	GameObject::Draw(rect);
}

void Boss::Update( float const time )
{
	GameObject::Update(time);
	if (isShooting_)
	{
		if (_spellcard[currentSc_])
			if (_spellcard[currentSc_]->IsSpellcardFinished())
			{
				//delete _spellcard[currentSc_++];
			}
	}
}

Spellcard * Boss::GetSpellcard()
{
	return _spellcard[currentSc_];
}

void Boss::TakeDamage( USHORT const damage )
{
	if (life_ - damage < 0  )
		life_ = 0;
	else
		life_ -= damage;
}

void Boss::SetIsShooting(bool const isShooting)
{
	isShooting_ = isShooting;
}

void Boss::AddSpellcard(Spellcard * const spellcard)
{
	_spellcard[scId] = spellcard;
	_spellcard[scId]->Activate(this->GetCenterPoint());
	scId++;
}

bool Boss::InitializePatterns(D3DXVECTOR2 const & position)
{
	for (SpellcardMap::const_iterator it = _spellcard.begin(); it != _spellcard.end(); ++it)
	{
		(*it).second->Initialize(this->GetCenterPoint());
	}
	return true;
};