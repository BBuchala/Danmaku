#pragma once

#include "GameObject.h"
#include "Move.h"

#define POS_X 620.0f
#define POS_Y 500.0f
#define SPEED 500.0f
#define FOCUS_SPEED 250.0f

//rozmiary (p�niej mog� by� dobierane na podstawie rozdzielczo�ci sprajta lub odwrotnie)

#define SIZE_X 40
#define SIZE_Y 60

class Player : public GameObject
{

protected:

	bool isFocused;

	D3DXVECTOR2 center;				// Przesuni�cie punktu �rodkowego wzgl�dem lewego g�rnego rogu

public:
	Player();
	void Update(float const & time, Move & move);

	// Gettery
	bool GetFocus();
	
	// Settery
	void SetFocus(bool focus);

	// Przeci��ona metoda zwracaj�ca �rodkowy punkt (piksel) gracza. P�niej do zast�pienia hitboxem.
	inline D3DXVECTOR2 GetPosition()
	{
		return this->position + center;
	};
	
};