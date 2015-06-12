#include "BonusFactory.h"

BonusFactory * BonusFactory::pInstance_ = 0;

/// <summary>
/// Instances this instance.
/// </summary>
/// <returns></returns>
BonusFactory & BonusFactory::Instance()
{
	if (!pInstance_)
	{
		pInstance_ = new BonusFactory();
	}
	return *pInstance_;
};

/// <summary>
/// Creates the bonus.
/// </summary>
/// <param name="bonus">The bonus.</param>
/// <param name="position">The position.</param>
/// <param name="value">The value.</param>
/// <param name="speed">The speed.</param>
/// <returns></returns>
Bonus * const BonusFactory::CreateBonus( BonusType const bonus, D3DXVECTOR2 const & position, float const value, float const speed )
{
	CallbackMap::const_iterator it = callbacks_.find( bonus );
	if ( it == callbacks_.end())
	{
		throw std::runtime_error("Nieznany identyfikator bonusu.");
	}
	return (it->second)(position, value, speed);
};

/// <summary>
/// Registers the bonus.
/// </summary>
/// <param name="bonus">The bonus.</param>
/// <param name="createFn">The create function.</param>
/// <returns></returns>
bool BonusFactory::RegisterBonus( BonusType const bonus, CreateBonusCallback createFn )
{
	return this->callbacks_.insert( CallbackMap::value_type( bonus, createFn )).second;
};


/// <summary>
/// Unregisters the bonus.
/// </summary>
/// <param name="bonus">The bonus.</param>
/// <returns></returns>
bool BonusFactory::UnregisterBonus( BonusType const bonus )
{
	return this->callbacks_.erase( bonus ) == 1;
};
