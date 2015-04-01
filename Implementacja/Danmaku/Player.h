#pragma once

#include "GameObject.h"


class Player : public GameObject
{
public:
	Player();

	void Update(float const & time, Move & move);
	
};