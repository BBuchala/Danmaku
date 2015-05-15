#pragma once

#include "GameObject.h"
#include "Move.h"
#include "PPattern.h"
#include "PlayerPattern01.h"
#include "PlayerPattern02.h"
#include "PlayerPattern03.h"
#include "PlayerPattern04.h"
#include "PlayerPattern05.h"
#include "Bomb.h"

class Player : public GameObject
{
protected:
	/* ==== DEFINICJE ===================================== */
	/// Definicja kolejki pocisków
	typedef std::deque<PlayerBullet*> PBulletQue;
	typedef std::unique_ptr<PPattern> PPatternPtr;
	typedef std::unique_ptr<Bomb> BombPtr;

	/* ==== STA£E ========================================= */
	// prêdkoœci
	static const unsigned short SPEED		= 500;
	static const unsigned short FOCUS_SPEED	= 250;
	//rozmiary (póŸniej mog¹ byæ dobierane na podstawie rozdzielczoœci sprajta lub odwrotnie)
	static const unsigned short SIZE_X		= 40;
	static const unsigned short SIZE_Y		= 60;
	static const float			INVULNERABLE_TIME;

	bool _isFocused;
	BYTE _lifeCount;
	BYTE _bombCount;

	BYTE _powerLevel;				// Oznacza aktualn¹ moc z jak¹ gracz napieprza wró¿ki/statki/whatever (1, 2, 3, 4)
	float _power;					// Odzwierciedla wartoœæ uzbieranych bonusów (np 2.15)
	bool _hasPatternChanged;

	float _invulnerableTime;
	bool _isInvulnerable;

	PPatternPtr _playerPattern;

	BombPtr _bomb;
	//Bomb * _bomb;

public:
	Player( D3DXVECTOR2 const & pos, BYTE lifeCount, BYTE bombCount = 3 );

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
	void SetIsInvulnerable();
	
	// Incrementy i Decrementy
	void IncrementLifeCount();
	void IncrementBombCount();
	void DecrementLifeCount();					
	void DecrementBombCount();
	
	// Strzelanie
	void CalculatePowerLevel();
	void AddToPower(const float value);
	void SubFromPower(const float value);

	void ChangePlayerPattern();
	void Shoot(float const time);

	// Bomba
	bool UseBomb();										// true - uda³o siê odpaliæ bombê, false - nie mamy bomb do odpalenia

	inline float GetPower()
	{
		return _power;
	};

	inline PBulletQue & GetBullets() const
	{
		return _playerPattern->GetBullets();
	};

	inline bool const IsUsingBomb() const
	{
		return _bomb->InUse();
	};

	inline bool const IsInvulnerable() const
	{
		return _isInvulnerable;
	};

};