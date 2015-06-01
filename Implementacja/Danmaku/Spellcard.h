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

	bool wasBombUsed;

public:
	Spellcard(std::string const & name, float time, UINT startBonus);
	~Spellcard();

	void Update(float time, D3DXVECTOR2 const & position);
	void Initialize(D3DXVECTOR2 const & position);
	void Draw(RECT const & rect);
	
	void AddPattern(std::string const & key, EPattern * const epattern);


	EPattern * GetPattern(std::string const & key);
	PatternMap * GetPatterns();

	void Activate(D3DXVECTOR2 const & position);
	void SetPosition(D3DXVECTOR2 const * position);
	void BombUsed();

	inline bool IsSpellcardFinished() const
	{
		return time_ == 0.0f ? true : false;
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
