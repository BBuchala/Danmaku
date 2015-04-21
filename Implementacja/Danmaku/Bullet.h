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
	Bullet( float const & speed );
	Bullet( D3DXVECTOR2 const & position, float const & speed = 0 );
	virtual ~Bullet();

	bool Initialize(LPDIRECT3DDEVICE9 device, std::string const & file, int const & width, int const & height) override;
	bool Initialize(LPDIRECT3DDEVICE9 device, std::vector<std::string> const & fileVect, int const & width, int const & height) override;

	void SetTrajectory( Road const & trajectory, D3DXVECTOR2 const & position, float const & a, float const & b = 0 );
	void SetTrajectory( Trajectory * trajectory );
	void SetTrajectory( TrajectoryPtr trajectory );
	void SetDistance( float const & distance );

	inline Trajectory * GetTrajectory() const
	{
		return trajectory.get();
	}

	void Update(float const & time) override;

};



