#pragma once

#include "GameObject.h"
#include "Move.h"

#define POS_X 620.0f
#define POS_Y 500.0f
#define SPEED 500.0f
#define FOCUS_SPEED 250.0f

class Player : public GameObject
{

protected:

	bool isFocused;

public:
	Player();
	void Update(float const & time, Move & move);

	// Gettery
	bool GetFocus();

	// Settery
	void SetFocus(bool focus);
	
};