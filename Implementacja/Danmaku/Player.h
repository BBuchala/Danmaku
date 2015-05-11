#pragma once

#include "GameObject.h"
#include "Move.h"
#include "PPattern.h"
#include "PlayerPattern01.h"
#include "PlayerPattern02.h"
#include "PlayerPattern03.h"


class Player : public GameObject
{
protected:
	/* ==== DEFINICJE ======================== */
	/// Definicja kolejki pocisków
	typedef std::deque<PlayerBullet*> PBulletQue;

	/* ==== STA£E ======================== */
	// prêdkoœci
	static const unsigned short SPEED		= 500;
	static const unsigned short FOCUS_SPEED	= 250;
	//rozmiary (póŸniej mog¹ byæ dobierane na podstawie rozdzielczoœci sprajta lub odwrotnie)
	static const unsigned short SIZE_X		= 40;
	static const unsigned short SIZE_Y		= 60;

	typedef std::unique_ptr<PPattern> PPatternPtr;

	bool isFocused;
	BYTE lifeCount;
	BYTE bombCount;
	//bool isShooting;

	BYTE powerLevel;				// Oznacza aktualn¹ moc z jak¹ gracz napieprza wró¿ki/statki/whatever (1, 2, 3, 4)
	float power;					// Odzwierciedla wartoœæ uzbieranych bonusów (np 2.15)
	bool hasPatternChanged;

public:
	
	PPatternPtr playerPattern;

	Player( D3DXVECTOR2 const & pos, BYTE lifeCount, BYTE bombCount );
	Player( D3DXVECTOR2 const & pos, BYTE lifeCount );

	bool InitializePattern(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position);

	// Przeci¹¿one metody GameObject
	void Update(float const time, Move const move);
	void Draw(RECT const & rect);

	// Gettery
	bool GetFocus() const;
	BYTE GetLifeCount();
	BYTE GetBombCount();
	bool IsShooting();
	bool HasPatternChanged();
	
	// Settery
	void SetFocus(bool const focus);
	void SetLifeCount(const BYTE lifeCount);
	void SetBombCount(const BYTE bombCount);
	void SetIsShooting(const bool isShooting);
	void SetHasPatternChanged(const bool hasPatternChanged);
	
	// Incrementy i Decrementy
	void IncrementLifeCount();
	void IncrementBombCount();
	void DecrementLifeCount();					// to mo¿na wykorzystaæ przy sprawdzaniu warunku koñca gry - if (player->lifeCount <= 0) ...
	void DecrementBombCount();					// t¹ jedn¹ wsadzi siê do jakiej wiêkszej metody UseBomb() - ze sprawdzaniem czasu deathbomby, efektem graficznym itp.
	
	// Strzelanie
	void CalculatePowerLevel();
	void AddToPower(const float value);
	void SubFromPower(const float value);

	void ChangePlayerPattern();
	void Shoot(float const time);

	inline float GetPower()
	{
		return this->power;
	};

	inline PBulletQue const & GetBullets() const
	{
		return this->playerPattern->GetBullets();
	};
};