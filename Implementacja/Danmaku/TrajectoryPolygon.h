#pragma once

#include <vector>

#include "TrajectoryManyPoints.h"
#include "Vector.h"

class TrajectoryPolygon: public TrajectoryManyPoints
{
protected:
	// zbi�r d�ugo�ci wektor�w
	typedef std::vector<float>	DistanceVector;
	DistanceVector				distanceBetweenPoint;

public:
	// Konstruktory
	TrajectoryPolygon();
	TrajectoryPolygon(std::vector<D3DXVECTOR2> const & pointVector);

	// zwr�cenie pozycji na linii w postaci wektora
	D3DXVECTOR2 GetPosition( float const dis ) override;
	// Dodanie punktu i uzupe�nienie listy d�ugo�ci odcink�w
	void AddPoint(D3DXVECTOR2 const & point) override;
	
	// obliczenie d�ugo�ci linii �amanej
	void CalculateLength() override;
	// metoda skalowania uzwgl�dniaj�ca d�ugo�ci odcink�w
	void Scale( float const scale );
};

