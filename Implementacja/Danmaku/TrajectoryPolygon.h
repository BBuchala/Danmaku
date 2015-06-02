#pragma once

#include <vector>

#include "TrajectoryManyPoints.h"
#include "Vector.h"

class TrajectoryPolygon: public TrajectoryManyPoints
{
protected:
	// zbiór d³ugoœci wektorów
	typedef std::vector<float>	DistanceVector;
	DistanceVector				distanceBetweenPoint;

public:
	// Konstruktory
	TrajectoryPolygon();
	TrajectoryPolygon(std::vector<D3DXVECTOR2> const & pointVector);

	// zwrócenie pozycji na linii w postaci wektora
	D3DXVECTOR2 GetPosition( float const dis ) override;
	// Dodanie punktu i uzupe³nienie listy d³ugoœci odcinków
	void AddPoint(D3DXVECTOR2 const & point) override;
	
	// obliczenie d³ugoœci linii ³amanej
	void CalculateLength() override;
	// metoda skalowania uzwglêdniaj¹ca d³ugoœci odcinków
	void Scale( float const scale );
};

