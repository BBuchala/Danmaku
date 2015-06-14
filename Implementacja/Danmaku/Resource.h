#pragma once

#include <memory>
#include "GraphicsDevice.h"

/// <summary>
/// Klasa przechowuj¹ca materia³y
/// </summary>
template <class K, class V>
class Resource
{
protected:
	typedef std::shared_ptr<V>			ResourcePtr;
	typedef std::map<K, ResourcePtr>	Map;
	Map _map;

public:
	virtual void Create(GraphicsDevice * const gDevice) = 0;

	/// <summary>
	/// Dodanie nowego elementu do mapy.
	/// </summary>
	/// <param name="key">The key.</param>
	/// <returns></returns>
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

	/// <summary>
	/// Zwrócenie materia³ów.
	/// </summary>
	/// <returns></returns>
	inline Map const & GetResources() const
	{
		return _map;
	}

	ResourcePtr operator[] (K const & rhs)
	{
		Map::const_iterator it = _map.find(rhs);
		if ( it != _map.end())
		{
			return _map[rhs];
		}
		return nullptr;
	}
};
