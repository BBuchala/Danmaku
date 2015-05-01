#pragma once

#include "GameObject.h"
#include "Move.h"
#include "PlayerPattern.h"


class Player : public GameObject
{
protected:
	/* ==== STA£E ======================== */
	// prêdkoœci
	static const unsigned short SPEED		= 500;
	static const unsigned short FOCUS_SPEED	= 250;
	//rozmiary (póŸniej mog¹ byæ dobierane na podstawie rozdzielczoœci sprajta lub odwrotnie)
	static const unsigned short SIZE_X		= 40;
	static const unsigned short SIZE_Y		= 60;

	bool isFocused;
	BYTE lifeCount;
	BYTE bombCount;

	BYTE powerLevel;				// Oznacza aktualn¹ moc z jak¹ gracz napieprza wró¿ki/statki/whatever (1, 2, 3, 4)
	float power;					// Odzwierciedla wartoœæ uzbieranych bonusów (np 2.15)

	bool isShooting;


public:

	PlayerPattern * playerPattern;

	Player( D3DXVECTOR2 const & pos, BYTE lifeCount, BYTE bombCount );
	Player( D3DXVECTOR2 const & pos, BYTE lifeCount );

	void Update(float const time, Move const move);

	// Gettery
	bool GetFocus() const;
	BYTE GetLifeCount();
	BYTE GetBombCount();
	bool IsShooting();
	
	// Settery
	void SetFocus(bool const focus);
	void SetLifeCount(const BYTE lifeCount);
	void SetBombCount(const BYTE bombCount);
	void SetIsShooting(const bool isShooting);
	
	// Incrementy i Decrementy
	void IncrementLifeCount();
	void IncrementBombCount();
	void DecrementLifeCount();					// to mo¿na wykorzystaæ przy sprawdzaniu warunku koñca gry - if (player->lifeCount <= 0) ...
	void DecrementBombCount();					// t¹ jedn¹ wsadzi siê do jakiej wiêkszej metody UseBomb() - ze sprawdzaniem czasu deathbomby, efektem graficznym itp.
	
	// Strzelanie
	void CalculatePowerLevel();

	void Shoot(LPDIRECT3DDEVICE9 device);

};