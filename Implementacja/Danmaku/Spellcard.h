#pragma once

#include "EPattern.h"

/// <summary>
/// Klasa odpowiadaj¹ca za obs³ugê ataków bossa
/// </summary>
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

	/// <summary>
	/// Czy spellcard zakoñczy³ swe dzia³anie.
	/// </summary>
	/// <returns></returns>
	inline bool IsSpellcardFinished() const
	{
		return time_ == 0.0f ? true : false;
	}

	/// <summary>
	/// Zwrócenie nazwy spellcardu.
	/// </summary>
	/// <returns></returns>
	inline const std::string & GetName() const
	{
		return name_;
	}

	/// <summary>
	/// Zwrócenie aktualnego czasu trwania.
	/// </summary>
	/// <returns></returns>
	inline const float GetTime() const
	{
		return time_;
	}

	/// <summary>
	/// Zwrócenie bonusu.
	/// </summary>
	/// <returns></returns>
	inline const UINT GetBonus() const
	{
		return startBonus_;
	}
};
