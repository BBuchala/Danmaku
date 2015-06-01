#pragma once

#include "Spellcard.h"
typedef std::map<std::string, EPattern*> PatternMap;

Spellcard::Spellcard(std::string const & name, float time, UINT startBonus):
	name_(name), time_(time), startBonus_(startBonus), _interval(1.0f), _elapsedTime(0.0f), wasBombUsed(false)
{
};

Spellcard::~Spellcard()
{
	for (PatternMap::const_iterator it = sourcePattern_.begin(); it != sourcePattern_.end(); ++it)
	{
		delete (*it).second;
	}
	for (PatternMap::const_iterator it = pattern_.begin(); it != pattern_.end(); ++it)
	{
		delete (*it).second;
	}
}

void Spellcard::Initialize(D3DXVECTOR2 const & position)
{
	for (PatternMap::const_iterator it = sourcePattern_.begin(); it != sourcePattern_.end(); ++it)
	{
		(*it).second->Initialize(position);
	}
}

void Spellcard::Draw(RECT const & rect)
{
	for (PatternMap::const_iterator it = pattern_.begin(); it != pattern_.end(); ++it)
	{
		(*it).second->Draw(rect);
	}
}

void Spellcard::Update(float time, D3DXVECTOR2 const & position)
{
	if ( time_ - time >= 0.0000f)
		time_ -= time;
	else
		time_ = 0.0f;

	if (startBonus_ - 20000 * time >= 0 && !wasBombUsed)
		startBonus_ -= 20000 * time;
	else
		startBonus_ = 0;

	_elapsedTime += time;
	if (_elapsedTime >= _interval)
	{
		if (_interval - time >= 0.1000f)
		{
			_interval -= time;		// zmniejszenie odtêpu miêdzy eklipsami
		}
		for (PatternMap::const_iterator it = sourcePattern_.begin(); it != sourcePattern_.end(); ++it)
		{
			static USHORT id = 1;
			this->pattern_[std::to_string(id)] = (*it).second->Clone();
			// Nowa pozycja specjalnie dla Remi :3
			D3DXVECTOR2 newPosition = *position_;
			newPosition.x -= 24.0f;
			newPosition.y -= 4.0f;
			this->pattern_[std::to_string(id)]->StartBullets(newPosition);
			++id;
		}
		_elapsedTime = 0.0f;
	}
	for (PatternMap::const_iterator it = pattern_.begin(); it != pattern_.end(); ++it)
	{
		(*it).second->Rotate(0.5f * time);
		(*it).second->Update(time, position);
	}
}

void Spellcard::AddPattern(std::string const & key, EPattern * const epattern)
{
	sourcePattern_[key] = epattern;
}

EPattern * Spellcard::GetPattern(std::string const & key)
{
	return sourcePattern_[key];
}

PatternMap * Spellcard::GetPatterns()
{
	if (pattern_.size() != 0)
		return &pattern_;
	else
		return nullptr;
}

void Spellcard::Activate(D3DXVECTOR2 const & position)
{
	for (PatternMap::const_iterator it = sourcePattern_.begin(); it != sourcePattern_.end(); ++it)
	{
		(*it).second->ForceActivate(position);
	}
}

void Spellcard::SetPosition(D3DXVECTOR2 const * position)
{
	this->position_ = position;
}

void Spellcard::BombUsed()
{
	this->wasBombUsed = true;
}