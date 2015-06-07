#pragma once

#include "TrajectoryFactory.h"
#include "TrajectorySingle.h"
#include "Vector.h"

class TrajectorySpiral : public TrajectorySingle
{
protected:
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
	void Translate( D3DXVECTOR2 const & translate ) override;
	void Scale( float const scale ) override;
	void Rotate( float const theta ) override;

	void SetCenterPoint( D3DXVECTOR2 const & center ) override;
};
