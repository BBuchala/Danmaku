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

	short scId;				// ID przypisywane spellcardom

public:
	Boss( D3DXVECTOR2 const & position, USHORT const life, std::string const & name );
	~Boss();

	void Draw(RECT const & rect);
	void Update( float const time );

	bool InitializePatterns(D3DXVECTOR2 const & position);

	void TakeDamage( USHORT const damage );

	Spellcard * GetSpellcard();

	void SetIsShooting(bool const isShooting);
	void AddSpellcard(Spellcard * const spellcard);

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
