/* ======================================================== *\
 *  @Bullet.h
 *  @Opis: Pocisk, który porusza siê po elipsie
 *  @Utworzona: 22.03.2015 13:48
 *  @Autor: Mateusz Forczmañski
\* ======================================================== */

#pragma once

#include "GameObject.h"
#include "TrajectoryElipse.h"
#include "TrajectoryLine.h"
#include "TrajectorySpiral.h"

static enum Road
{
	LINE, ELIPSE, SPIRAL
};


class Bullet : public GameObject
{
	Trajectory * trajectory;

	float distance;


public:
	Bullet( float const & speed );
	Bullet( D3DXVECTOR2 const & position, float const & speed = 0 );
	virtual ~Bullet();

	bool Initialize(LPDIRECT3DDEVICE9 device, std::string const & file, int const & width, int const & height) override;
	bool Initialize(LPDIRECT3DDEVICE9 device, std::vector<std::string> const & fileVect, int const & width, int const & height) override;

	bool SetTrajectory( Road const & trajectory, D3DXVECTOR2 const & position, float const & a, float const & b = 0 );
	void SetDistance( float const & distance );

	inline Trajectory * GetTrajectory() const
	{
		return trajectory;
	}

	void Update(float const & time) override;

};



