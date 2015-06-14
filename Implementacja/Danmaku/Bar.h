#pragma once

#include "Sprite.h"
#include "BarInitializationFailedException.h"

/// <summary>
/// Klasa odpowiadaj¹ca za tworznie pasków z ikonami
/// </summary>
class Bar
{
private:

	Sprite * sprite;
	D3DXVECTOR2 startPos;

	BYTE count;

public:
	Bar(D3DXVECTOR2 pos, BYTE initialCount);
	~Bar();

	bool Initialize(LPDIRECT3DDEVICE9 device, std::string const & file, int const width, int const height);
	bool Initialize(LPDIRECT3DDEVICE9 device, std::string const & file);

	void Draw();

	void IncrementCount();
	void DecrementCount();

	void SetCount(short newCount);

	Bar & operator++();		// ++Bar
	Bar & operator--();		// --Bar
	int operator++(int);	// Bar++
	int operator--(int);	// Bar++
};