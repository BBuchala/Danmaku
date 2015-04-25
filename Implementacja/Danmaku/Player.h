#pragma once

#include "GameObject.h"
#include "Move.h"


class Player : public GameObject
{
protected:
	/* ==== STA�E ======================== */
	// pr�dko�ci
	static const unsigned short SPEED		= 500;
	static const unsigned short FOCUS_SPEED	= 250;
	//rozmiary (p�niej mog� by� dobierane na podstawie rozdzielczo�ci sprajta lub odwrotnie)
	static const unsigned short SIZE_X		= 40;
	static const unsigned short SIZE_Y		= 60;

	bool isFocused;

public:
	Player( D3DXVECTOR2 const & pos );

	bool InitializeSprite(LPDIRECT3DDEVICE9 device, std::string const & file, int const & width, int const & height);

	void Update(float const & time, Move & move);

	// Gettery
	bool GetFocus();
	
	// Settery
	void SetFocus(bool focus);

	// Przeci��ona metoda zwracaj�ca �rodkowy punkt (piksel) gracza. P�niej do zast�pienia hitboxem.
	//inline D3DXVECTOR2 GetPosition()
	//{
	//	return this->position + center;
	//};
	
};