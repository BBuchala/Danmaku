/* ======================================================== *\
 *  @Bullet.h
 *  @Opis: Pocisk, kt�ry porusza si� po elipsie
 *  @Utworzona: 22.03.2015 13:48
 *  @Autor: Mateusz Forczma�ski
\* ======================================================== */

#pragma once

#include "GameObject.h"
#include "TrajectoryFactory.h"

#include <memory>

/// <summary>
/// Pocisk, jaki mo�e zosta� wystrzelony
/// </summary>
class Bullet : public GameObject
{
	/// <summary>
	/// Definicja wsp�lnego wska�nika na tor
	/// </summary>
	typedef std::shared_ptr<Trajectory> TrajectoryPtr;
	/// <summary>
	/// Trajektoria pocisku
	/// </summary>
	TrajectoryPtr trajectory;
	/// <summary>
	/// Dystans jaki pocisk przeby�
	/// </summary>
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

	/// <summary>
	/// Zwraca trajektori�
	/// </summary>
	/// <returns></returns>
	inline TrajectoryPtr const GetTrajectory() const
	{
		return trajectory;
	}

	void Update(float const time) override;

};



