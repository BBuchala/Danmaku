#include "EPatternFactory.h"

EPatternFactory * EPatternFactory::pInstance_ = 0;

/// <summary>
/// Utworzenie singletonu fabryki.
/// </summary>
/// <returns></returns>
EPatternFactory & EPatternFactory::Instance()
{
	if (!pInstance_)
	{
		pInstance_ = new EPatternFactory();
	}
	return *pInstance_;
};

/// <summary>
/// Zwrócenie nowego obiektu wzoru.
/// </summary>
/// <param name="pattern">Rodzaj wzoru.</param>
/// <param name="par1">Pierwszy parametr.</param>
/// <param name="par2">Drugi parametr.</param>
/// <param name="number">Liczba wzorów.</param>
/// <param name="activationTime">Czas aktywacji.</param>
/// <returns></returns>
EnemyPattern * const EPatternFactory::Create( Pattern const pattern, float const par1, float const par2, float const number, float const activationTime )
{
	CallbackMap::const_iterator it = callbacks_.find( pattern );
	if ( it == callbacks_.end())
	{
		throw std::runtime_error("Nieznany identyfikator wzoru.");
	}
	return (it->second)(par1, par2, number, activationTime);
};

/// <summary>
/// Zarejestrowanie nowej wzoru.
/// </summary>
/// <param name="wzoru">Id rodzaju wzoru.</param>
/// <param name="createFn">Funkcja tworz¹ca nowy obiekt.</param>
/// <returns></returns>
bool EPatternFactory::Register( Pattern const pattern, CreateEPatternCallback createFn )
{
	return this->callbacks_.insert( CallbackMap::value_type( pattern, createFn )).second;
};


/// <summary>
/// Usuniêcie wzoru z mapy.
/// </summary>
/// <param name="pattern">Id rodzaju wzoru.</param>
/// <returns></returns>
bool EPatternFactory::Unregister( Pattern const pattern )
{
	return this->callbacks_.erase( pattern ) == 1;
};
