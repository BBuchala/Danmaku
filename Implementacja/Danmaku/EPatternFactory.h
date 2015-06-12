#pragma once

#include "EPattern.h"
#include <map>


/// <summary>
/// Fabryka wrogich wzorów pocisków
/// </summary>
class EPatternFactory
{
	typedef EPattern * (*CreateEPatternCallback)( float const par1, float const par2, float const number, float const activationTime );
	typedef std::map<Pattern, CreateEPatternCallback> CallbackMap;

	// mapa wywo³añ
	CallbackMap callbacks_;

	// instancja fabryki
	static EPatternFactory * pInstance_;

public:
	// zwrócenie instancji fabryki
	static EPatternFactory & Instance();

	// zwrócenie nowego obiektu bonusu
	EPattern * const Create( Pattern const pattern, float const par1, float const par2, float const number = 1.0f, float const activationTime = 1.0f );

	// zarejestrowanie nowego bonusu
	bool Register( Pattern const bonus, CreateEPatternCallback createFn );

	// usuniêcie bonusu z mapy
	bool Unregister( Pattern const bonus );
};

