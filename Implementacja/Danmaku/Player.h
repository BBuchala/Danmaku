#pragma once

#include "GameObject.h"

#define POS_X 620.0f
#define POS_Y 500.0f
#define SPEED 250.0f

class Player : public GameObject
{
public:
	Player();

	void Update(float const & time, Move & move);
	
};