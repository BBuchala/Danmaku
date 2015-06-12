#pragma once

#include "EPattern.h"
#include <map>


/// <summary>
/// Fabryka wrogich wzor�w pocisk�w
/// </summary>
class EPatternFactory
{
	typedef EPattern * (*CreateEPatternCallback)( float const par1, float const par2, float const number, float const activationTime );
	typedef std::map<Pattern, CreateEPatternCallback> CallbackMap;

	// mapa wywo�a�
	CallbackMap callbacks_;

	// instancja fabryki
	static EPatternFactory * pInstance_;

public:
	// zwr�cenie instancji fabryki
	static EPatternFactory & Instance();

	// zwr�cenie nowego obiektu bonusu
	EPattern * const Create( Pattern const pattern, float const par1, float const par2, float const number = 1.0f, float const activationTime = 1.0f );

	// zarejestrowanie nowego bonusu
	bool Register( Pattern const bonus, CreateEPatternCallback createFn );

	// usuni�cie bonusu z mapy
	bool Unregister( Pattern const bonus );
};

