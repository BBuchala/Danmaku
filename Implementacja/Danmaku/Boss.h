#pragma once

#include <map>

#include "GameObject.h"
#include "Spellcard.h"

class Boss: public GameObject
{
	USHORT const MAX_LIFE;
	USHORT life_;
	std::string name_;

	typedef std::map<short, Spellcard*>		SpellcardMap;
	typedef std::pair<short, Spellcard*>	SpellcardPair;
	SpellcardMap _spellcard;

	bool isShooting_;

	float waitTime_;		// czas oczekiwania pomiêdzy spellcardami
	short currentSc_;		// obecnie wystrzeliwany spellcard

public:
	Boss( D3DXVECTOR2 const & position, USHORT const life, std::string const & name )
		: GameObject(position), isShooting_(true), waitTime_(3.0f), currentSc_(1), name_(name),
		MAX_LIFE(life), life_(life)
	{
	}
	~Boss()
	{

	};

	void Draw(RECT const & rect)
	{
		GameObject::Draw(rect);
	}


	void Update( float const time )
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

	Spellcard * GetSpellcard()
	{
		return _spellcard[currentSc_];
	}


	void TakeDamage( USHORT const damage )
	{
		if (life_ - damage < 0  )
			life_ = 0;
		else
			life_ -= damage;
	}


	void SetIsShooting(bool const isShooting)
	{
		isShooting_ = isShooting;
	}


	void AddSpellcard(Spellcard * const spellcard)
	{
		static short scId = 1;
		_spellcard[scId] = spellcard;
		_spellcard[scId]->Activate(this->GetCenterPoint());
		scId++;
	}

	bool InitializePatterns(D3DXVECTOR2 const & position)
	{
		for (SpellcardMap::const_iterator it = _spellcard.begin(); it != _spellcard.end(); ++it)
		{
			(*it).second->Initialize(this->GetCenterPoint());
		}
		return true;
	};

	inline bool IsAlive() const
	{
		return life_ == 0 ? false : true;
	}

	inline const std::string & GetName() const
	{
		return this->name_;
	}

	inline const USHORT GetLife() const
	{
		return life_;
	}

	inline const USHORT GetMaxLife() const
	{
		return MAX_LIFE;
	}
};
