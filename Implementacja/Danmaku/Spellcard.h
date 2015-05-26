#pragma once

#include "EPattern.h"

class Spellcard
{
protected:
	float	time_;
	UINT	startBonus_;
	std::string name_;

	typedef std::map<std::string, EPattern*> PatternMap;
	PatternMap sourcePattern_;
	PatternMap pattern_;

	float _interval;
	float _elapsedTime;

	D3DXVECTOR2 const * position_;

public:
	Spellcard(std::string const & name, float time, UINT startBonus)
			: name_(name), time_(time), startBonus_(startBonus), _interval(1.0f), _elapsedTime(0.0f)
	{
	}

	~Spellcard()
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


	void Update(float time, D3DXVECTOR2 const & position)
	{
		if ( time_ - time >= 0.0000f)
			time_ -= time;
		else
			time_ = 0.0f;

		if (startBonus_ - 20000 * time >= 0)
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

	void Draw(RECT const & rect)
	{
		for (PatternMap::const_iterator it = pattern_.begin(); it != pattern_.end(); ++it)
		{
			(*it).second->Draw(rect);
		}
	}


	inline bool IsSpellcardFinished() const
	{
		return time_ == 0.0f ? true : false;
	}

	void AddPattern(std::string const & key, EPattern * const epattern)
	{
		sourcePattern_[key] = epattern;
	}


	EPattern * GetPattern(std::string const & key)
	{
		return sourcePattern_[key];
	}

	PatternMap * GetPatterns()
	{
		if (pattern_.size() != 0)
			return &pattern_;
		else
			return nullptr;
	}


	void Initialize(D3DXVECTOR2 const & position)
	{
		for (PatternMap::const_iterator it = sourcePattern_.begin(); it != sourcePattern_.end(); ++it)
		{
			(*it).second->Initialize(position);
		}
	}


	void Activate(D3DXVECTOR2 const & position)
	{
		for (PatternMap::const_iterator it = sourcePattern_.begin(); it != sourcePattern_.end(); ++it)
		{
			(*it).second->ForceActivate(position);
		}
	}


	void SetPosition(D3DXVECTOR2 const * position)
	{
		this->position_ = position;
	}

	inline const std::string & GetName() const
	{
		return name_;
	}

	inline const float GetTime() const
	{
		return time_;
	}

	inline const UINT GetBonus() const
	{
		return startBonus_;
	}
};
