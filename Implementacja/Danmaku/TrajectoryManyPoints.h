#pragma once

#include "Trajectory.h"
#include <vector>

class TrajectoryManyPoints: public Trajectory
{
protected:
	// definicja wektora punkt�w
	typedef std::vector<D3DXVECTOR2>	PointVector;
	// zbi�r pubkt�w
	PointVector	point;
	// ca�kowita d�ugo�� drogi
	float totalLength;

public:
	// Konstruktory
	TrajectoryManyPoints();
	TrajectoryManyPoints(std::vector<D3DXVECTOR2> const & pointVector);
	// Destruktor
	virtual ~TrajectoryManyPoints();

	/* ==== Metody przeci��one z Trajectory ====== */
	// ustawienie punktu pocz�tkowego
	void SetStartPoint( D3DXVECTOR2 const & startPoint ) override;
	// Przekszta�cenia afiniczne
	void Translate( D3DXVECTOR2 const & translate ) override;
	virtual void Scale( float const scale ) override;
	void Rotate( float const theta ) override;

	// obliczenie d�ugo�ci drogi
	virtual void CalculateLength() = 0;
	// Dodanie nowego punktu do zbioru
	virtual void AddPoint(D3DXVECTOR2 const & point);
};
