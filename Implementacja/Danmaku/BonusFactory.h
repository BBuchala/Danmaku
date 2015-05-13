#pragma once

#include "Bonus.h"
#include <map>

class BonusFactory
{
	typedef Bonus * (*CreateBonusCallback)( D3DXVECTOR2 const & position, float const value, float const speed );
	typedef std::map<Bonuses, CreateBonusCallback> CallbackMap;

	// mapa wywo³añ
	CallbackMap callbacks_;

	// instancja fabryki
	static BonusFactory * pInstance_;

public:
	// zwrócenie instancji fabryki
	static BonusFactory & Instance();

	// zwrócenie nowego obiektu bonusu
	Bonus * const CreateBonus( Bonuses const bonus, D3DXVECTOR2 const & position, float const value = 1.0f, float const speed = 100.0f );

	// zarejestrowanie nowego bonusu
	bool RegisterBonus( Bonuses const bonus, CreateBonusCallback createFn );

	// usuniêcie bonusu z mapy
	bool UnregisterBonus( Bonuses const bonus );
};
