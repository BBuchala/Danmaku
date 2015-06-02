#pragma once

#include "Trajectory.h"
#include <vector>

class TrajectoryManyPoints: public Trajectory
{
protected:
	// definicja wektora punktów
	typedef std::vector<D3DXVECTOR2>	PointVector;
	// zbiór pubktów
	PointVector	point;
	// ca³kowita d³ugoœæ drogi
	float totalLength;

public:
	// Konstruktory
	TrajectoryManyPoints();
	TrajectoryManyPoints(std::vector<D3DXVECTOR2> const & pointVector);
	// Destruktor
	virtual ~TrajectoryManyPoints();

	/* ==== Metody przeci¹¿one z Trajectory ====== */
	// ustawienie punktu pocz¹tkowego
	void SetStartPoint( D3DXVECTOR2 const & startPoint ) override;
	// Przekszta³cenia afiniczne
	void Translate( D3DXVECTOR2 const & translate ) override;
	virtual void Scale( float const scale ) override;
	void Rotate( float const theta ) override;

	// obliczenie d³ugoœci drogi
	virtual void CalculateLength() = 0;
	// Dodanie nowego punktu do zbioru
	virtual void AddPoint(D3DXVECTOR2 const & point);
};
