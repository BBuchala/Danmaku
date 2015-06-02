#pragma once

#include "TrajectoryFactory.h"
#include "Vector.h"

namespace
{
	class TrajectorySpiral : public TrajectorySingle
	{
		/* wspó³czynnik obrotu spirali */
		float a;

		/* odleg³oœæ miêdzy kolejnymi obrotami */
		float b;

		/* punkt centralny spirali */
		D3DXVECTOR2 center;

	public:
		TrajectorySpiral( D3DXVECTOR2 const & center, float const a, float const b );
		~TrajectorySpiral();

	private:
		void SetParameters( float const a, float const b );

	public:
		/* ==== Przeci¹¿one interfejsy ==== */
		D3DXVECTOR2 GetPosition( float const theta ) override;
		void Translate( D3DXVECTOR2 const & translate ) override;
		void Scale( float const scale ) override;
		void Rotate( float const theta ) override;

		void SetCenterPoint( D3DXVECTOR2 const & center ) override;
	};

	// zarejestrowanie toru w Fabryce
	TrajectorySingle * CreateTrajectorySpiral( D3DXVECTOR2 const & center, float const a, float const b )
	{
		return new TrajectorySpiral( center, a, b );
	}
	Road const tracId = Road::SPIRAL;
	bool const registrered = TrajectoryFactory::Instance().RegisterTrajectory( tracId, CreateTrajectorySpiral );
};
