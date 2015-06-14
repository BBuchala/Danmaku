#pragma once

#include <d3d9.h>
#include <deque>

#include "Bullet.h"
#include "TrajectoryFactory.h"

/// <summary>
/// Szablon wzoru pocisków
/// </summary>
class IPattern
{
protected:
	typedef std::deque<Bullet*> BulletQue;

public:
	virtual ~IPattern() = 0 {};

	// zainicjalizowanie patternu
	virtual void SetPositionPtr( D3DXVECTOR2 * const position ) = 0;

	// zaktualizowanie stanu
	virtual void Update(float const time) = 0;

	// narysowanie pocisków
	virtual void Draw(RECT const & rect) = 0;

	// dodanie nowego pocisku
	virtual void AddBullet() = 0;
};