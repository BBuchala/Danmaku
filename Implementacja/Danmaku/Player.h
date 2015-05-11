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
	/// Definicja kolejki pocisk�w
	typedef std::deque<PlayerBullet*> PBulletQue;

	/* ==== STA�E ======================== */
	// pr�dko�ci
	static const unsigned short SPEED		= 500;
	static const unsigned short FOCUS_SPEED	= 250;
	//rozmiary (p�niej mog� by� dobierane na podstawie rozdzielczo�ci sprajta lub odwrotnie)
	static const unsigned short SIZE_X		= 40;
	static const unsigned short SIZE_Y		= 60;

	typedef std::unique_ptr<PPattern> PPatternPtr;

	bool isFocused;
	BYTE lifeCount;
	BYTE bombCount;
	//bool isShooting;

	BYTE powerLevel;				// Oznacza aktualn� moc z jak� gracz napieprza wr�ki/statki/whatever (1, 2, 3, 4)
	float power;					// Odzwierciedla warto�� uzbieranych bonus�w (np 2.15)
	bool hasPatternChanged;

public:
	
	PPatternPtr playerPattern;

	Player( D3DXVECTOR2 const & pos, BYTE lifeCount, BYTE bombCount );
	Player( D3DXVECTOR2 const & pos, BYTE lifeCount );

	bool InitializePattern(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position);

	// Przeci��one metody GameObject
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
	void DecrementLifeCount();					// to mo�na wykorzysta� przy sprawdzaniu warunku ko�ca gry - if (player->lifeCount <= 0) ...
	void DecrementBombCount();					// t� jedn� wsadzi si� do jakiej wi�kszej metody UseBomb() - ze sprawdzaniem czasu deathbomby, efektem graficznym itp.
	
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