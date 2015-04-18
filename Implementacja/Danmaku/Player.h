#pragma once

#include "GameObject.h"
#include "Move.h"

#define POS_X 620.0f
#define POS_Y 500.0f
#define SPEED 500.0f
#define FOCUS_SPEED 250.0f

//rozmiary (póŸniej mog¹ byæ dobierane na podstawie rozdzielczoœci sprajta lub odwrotnie)

#define SIZE_X 40
#define SIZE_Y 60

class Player : public GameObject
{

protected:

	bool isFocused;

	D3DXVECTOR2 center;				// Przesuniêcie punktu œrodkowego wzglêdem lewego górnego rogu

public:
	Player();
	void Update(float const & time, Move & move);

	// Gettery
	bool GetFocus();
	D3DXVECTOR2 GetPosition();
	
	// Settery
	void SetFocus(bool focus);
	
};