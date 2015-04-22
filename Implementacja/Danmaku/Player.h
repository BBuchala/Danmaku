#pragma once

#include "GameObject.h"
#include "Move.h"

#define SPEED 500.0f
#define FOCUS_SPEED 250.0f

//rozmiary (póŸniej mog¹ byæ dobierane na podstawie rozdzielczoœci sprajta lub odwrotnie)

#define SIZE_X 40
#define SIZE_Y 60

class Player : public GameObject
{

protected:

	bool isFocused;

public:
	Player( D3DXVECTOR2 const & pos );
	void Update(float const & time, Move & move);

	// Gettery
	bool GetFocus();
	
	// Settery
	void SetFocus(bool focus);

	// Przeci¹¿ona metoda zwracaj¹ca œrodkowy punkt (piksel) gracza. PóŸniej do zast¹pienia hitboxem.
	//inline D3DXVECTOR2 GetPosition()
	//{
	//	return this->position + center;
	//};
	
};