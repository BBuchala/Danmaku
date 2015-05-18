#pragma once

#include <memory>
#include "GraphicsDevice.h"

template <class K, class V>
class Resource
{
protected:
	typedef std::shared_ptr<V>			ResourcePtr;
	typedef std::map<K, ResourcePtr>	Map;
	Map _map;

public:
	virtual void Create(GraphicsDevice * const gDevice) = 0;

	bool Add(K const & key)
	{
		bool success = false;
		if (_map.find(key) == _map.end())
		{
			_map[key] = ResourcePtr(new V());
			success = true;
		}
		return success;
	}

	inline Map const & GetResources() const
	{
		return _map;
	}

	ResourcePtr operator[] (K const & rhs)
	{
		return _map[rhs];
	}
};
