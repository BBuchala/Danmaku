#pragma once

#include "TrajectoryManyPoints.h"

// Klasa obs³uguj¹ca utworzenie i zarz¹dzanie traœ a wpostaci linii Beziera
// Nie mo¿e sk³adaæ siê z wiêcej ni¿ 4 punktów
class TrajectoryBezier: public TrajectoryManyPoints
{
public:
	// czy krzywa siê zapêtla
	bool _loopFlag;

	// zwrócenie pozycji na linii w postaci wektora
	D3DXVECTOR2 GetPosition( float const dis ) override;

	// Dodanie punktu do zbioru
	void AddPoint(D3DXVECTOR2 const & point) override;

	// Wyszukanie punktu na linii Beziera
	D3DXVECTOR2 FindPoint(double t, D3DXVECTOR2 start, D3DXVECTOR2 c1, D3DXVECTOR2 c2, D3DXVECTOR2 end);
	double FindPoint(double t, double start, double c1, double c2, double end);

	// Obliczenie d³ugoœci linii Beziera
	void CalculateLength() override;

	// Konstruktor
	TrajectoryBezier();

	// Ustawienie loopu
	void SetLoop(bool value);
	
private:
	// Obliczenie d³ugoœci linii dla 2 punktów
	// Obliczane zgodnie ze zwyk³ych wzorem na d³ugoœc odcinka
	 void CalculateLength2P();

	// Obliczenie d³ugoœci linii dla 3 punktów
	// Obliczane zgodnie ze szczegó³owym wzorem
	void CalculateLength3P();

	// Obliczenie d³ugoœci linii dla 3 punktów
	// Obliczane wg metody aproksymuj¹cej
	void CalculateLength4P();
};
