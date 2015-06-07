#pragma once

#include "TrajectoryManyPoints.h"

// Klasa obs�uguj�ca utworzenie i zarz�dzanie tra� a wpostaci linii Beziera
// Nie mo�e sk�ada� si� z wi�cej ni� 4 punkt�w
class TrajectoryBezier: public TrajectoryManyPoints
{
public:
	// czy krzywa si� zap�tla
	bool _loopFlag;

	// zwr�cenie pozycji na linii w postaci wektora
	D3DXVECTOR2 GetPosition( float const dis ) override;

	// Dodanie punktu do zbioru
	void AddPoint(D3DXVECTOR2 const & point) override;

	// Wyszukanie punktu na linii Beziera
	D3DXVECTOR2 FindPoint(double t, D3DXVECTOR2 start, D3DXVECTOR2 c1, D3DXVECTOR2 c2, D3DXVECTOR2 end);
	double FindPoint(double t, double start, double c1, double c2, double end);

	// Obliczenie d�ugo�ci linii Beziera
	void CalculateLength() override;

	// Konstruktor
	TrajectoryBezier();

	// Ustawienie loopu
	void SetLoop(bool value);
	
private:
	// Obliczenie d�ugo�ci linii dla 2 punkt�w
	// Obliczane zgodnie ze zwyk�ych wzorem na d�ugo�c odcinka
	 void CalculateLength2P();

	// Obliczenie d�ugo�ci linii dla 3 punkt�w
	// Obliczane zgodnie ze szczeg�owym wzorem
	void CalculateLength3P();

	// Obliczenie d�ugo�ci linii dla 3 punkt�w
	// Obliczane wg metody aproksymuj�cej
	void CalculateLength4P();
};
