#include "EPatternFactory.h"

EPatternFactory * EPatternFactory::pInstance_ = 0;

EPatternFactory & EPatternFactory::Instance()
{
	if (!pInstance_)
	{
		pInstance_ = new EPatternFactory();
	}
	return *pInstance_;
};

EPattern * const EPatternFactory::Create( Pattern const pattern, float const par1, float const par2, float const number, float const activationTime )
{
	CallbackMap::const_iterator it = callbacks_.find( pattern );
	if ( it == callbacks_.end())
	{
		throw std::runtime_error("Nieznany identyfikator wzoru.");
	}
	return (it->second)(par1, par2, number, activationTime);
};

bool EPatternFactory::Register( Pattern const pattern, CreateEPatternCallback createFn )
{
	return this->callbacks_.insert( CallbackMap::value_type( pattern, createFn )).second;
};


bool EPatternFactory::Unregister( Pattern const pattern )
{
	return this->callbacks_.erase( pattern ) == 1;
};
