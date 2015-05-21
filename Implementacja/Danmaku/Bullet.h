/* ======================================================== *\
 *  @Bullet.h
 *  @Opis: Pocisk, który porusza siê po elipsie
 *  @Utworzona: 22.03.2015 13:48
 *  @Autor: Mateusz Forczmañski
\* ======================================================== */

#pragma once

#include "GameObject.h"
#include "TrajectoryFactory.h"

#include <memory>


class Bullet : public GameObject
{
	// definicja wspólnego wskaŸnika na tor
	typedef std::shared_ptr<Trajectory> TrajectoryPtr;
	TrajectoryPtr trajectory;

	float distance;

public:
	Bullet( float const speed  = 0.0f, float const acc = 0.0f );
	Bullet( D3DXVECTOR2 const & position, float const speed = 0.0f, float const acc = 0.0f);
	Bullet( Bullet const & bullet );
	virtual ~Bullet();

	void SetTrajectory( Road const trajectory, D3DXVECTOR2 const & position, float const a, float const b = 0 );
	void SetTrajectory( Trajectory * const trajectory );
	void SetTrajectory( TrajectoryPtr const & trajectory );
	void SetDistance( float const distance );

	inline TrajectoryPtr const GetTrajectory() const
	{
		return trajectory;
	}

	void Update(float const time) override;

};



