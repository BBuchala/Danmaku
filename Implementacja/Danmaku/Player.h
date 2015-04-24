#pragma once

#include "GameObject.h"
#include "Move.h"

#define SPEED 500.0f
#define FOCUS_SPEED 250.0f

//rozmiary (p�niej mog� by� dobierane na podstawie rozdzielczo�ci sprajta lub odwrotnie)

#define SIZE_X 40
#define SIZE_Y 60

class Player : public GameObject
{

protected:

	bool isFocused;

public:
	Player( D3DXVECTOR2 const & pos );

	bool Initialize(LPDIRECT3DDEVICE9 device, std::string const & file, int const & width, int const & height);

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