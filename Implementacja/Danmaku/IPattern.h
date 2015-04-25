#pragma once

#include <d3d9.h>
#include <deque>

#include "EnemyBullet.h"
#include "TrajectoryFactory.h"

class IPattern
{
protected:
	typedef std::deque<EnemyBullet*> EBulletQue;

public:
	virtual ~IPattern() = 0 {};

	// zainicjalizowanie patternu
	virtual void Initialize( LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position ) = 0;

	// zaktualizowanie stanu
	virtual void Update(float const time) = 0;

	// narysowanie pocisków
	virtual void Draw( short const x, short const y, short const width, short const height ) = 0;

	// pobranie wszystkich pocisków
	virtual EBulletQue const & GetBullets() const = 0;
};